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

#ifndef ETISS_OR1KArch_OR1KArch_H_
#define ETISS_OR1KArch_OR1KArch_H_

#include "etiss/CPUArch.h"
#include "etiss/Instruction.h"
#include "ARMv6M.h"
#include <map>



class ARMv6MArch : public etiss::CPUArch {

public:

	ARMv6MArch();

	virtual const std::set<std::string> & getListenerSupportedRegisters();

	//virtual etiss::Plugin * newTimer(ETISS_CPU * cpu);
	//virtual void deleteTimer(etiss::Plugin * timer);

	virtual ETISS_CPU * newCPU();
	virtual void resetCPU(ETISS_CPU * cpu,etiss::uint64 * startpointer);
	virtual void deleteCPU(ETISS_CPU *);
	virtual std::shared_ptr<etiss::VirtualStruct> getVirtualStruct(ETISS_CPU * cpu);



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
		virtual void compensateEndianess(ETISS_CPU * cpu,etiss::instr::BitArray & ba) const ;

	//virtual etiss::InterruptVector * createInterruptVector(ETISS_CPU * cpu);
	//virtual void deleteInterruptVector(etiss::InterruptVector * vec,ETISS_CPU * cpu);

	//virtual etiss::plugin::gdb::GDBCore & getGDBCore();


private:

	std::set<std::string> listenerSupportedRegisters_;
	std::set<std::string> headers_;


};
#endif
