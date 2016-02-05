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

@date July 28, 2014

@version 0.1

*/
/**
	@file

	@brief contains a simple plugin to print instructions

	@detail

*/
#ifndef ETISS_PLUGIN_PREINSTRUCTIONMANIPULATIONCALLBACK_H_
#define ETISS_PLUGIN_PREINSTRUCTIONMANIPULATIONCALLBACK_H_

#include "etiss/Plugin.h"
#include "etiss/Instruction.h"

namespace etiss {

	namespace plugin {

		/**
			@brief a simple plugin that prints the instruction and address when an instruction is executed
		*/
		class PreInstructionManipulationCallback : public etiss::TranslationPlugin{
		public:
			struct Data {
				uint32_t state_; // must be first field to allow pointer cast to uint32_t* for direct acess; the state is increased whenever a change is made
				void * this_;
			};
		private:
			Data pluginData_;
			std::set<uint64_t> caddrset_;
		public:
			PreInstructionManipulationCallback();
			~PreInstructionManipulationCallback();
			/// implement this callback to manipulate the cpu be fore executing the defined instructions at the defined address
			virtual void callback() = 0;

			/// implement to return true to call PreInstructionManipulationCallback::callback whenever that instruction is executed. used by finalizeInstrSet
			inline virtual bool callbackOnInstruction(etiss::instr::Instruction & instr) const { return false; }

			/// call to add an address at which callback should be called upon execution. May be changed during execution.please not that only aligned addresses will have an effect.
			inline virtual void addCallbackAddress(uint64_t addr){
				caddrset_.insert(addr);
				pluginData_.state_++;
			}
			inline virtual void removeCallbackAddress(uint64_t addr){
				caddrset_.erase(addr);
				pluginData_.state_++;
			}

			inline const std::set<uint64_t> & callbackAddresses() const {return caddrset_;}

			virtual void finalizeInstrSet(etiss::instr::ModedInstructionSet & ) const;
			virtual void initCodeBlock(etiss::CodeBlock & block)const;
			virtual std::string _getPluginName() const;
			virtual void* getPluginHandle();
		};

	}

}

#endif

