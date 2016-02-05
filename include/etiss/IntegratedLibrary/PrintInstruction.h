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
#include "etiss/Plugin.h"


namespace etiss {

	namespace plugin {

		/**
			@brief a simple plugin that prints the instruction and address when an instruction is executed
		*/
		class PrintInstruction : public etiss::TranslationPlugin{
		public:
			virtual void finalizeInstrSet(etiss::instr::ModedInstructionSet & ) const;
			virtual void initCodeBlock(etiss::CodeBlock & block)const;
			virtual std::string _getPluginName() const;
			virtual void* getPluginHandle();

		};

	}

}
