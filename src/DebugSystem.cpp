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

	@brief implementation of etiss/DebugSystem.h

	@detail

*/

#include "etiss/DebugSystem.h"
#include "etiss/CPUArch.h"
#include "etiss/Misc.h"
#include <iostream>
#include <cstring>
#include <fstream>

using namespace etiss;

DebugSystem::DebugSystem(){
	memset(mem,0,DEBUGSYSTEM_MEMBLOCKSIZE*2);
}

etiss::int32 DebugSystem::iread(ETISS_CPU*,etiss::uint64 addr,etiss::uint32 len){
	return RETURNCODE::NOERROR;
}
etiss::int32 DebugSystem::iwrite(ETISS_CPU*,etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len){
	etiss::log(etiss::VERBOSE,"Blocked instruction write ");
	return RETURNCODE::IBUS_WRITE_ERROR;
}
etiss::int32 DebugSystem::dread(ETISS_CPU*,etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len){
	if (addr >= DEBUGSYSTEM_MEMBLOCKSIZE*2 || addr +len > DEBUGSYSTEM_MEMBLOCKSIZE*2){
		std::cout << "Failed to read data from " << std::hex << addr << "-" << addr+len << std::dec << std::endl;
		memset(buf,0,len);
		return RETURNCODE::IBUS_READ_ERROR;
	}
	memcpy(buf,mem+addr,len);
	return RETURNCODE::NOERROR;
}
etiss::int32 DebugSystem::dwrite(ETISS_CPU*,etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len){
	if (addr >= DEBUGSYSTEM_MEMBLOCKSIZE*2 || addr +len > DEBUGSYSTEM_MEMBLOCKSIZE*2){
		std::cout << "Failed to write data to " << std::hex << addr << "-" << addr+len << std::dec << std::endl;
		return RETURNCODE::DBUS_WRITE_ERROR;
	}
	memcpy(mem+addr,buf,len);
	return RETURNCODE::NOERROR;
}

etiss::int32 DebugSystem::dbg_read(etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len){
	if (addr >= DEBUGSYSTEM_MEMBLOCKSIZE*2 || addr +len > DEBUGSYSTEM_MEMBLOCKSIZE*2){
		std::cout << "Failed to read data from " << std::hex << addr << "-" << addr+len << std::dec << std::endl;
		memset(buf,0,len);
		return RETURNCODE::IBUS_READ_ERROR;
	}
	memcpy(buf,mem+addr,len);
	/*
	std::cout << "read data from " << std::hex << addr << "-" << addr+len << " bytes: ";
	for (etiss::uint32 i = 0;i<len;i++){
		std::cout << "0x" << (unsigned)buf[i] << ", ";
	}
	std::cout << std::dec << std::endl;
	*/
	return RETURNCODE::NOERROR;
}
etiss::int32 DebugSystem::dbg_write(etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len){
	if (addr >= DEBUGSYSTEM_MEMBLOCKSIZE*2 || addr +len > DEBUGSYSTEM_MEMBLOCKSIZE*2){
		std::cout << "Failed to write data to " << std::hex << addr << "-" << addr+len << std::dec << std::endl;
		return RETURNCODE::IBUS_WRITE_ERROR;
	}
	memcpy(mem+addr,buf,len);
	/*
	std::cout << "wrote data to " << std::hex << addr << "-" << addr+len << " bytes: ";
	for (etiss::uint32 i = 0;i<len;i++){
		std::cout << "0x" << (unsigned)buf[i] << ", ";
	}
	std::cout << std::dec << std::endl;
	*/
	return RETURNCODE::NOERROR;
}
bool DebugSystem::load(etiss::uint64 addr,const char * file){
	std::ifstream in;
	in.open(file,std::ifstream::binary);
	if (!in.is_open())
		return false;
	etiss::uint8 byte;
	while (in.good()){
		byte = (etiss::uint8) in.get();
		if (in.good()){
			if (addr< DEBUGSYSTEM_MEMBLOCKSIZE*2){
				mem[addr] = byte;
			} else {
				std::cout << "ERROR: failed to load data to debug system memory: invalid address (" << std::hex << addr << std::dec << ")" << std::endl;
				in.close();
				return false;
			}
			addr++;
		}
	}
	in.close();
	return true;
}
extern void global_sync_time(uint64 time_ps);
void DebugSystem::syncTime(ETISS_CPU * cpu){
	//std::cout << "CPU time: " << cpu -> cpuTime_ps << "ps" << std::endl;
	//global_sync_time(cpu->cpuTime_ps);
}
void DebugSystem::swapEndian(unsigned align){
	etiss::uint8 buf_[8];
	etiss::uint8 * buf;
	if (align > 8){
		buf = new etiss::uint8[align];
	}
	else {
		buf = buf_;
	}
	for (int i = 0;i < DEBUGSYSTEM_MEMBLOCKSIZE*2;i+=align){
		etiss::uint8 * cur = mem+i;
		for (unsigned j = 0; j < align;j++){
			buf[j] = cur[j];
		}
		for (unsigned j = 0; j < align;j++){
			cur[align-j-1] = buf[j];
		}
	}
	if (buf != buf_)
		delete[] buf;
}
