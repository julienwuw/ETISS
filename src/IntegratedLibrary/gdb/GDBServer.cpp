/**

@copyright
<pre>


	Copyright (c) 2014 Institute for Electronic Design Automation, TU Munich

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.


</pre>
@author Marc Greim <marc.greim@mytum.de>

@date July 29, 2014

@version 0.1

*/
/**
	@file

	@brief implementation of etiss/IntegratedLibrary/gdb/GDBServer.h

	@detail

*/
#include "etiss/jit/types.h"
#include "etiss/IntegratedLibrary/gdb/GDBServer.h"
#include "etiss/IntegratedLibrary/gdb/Hex.h"
#include "etiss/IntegratedLibrary/gdb/UnixTCPGDBConnection.h"
#include "etiss/CPUCore.h"
#include <chrono>
#include <thread>
#include <cstring>

using namespace etiss::plugin::gdb;

BreakpointDB::BreakpointDB(){
	instrbrkpt_ = 0;
}

void BreakpointDB::set(etiss::uint64 addr,etiss::uint32 val){
	if (instrbrkpt_ == 0){
		if (val == 0) return;
		instrbrkpt_ = new etiss::uint32 *** [1<<16];
		memset(instrbrkpt_,0,sizeof(etiss::uint32 *** [1<<16]));
	}
	unsigned a1 = (addr)&0xFFFF;
	if (instrbrkpt_[a1] == 0){
		if (val == 0) return;
		instrbrkpt_[a1] = new etiss::uint32 ** [1<<16];
		memset(instrbrkpt_[a1],0,sizeof(etiss::uint32 ** [1<<16]));
	}
	unsigned a2 = (addr>>16)&0xFFFF;
	if (instrbrkpt_[a1][a2] == 0){
		if (val == 0) return;
		instrbrkpt_[a1][a2] = new etiss::uint32 * [1<<16];
		memset(instrbrkpt_[a1][a2],0,sizeof(etiss::uint32 * [1<<16]));
	}
	unsigned a3 = (addr>>32)&0xFFFF;
	if (instrbrkpt_[a1][a2][a3] == 0){
		if (val == 0) return;
		instrbrkpt_[a1][a2][a3] = new etiss::uint32[1<<16];
		memset(instrbrkpt_[a1][a2][a3],0,sizeof(etiss::uint32[1<<16]));
	}
	unsigned a4 = (addr>>48)&0xFFFF;
	if (instrbrkpt_[a1][a2][a3][a4] != 0 && val==0)
		std::cout << "Breakpoint removed: " << std::hex << (addr<<2) << std::dec << std::endl;
	if (instrbrkpt_[a1][a2][a3][a4] == 0 && val!=0)
		std::cout << "Breakpoint added: " << std::hex << (addr<<2) << std::dec << std::endl;
	instrbrkpt_[a1][a2][a3][a4] = val;
	if (val == 0){ // cleanup
		bool empty = true;
		for (unsigned i = 0;i<(1<<16);i++){
			if (instrbrkpt_[a1][a2][a3][i] != 0){
				empty = false;
				break;
			}
		}
		if (!empty) return;
		delete instrbrkpt_[a1][a2][a3];
		instrbrkpt_[a1][a2][a3] = 0;
		for (unsigned i = 0;i<(1<<16);i++){
			if (instrbrkpt_[a1][a2][i] != 0){
				empty = false;
				break;
			}
		}
		if (!empty) return;
		delete instrbrkpt_[a1][a2];
		instrbrkpt_[a1][a2] = 0;
		for (unsigned i = 0;i<(1<<16);i++){
			if (instrbrkpt_[a1][i] != 0){
				empty = false;
				break;
			}
		}
		if (!empty) return;
		delete instrbrkpt_[a1];
		instrbrkpt_[a1] = 0;
		for (unsigned i = 0;i<(1<<16);i++){
			if (instrbrkpt_[i] != 0){
				empty = false;
				break;
			}
		}
		if (!empty) return;
		delete instrbrkpt_;
		instrbrkpt_ = 0;
	}
}

Server::Server(etiss::plugin::gdb::PacketProtocol & pp) : con_(pp){
	status_paused_ = true;
	gdb_status_paused_ = true;
	status_step_ = false;
	status_pending_jump_ = false;
	status_pending_kill_ = false;
	status_jumpaddr_ = false;
	arch_ = nullptr;
	cpu_ = nullptr;
	system_ = nullptr;
	execute_skip_count = 25;
	execute_skip_index = 0;
}

Server::~Server(){

}

etiss::int32 Server::preInstructionCallback(){
	//std::cout << "0x" << std::hex << (cpu_->instructionPointer<<2) << std::dec << " 0x" << std::hex << (cpu_->instructionPointer) << std::dec << std::endl;
	// check for instruction breakpoints
	if (unlikely(!breakpoints_.isEmpty())){
		etiss::uint32 bp = breakpoints_.get(arch_->getGDBCore().getInstructionPointer(cpu_));
		if (unlikely(bp != 0)){
			if ((bp & 3) != 0){
				status_paused_ = true;
			}
		}
	}
	// apply single step pause
	if (unlikely(status_step_>0)){
		status_paused_ = true;
		status_step_--;
	}
	if (unlikely(status_pending_kill_)){
		return RETURNCODE::CPUTERMINATED;
	}
	// check paused state (due to singlestep,ctrl+c)
	if (unlikely(status_paused_)){
		if (!gdb_status_paused_){ // answer pending 'c'/'s' command
			//std::cout << "GDB: answer: " << "T"<<hex::fromByte(5) << std::endl;
			con_.snd("T"+hex::fromByte(5),false);
			gdb_status_paused_ = true;
		}

		while (unlikely(status_paused_)){
			handlePacket(true);
			if (unlikely(status_pending_kill_)){
				return RETURNCODE::CPUTERMINATED;
			}
			if (status_paused_){
				//std::this_thread::sleep_for(std::chrono::milliseconds(50)); // removed due to blocking handle packet call
			} else {
				if (status_pending_jump_){
					cpu_->instructionPointer = status_jumpaddr_;
					status_pending_jump_ = false;
				}
			}
		}
	}


	return RETURNCODE::NOERROR;
}

etiss::int32 Server::execute(){

	if (unlikely(status_pending_kill_)){
		return RETURNCODE::CPUTERMINATED;
	}

	if ((execute_skip_index++) > execute_skip_count){ // connections such as tcp sockets have a large overhead. to provide acceptable performance packet checks may not be performed too frequent
		execute_skip_index = 0;
		// check for BREAK event in between blocks
		handlePacket(false);
	}
	if (unlikely(status_pending_kill_)){
		return RETURNCODE::CPUTERMINATED;
	}

	return 0;
}

void Server::process(etiss::CodeBlock & block,unsigned index){

	// add gdb callback code at the start of single instructions and at the start of meta instructions (NOT in between parts of meta instructions)
	bool wasmeta = false;
	for (unsigned i = 0;i<block.length();i++){
		if (!wasmeta){ // may return
			CodeSet & cs = block.get(i).getCodeSet();
			CodePart & part = cs.append(CodePart::PREINITIALDEBUGRETURNING);
			std::stringstream ss;
			ss << "{\n";
			ss << "\tetiss_int32 _gdb_exception = gdb_pre_instruction(cpu,system,plugin_pointers["<< index << "]);\n";
			ss << "\tif (_gdb_exception != 0)\n\t return _gdb_exception==-16?0:_gdb_exception;";
			ss << "}";
			part.getCode() = ss.str();
		} else {
			CodeSet & cs = block.get(i).getCodeSet();
			CodePart & part = cs.prepend(CodePart::INITIALREQUIRED);
			std::stringstream ss;
			ss << "{\n";
			ss << "\tgdb_pre_instruction_noreturn(cpu,system,plugin_pointers["<< index << "]);\n";
			ss << "}";
			part.getCode() = ss.str();
		}
		//wasmeta = block.get(i).isMetaInstruction();
	}

	// add file global code
	block.fileglobalCode().insert("extern etiss_int32 gdb_pre_instruction(ETISS_CPU * ,ETISS_System * ,void * );extern void gdb_pre_instruction_noreturn(ETISS_CPU * ,ETISS_System * ,void * );");


}


static void Server_finalizeInstrSet(etiss::instr::InstructionSet * set,std::string pcode){
	if (set == nullptr)
		return;
	set->foreach([pcode](etiss::instr::Instruction & instr){
		instr.addCallback([pcode](etiss::instr::BitArray &,etiss::CodeSet &cs,etiss::instr::InstructionContext &){
			etiss::CodePart & cp = cs.prepend(etiss::CodePart::PREINITIALDEBUGRETURNING);
			cp.code() = std::string(
				"{\n"
				"\tetiss_int32 _gdb_exception = gdb_pre_instruction(cpu,system,") + pcode + ");\n"
				"\tif (_gdb_exception != 0)\n\t return _gdb_exception==-16?0:_gdb_exception;\n"
				"}";
			return true;
		},0);
		///TODO? ensure instruction pointer update
	});
}

void Server::finalizeInstrSet(etiss::instr::ModedInstructionSet & mis) const{
	std::string pcode = getPointerCode();
	mis.foreach([pcode](etiss::instr::VariableInstructionSet & vis){vis.foreach([pcode](etiss::instr::InstructionSet & set){ Server_finalizeInstrSet(&set,pcode) ;});});
}

 void Server::finalizeCodeBlock(etiss::CodeBlock & cb) const {

	cb.fileglobalCode().insert("extern etiss_int32 gdb_pre_instruction(ETISS_CPU * ,ETISS_System * ,void * );extern void gdb_pre_instruction_noreturn(ETISS_CPU * ,ETISS_System * ,void * );");

}



void Server::handlePacket(bool block){

	if (con_.available(block)){
		bool isnotification;
		std::string command = con_.rcv(isnotification);
		if (command.length()>0){
			if (!status_paused_){
				if (!gdb_status_paused_){ // answer pending 'c'/'s' command
					//std::cout << "GDB: answer: " << "T"<<hex::fromByte(5) << std::endl;
					con_.snd("T"+hex::fromByte(5),false);
					gdb_status_paused_ = true;
				}
				status_paused_ = true;
			}
			bool nodbgaction = false;
			std::string answer;
			bool answerisnotification = false;
			switch (command[0]){
			case 'g': // read registers
			{
				for (unsigned i = 0;i<arch_->getGDBCore().mappedRegisterCount();i++){
					std::string regname = arch_->getGDBCore().mapRegister(i);
                    auto  f = plugin_core_->getStruct()->findName(regname);
                    if (!f){
                        answer = "EFF";
                        etiss::log(etiss::ERROR,"Faulty implementation of the GDBCore: Register not found",regname,*plugin_core_);
                        break;
					}
					switch (f->width_){
						case 8:
							hex::fromInt(answer,(uint8_t)f->read(),arch_->getGDBCore().isLittleEndian());
							break;
						case 16:
							hex::fromInt(answer,(uint16_t)f->read(),arch_->getGDBCore().isLittleEndian());
							break;
						case 32:
							hex::fromInt(answer,(uint32_t)f->read(),arch_->getGDBCore().isLittleEndian());
							break;
						case 64:
							hex::fromInt(answer,(uint64_t)f->read(),arch_->getGDBCore().isLittleEndian());
							break;
					}
				}
			}
			break;
			case 'G': // write registers
			{
				unsigned treglen = 0;
				for (unsigned i = 0;i<arch_->getGDBCore().mappedRegisterCount();i++){
				    auto  f = plugin_core_->getStruct()->findName(arch_->getGDBCore().mapRegister(i));
                    if (!f){
                        answer = "EFF";
                        etiss::log(etiss::ERROR,"Faulty implementation of the GDBCore: Register not found",arch_->getGDBCore().mapRegister(i),*plugin_core_);
                        break;
					}
					treglen+= f->width_;
				}
				if (command.length() == (treglen>>2)+1){
					answer = "OK";
					unsigned off = 1;
					for (unsigned i = 0;i<arch_->getGDBCore().mappedRegisterCount();i++){
						std::string regname = arch_->getGDBCore().mapRegister(i);
						auto  f = plugin_core_->getStruct()->findName(regname);
                        if (!f){
                            answer = "EFF";
                            etiss::log(etiss::ERROR,"Faulty implementation of the GDBCore: Register not found",regname,*plugin_core_);
                            break;
					    }
					    switch (f->width_){
							case 8:
								f->write(hex::toInt<uint8_t>(command,arch_->getGDBCore().isLittleEndian(),off));
								off += 8>>2;
								break;
							case 16:
								f->write(hex::toInt<uint16_t>(command,arch_->getGDBCore().isLittleEndian(),off));
								off += 16>>2;
								break;
							case 32:
								f->write(hex::toInt<uint32_t>(command,arch_->getGDBCore().isLittleEndian(),off));
								off += 32>>2;
								break;
							case 64:
								f->write(hex::toInt<uint64_t>(command,arch_->getGDBCore().isLittleEndian(),off));
								off += 64>>2;
								break;

						}
					}
				} else {
					answer = "E11";
				}

			}
			break;
			case 'm': // read memory
			{
				unsigned pos = 1;
				etiss::uint64 addr = hex::tryInt<etiss::uint64>(command,pos);
				pos++;
				etiss::uint32 length = hex::tryInt<etiss::uint32>(command,pos);
				etiss::uint8 * buf = new etiss::uint8[length];
				etiss::int32 exception = (*system_->dbg_read)(system_->handle,addr,buf,length);
				if (exception != RETURNCODE::NOERROR){
					answer = "EFF";
				} else {
					answer = hex::fromBytes(buf,length);
				}
				nodbgaction = true;
				delete[] buf;
			}
			break;
			case 'c':// continue
			{
				if (command.length()>1){
					etiss::uint64 addr = 0;
					for (size_t i = 1;i<command.length();i+=2){
						addr = (addr<<8) | hex::toByte(command[i],command[i+1]);
					}
					status_jumpaddr_ = addr;
					status_pending_jump_ = true;
				}
				status_paused_ = false;
				gdb_status_paused_ = false;
				status_step_ = 0;
				//std::cout << "GDB: command: " << command << std::endl;
				return;
			}
			break;
			case 's':
			{
				if (command.length()>1){
					etiss::uint64 addr = 0;
					for (size_t i = 1;i<command.length();i+=2){
						addr = (addr<<8) | hex::toByte(command[i],command[i+1]);
					}
					status_jumpaddr_ = addr;
					status_pending_jump_ = true;
				}
				status_paused_ = false;
				gdb_status_paused_ = false;
				status_step_ = 1;
				//std::cout << "GDB: command: " << command << std::endl;
				return;
			}
			break;
			case '?':
			{
				answer = "T";hex::fromByte(answer,5);
			}
			break;
			case 'W': // custom break message; might be changed in future if W is used (apply changes also to Connection::BREAKMESSAGE)
			{
				status_paused_ = true;
				return;
			}
			break;
			case 'Z': // insert breakpoint
			{
				if (command.length()>2 && command[2] == ','){
					switch (command[1]){
					case '0': // memory breakpoint
					{
						unsigned pos = 3;
						etiss::uint64 addr = hex::tryInt<etiss::uint64>(command,pos);
						addr = addr >> 2;
						if (pos>3){
							etiss::uint32 flags = breakpoints_.get(addr);
							if ((flags&1) == 0){
								breakpoints_.set(addr,flags | 1);
							}
							answer = "OK";
						} else {
							answer = "EFF";
						}
					}
					break;
					case '1': // hardware breakpoint
					{
						unsigned pos = 3;
						etiss::uint64 addr = hex::tryInt<etiss::uint64>(command,pos);
						addr = addr >> 2;
						if (pos>3){
							etiss::uint32 flags = breakpoints_.get(addr);
							if ((flags&2) == 0){
								breakpoints_.set(addr,flags | 2);
							}
							answer = "OK";
						} else {
							answer = "EFF";
						}
					}
					break;
					}
				}
			}
			break;
			case 'z': // remove breakpoint
			{
				if (command.length()>2 && command[2] == ','){
					switch (command[1]){
					case '0': // memory breakpoint
					{
						unsigned pos = 3;
						etiss::uint64 addr = hex::tryInt<etiss::uint64>(command,pos);
						addr = addr >> 2;
						if (pos>3){
							etiss::uint32 flags = breakpoints_.get(addr);
							if ((flags&1) != 0){
								breakpoints_.set(addr,flags & ~1);
							}
							answer = "OK";
						} else {
							answer = "EFF";
						}
					}
					break;
					case '1': // hardware breakpoint
					{
						unsigned pos = 3;
						etiss::uint64 addr = hex::tryInt<etiss::uint64>(command,pos);
						addr = addr >> 2;
						if (pos>3){
							etiss::uint32 flags = breakpoints_.get(addr);
							if ((flags&2) != 0){
								breakpoints_.set(addr,flags & ~2);
							}
							answer = "OK";
						} else {
							answer = "EFF";
						}
					}
					break;
					}
				}
			}
			break;
			case 'q':
				{
					if (command.substr(1,9) == "Supported"){
						answer = "";
					} else
					if (command.substr(1,8) == "Attached"){
						answer = "0";
					} else
					if (command.substr(1,8) == "Symbol::"){
						answer = "OK";
					} else
					if (command.substr(1,1) == "C"){
						answer = "0";
					} else
					if (command.substr(1,7) == "TStatus"){
						answer = "T0;tnotrun:0";
					}
				}
			break;
			case 'k':
				{
					status_pending_kill_ = true;
					return;
				}
			break;
			case 'H':
				if (command.length()>1){
					switch(command[1]){
					case 'c':
					case 'g':
						answer = "OK"; // only one thread. ignore thread selection and continue
						break;
					default:
						std::cout << "GDB: unknown command: " << command << std::endl;
					}
				} else {
					//std::cout << "GDB: unknown command: " << command << std::endl;
				}
			break;
			default:
				std::cout << "GDB: unknown command: " << command << std::endl;
			break;
			}
			if (!nodbgaction){
				//std::cout << "GDB: command: " << command << std::endl;
				//std::cout << "GDB: answer: "<<answer << std::endl;
			}
			con_.snd(answer,answerisnotification);
		}
	}

}

etiss::int32 Server::preMemoryAccessCallback(etiss::uint64 addr,etiss::uint32 len,bool data,bool read){

	return RETURNCODE::NOERROR;

}

std::string Server::_getPluginName()const{
	return "GDB";
}

void * Server::getPluginHandle(){
	return (void*) this;
}

void Server::init(ETISS_CPU * cpu,ETISS_System * system,etiss::CPUArch * arch){
	arch_ = arch;
	cpu_ = cpu;
	system_ = system;
}

void Server::cleanup(){
	arch_ = nullptr;
	cpu_ = nullptr;
	system_ = nullptr;
}

Server * Server::createTCPServer(std::map<std::string,std::string> options){
	int port = 2222;

	{ // parse port
		auto f = options.find("port");
		if (f != options.end()){
			int tmp = atoi(f->second.c_str());
			if (tmp > 0)
				port = tmp;
			else
				etiss::log(etiss::ERROR,std::string("etiss::plugin::gdb::Server: failed to parse port value for tcp socket: ")+f->second);
		}
	}



	Server * s = createTCPServer(port);

	{ // parse skip count
		auto f = options.find("skipcount");
		if (f != options.end()){
			int tmp = atoi(f->second.c_str());
			if (tmp >= 0)
				s->execute_skip_count = tmp;
		}
	}

	return s;

}
Server * Server::createTCPServer(int port){

#if ETISS_USE_POSIX_SOCKET
	etiss::log(etiss::VERBOSE,std::string("etiss::plugin::gdb::Server: starting tcp server on port ") + etiss::toString(port));

	std::shared_ptr<Connection> cs(new etiss::plugin::gdb::UnixTCPGDBConnection(port));

	Server * s = new Server(cs.get()->getPacketProtocol());

	s->cinst_ = cs;

	return s;
#else

    return 0;

#endif



}

extern "C" {
	etiss_int32 gdb_pre_instruction(ETISS_CPU * cpu,ETISS_System * system,void * gdbserver){
		return ((etiss::plugin::gdb::Server*)gdbserver)->preInstructionCallback();
	}
	void gdb_pre_instruction_noreturn(ETISS_CPU * ,ETISS_System * ,void * gdbserver){
		/// @todo fix possible exception loss
		((etiss::plugin::gdb::Server*)gdbserver)->preInstructionCallback();
	}
}

















