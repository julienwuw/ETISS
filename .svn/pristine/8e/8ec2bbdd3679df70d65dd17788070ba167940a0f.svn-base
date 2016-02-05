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

	@brief class definition of the CPUArch implementation for an or1k processor

	@detail




*/

#ifndef ETISS_OR1KArch_OR1KArch_H_
#define ETISS_OR1KArch_OR1KArch_H_

#include "etiss/CPUArch.h"
#include "etiss/Instruction.h"
#include "OR1K.h"
#include <map>


// include etiss library interface
#define ETISS_LIBNAME OR1KArch

//#include "etiss/helper/CPUArchLibrary.h"

#include "OR1KGDBCore.h"

///TODO: implement opt_hostendianess for store/load instructions
class OR1KArch : public etiss::CPUArch {

public:

	OR1KArch();

	virtual const std::set<std::string> & getListenerSupportedRegisters();

	virtual etiss::Plugin * newTimer(ETISS_CPU * cpu);
	virtual void deleteTimer(etiss::Plugin * timer);

	virtual ETISS_CPU * newCPU();
	virtual void resetCPU(ETISS_CPU * cpu,etiss::uint64 * startpointer);
	virtual void deleteCPU(ETISS_CPU *);
	virtual std::shared_ptr<etiss::VirtualStruct> getVirtualStruct(ETISS_CPU * cpu);
    virtual void deleteVirtualStruct(etiss::VirtualStruct * stru) ;


	/**
		@return 8 (jump instruction + instruction of delay slot)
	*/
	virtual unsigned getMaximumInstructionSizeInBytes();
	/**
		@return 4
	*/
	virtual unsigned getInstructionSizeInBytes();
	/**
		@brief required headers (OR1K.h)
	*/
	virtual const std::set<std::string> & getHeaders() const;
	virtual etiss::int32 handleException(etiss::int32 code,ETISS_CPU * cpu);

	virtual void initInstrSet(etiss::instr::ModedInstructionSet & ) const;
	virtual void initCodeBlock(etiss::CodeBlock & cb) const;

	virtual etiss::InterruptVector * createInterruptVector(ETISS_CPU * cpu);
	virtual void deleteInterruptVector(etiss::InterruptVector * vec,ETISS_CPU * cpu);

	virtual etiss::plugin::gdb::GDBCore & getGDBCore();


private:
	std::set<std::string> reg32names;
	std::set<std::string> listenerSupportedRegisters_;
	std::set<std::string> headers_;
	OR1KGDBCore gdbcore_;
public:
	bool perfopt_noRangeException_; ///< performance option: if true then no range exception shall be thrown (speedup of additions etc.) @see etiss::CPUArch * OR1KArch_createCPUArch(unsigned index,std::map<std::string,std::string> options)
	bool opt_returnjump_; ///< if true then isjump will allways be false and jumps will be implemented with a return statement @see etiss::CPUArch * OR1KArch_createCPUArch(unsigned index,std::map<std::string,std::string> options)
	bool opt_hostendianness; ///< if true then no byte swapping will be done. requires the endianness of instruction/data in the memory to match host endianness @see etiss::CPUArch * OR1KArch_createCPUArch(unsigned index,std::map<std::string,std::string> options)
    bool ignore_sr_iee; ///< ignore sr iee flag
};

extern etiss::instr::InstructionCollection Processor_OR1K;
extern etiss::instr::InstructionClass OR32;
extern etiss::instr::InstructionGroup ORFPX32;
extern etiss::instr::InstructionGroup ORBIS32_I;
extern etiss::instr::InstructionGroup ORBIS32_II;

extern etiss::Plugin * getOR1200Timing(etiss::Configuration & );




#define OR1KArch_translateInvalidInstruction(CODESET) {etiss::CodePart & part = CODESET.append(etiss::CodePart::APPENDEDRETURNINGREQUIRED); part.code() = "return OR1K_ILLEGALINSTRUCTIONEXCEPTION;";}

/**
	@brief translates floating point instructions
	@see OR1KArch_fpu.cpp
*/
void translate_fpu(const etiss::uint32 instr,etiss::CodeSet & ret);

#endif
