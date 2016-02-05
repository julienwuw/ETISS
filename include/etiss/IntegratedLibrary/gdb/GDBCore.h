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

@date September 2, 2014

@version 0.1

*/
/**
	@file

	@brief

	@detail




*/
#ifndef ETISS_INCLUDE_GDB_GDBCORE_H_
#define ETISS_INCLUDE_GDB_GDBCORE_H_


#include <string>
#include "etiss/jit/CPU.h"

namespace etiss {

	namespace plugin {

		namespace gdb {

			/**
				@brief provides to architecture dependent registers as defined by gdb

				@detail gdb requires a predefined archtecture specific list of registers. Information about this list is provided by this class
			*/
			class GDBCore {
			public:
				virtual ~GDBCore();
				/**
					@brief the returned string identifies the register at the given index as defined by gdb. the returned string must match the get/setRegisterXX() functions of etiss::CPUArch
				*/
				virtual std::string mapRegister(unsigned index);
				/**
					@brief returns the index of the given register name in the list of registers as defined by gdb. max return INVALIDMAPPING if the passed name is not in the list
				*/
				virtual unsigned mapRegister(std::string name);
				/**
					@brief returns the number of registers in the gdb defined register list
				*/
				virtual unsigned mappedRegisterCount();
				/**
					@brief returns true if the values are expected to be little endian
				*/
				virtual bool isLittleEndian();
				/**
					@brief allows to calculate the index of the instruction to be executed for breakpoint checks. returns cpu->instructionPointer by default.
					@detail the OR1K architecture uses this to account for an invalid instruction pointer in case of a delay slot instruction
				*/
				virtual etiss::uint64 getInstructionPointer(ETISS_CPU * cpu);
			public:
				static const unsigned INVALIDMAPPING = (unsigned) -1;
			};

		}

	}
}

#endif
