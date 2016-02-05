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

@date July 24, 2014

@version 0.1

*/
/**
	@file

	@brief contains the basic cpu state structure with a instruction pointer and time parameters. Take special care with alignment of structure members

	@detail

*/

#ifndef ETISS_INCLUDE_JIT_CPU_H_
#define ETISS_INCLUDE_JIT_CPU_H_

#include "etiss/jit/types.h"

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 1) // NEVER ALLOW ALIGNMENT OF STRUCTURE MEMBERS
	/**
		@brief basic cpu state structure needed for execution of any cpu architecture.

		@detail <pre>
			to use this structure for an architecture it should be customized like this:
				#pragma pack(push, 1) // important!
				struct YOUR_CPU {
					ETISS_CPU cpu;

					etiss_uint32 your_registers[16];

					[...]

				};
				#pragma pack(pop) // undo changes
			now any pointer to YOUR_CPU can be directly casted to EITSS_CPU and back [YOUR_CPU ycpu; ETISS_CPU * cpu = (ETISS_CPU *) &ycpu; YOUR_CPU * ycpuPtr = (YOUR_CPU *) cpu;]
			it is guaranteed that the cpu pointer passed to generated code or functions of a CPUArch implementation was allocated by that CPUArch and can therefore be casted without additional checks.
			</pre>
	*/
	struct ETISS_CPU {

		etiss_uint64 instructionPointer; ///< pointer to next instruction. NOTE: not neccessarily the instruction address (e.g instruction minimal size: 4; instruction pointer: 2  -> instruction address: 2*4)

		etiss_uint64 cpuTime_ps;	///< simulation time of cpu

		etiss_uint64 cpuCycleTime_ps;	///< frequency of the cpu. use to allign e.g. memory delays

		void * _etiss_private_handle_; ///< private helper handle for plugins

		etiss_uint32 mode;	///< instruction set mode of the processor

	};
#pragma pack(pop)

	typedef struct ETISS_CPU ETISS_CPU;

	extern void ETISS_signalChangedRegisterValue(ETISS_CPU* cpu,const char * registerName); // implemented in CPUArch.cpp


#ifdef __cplusplus
}
#endif

#endif
