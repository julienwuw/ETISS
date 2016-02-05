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

	@brief implementation of etiss/IntegratedLibrary/PrintInstruction.h

	@detail

*/

#include "etiss/IntegratedLibrary/PreInstructionManipulationCallback.h"

extern "C" {
    void PreInstructionManipulationCallback_callback(void * this_)
    {
    	etiss::plugin::PreInstructionManipulationCallback::Data * data_ = (etiss::plugin::PreInstructionManipulationCallback::Data*)this_;
#if DEBUG
        if (this_ == 0)
        {
            etiss::log(etiss::ERROR,"PreInstructionManipulationCallback_callback called with nullptr.");
			return;
        }
        if (data_->this_ == 0){
			etiss::log(etiss::ERROR,"PreInstructionManipulationCallback_callback called with uninitialized struct.");
        }
#endif
        ((etiss::plugin::PreInstructionManipulationCallback*)(data_->this_))->callback();
    }
}

using namespace etiss::plugin;

PreInstructionManipulationCallback::PreInstructionManipulationCallback(){
	pluginData_.state_ = 0;
	pluginData_.this_ = this;
}
PreInstructionManipulationCallback::~PreInstructionManipulationCallback(){

}

void PreInstructionManipulationCallback::initCodeBlock(etiss::CodeBlock & block)const
{
    block.fileglobalCode().insert("extern void PreInstructionManipulationCallback_callback(void *); ");
    block.functionglobalCode().insert("if ( (*(uint32_t*)(" + getPointerCode() + ")) != " + etiss::toString(pluginData_.state_) + ") return ETISS_RETURNCODE_RELOADCURRENTBLOCK;"); // add print function
}

void PreInstructionManipulationCallback::finalizeInstrSet(etiss::instr::ModedInstructionSet & mis) const
{

    mis.foreach([this](etiss::instr::VariableInstructionSet & vis)
    {
        vis.foreach([this](etiss::instr::InstructionSet & set)
        {
            set.foreach([this](etiss::instr::Instruction & instr)
            {
                instr.addCallback([this](etiss::instr::BitArray & ba, etiss::CodeSet & cs,etiss::instr::InstructionContext & ic)
                {

                    if (this->callbackAddresses().find(ic.current_address_) != this->callbackAddresses().end())
                    {
                        std::stringstream ss;

                        ss << "PreInstructionManipulationCallback_callback(";

                        ss << getPointerCode();

                        ss << ");";

                        ss << "if ( (*(uint32_t*)(" << getPointerCode() << ")) != " << etiss::toString(pluginData_.state_) << ") return ETISS_RETURNCODE_RELOADCURRENTBLOCK;";

                        cs.append(CodePart::PREINITIALDEBUGRETURNING).code() = ss.str();

                    }

                    return true;

                },0);

                if (callbackOnInstruction(instr)){

					instr.addCallback([this](etiss::instr::BitArray & ba, etiss::CodeSet & cs,etiss::instr::InstructionContext & ic)
					{


						std::stringstream ss;

						ss << "PreInstructionManipulationCallback_callback(";

						ss << getPointerCode();

						ss << ");";

						cs.append(CodePart::PREINITIALDEBUGRETURNING).code() = ss.str();

						return true;

					},0);
                }

            });
        });
    });

}


std::string PreInstructionManipulationCallback::_getPluginName() const
{
    return "PreInstructionManipulationCallback";
}

void* PreInstructionManipulationCallback::getPluginHandle()
{
    return (void*) &pluginData_;
}

