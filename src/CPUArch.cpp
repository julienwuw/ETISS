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

	@brief implementation of etiss/CPUArch.h

	@detail

*/
#include "etiss/CPUArch.h"

#include <iostream>



using namespace etiss;

CPUArchRegListenerInterface::~CPUArchRegListenerInterface(){}

CPUArchCPUManipulation::~CPUArchCPUManipulation(){}



etiss::Plugin * CPUArchDefaultPlugins::newTimer(ETISS_CPU * cpu){ // disfunctional implementation
	return 0;
}

void CPUArchDefaultPlugins::deleteTimer(etiss::Plugin * timer){ // disfunctional implementation
	delete timer;
}

CPUArch::CPUArch(std::string archname) : archname_(archname) {}

CPUArch::~CPUArch(){}

std::string CPUArch::getArchName() const{
	return archname_;
}


bool CPUArch::unlikelyInstruction(etiss::uint8* instr,unsigned length,bool & ismetainstruction){ // simple implementation that return 0 if the data is 0
	ismetainstruction = false;
	while (length >= 4){
		if (*(etiss::uint32*)instr != 0)
			return false;
		instr += 4;
		length -= 4;
	}
	while (length > 0){
		if (*instr != 0)
			return false;
		instr += 1;
		length -= 1;
	}
	return true;
}

std::string CPUArch::getBlockGlobalCode(){
	return "";
}

unsigned CPUArch::getMaximumInstructionsPerMetaInstruction(){
	return getMaximumInstructionSizeInBytes()/getInstructionSizeInBytes(); ///TODO update to remove deprecated function
}

unsigned CPUArch::getSuperInstructionCount(){
	return 1;
}

etiss::int32 CPUArch::handleException(etiss::int32 code,ETISS_CPU *cpu){ // disfunctional implementation
	return code;
}

etiss::InterruptVector * CPUArch::createInterruptVector(ETISS_CPU * cpu){ // disfunctional implementation
	return (etiss::InterruptVector *) 0;
}
void CPUArch::deleteInterruptVector(etiss::InterruptVector * vec,ETISS_CPU * cpu){ // disfunctional implementation
	// allow memory leak
}

etiss::plugin::gdb::GDBCore & CPUArch::getGDBCore(){ // disfunctional implementation
	return gdbcore_;
}

std::string CPUArch::getIncludePath(){
	return etiss::cfg().get<std::string>("etiss_wd","")+"Arch/"+getName()+"/";
}

std::string CPUArch::_getPluginName() const{
	return getName();
}

static void CPUArch_finalizeInstrSet(etiss::instr::InstructionSet * set){
	if (set == nullptr)
		return;
	set->foreach([](etiss::instr::Instruction & instr){
		if (((uint32_t)instr.presentBuiltinGroups() & (uint32_t)etiss::instr::Instruction::BUILTINGROUP::CPUTIMEUPDATE) == 0){ // update time
			instr.addCallback([](etiss::instr::BitArray &,etiss::CodeSet &cs,etiss::instr::InstructionContext &){
				CodePart & cp = cs.prepend(CodePart::INITIALREQUIRED);
				cp.getAffectedRegisters().add("cpuTime_ps",64);
				cp.code() = "cpu->cpuTime_ps += cpu->cpuCycleTime_ps;";
				return true;
			},(uint32_t)etiss::instr::Instruction::BUILTINGROUP::CPUTIMEUPDATE);
		}
		///TODO? ensure instruction pointer update
	});
}

void CPUArch::finalizeInstrSet(etiss::instr::ModedInstructionSet & mis) const{
	mis.foreach([](etiss::instr::VariableInstructionSet & vis){vis.foreach([](etiss::instr::InstructionSet & set){ CPUArch_finalizeInstrSet(&set) ;});});
}

void CPUArch::compensateEndianess(ETISS_CPU * cpu,etiss::instr::BitArray & ba) const{
	ba.recoverFromEndianness(4,etiss::_BIG_ENDIAN_);
}

extern "C" {

	void ETISS_signalChangedRegisterValue(ETISS_CPU* cpu,const char * registerName){
		CPUArch::signalChangedRegisterValue(cpu,registerName);
	}

}





