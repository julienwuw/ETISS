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

extern "C"{
	int pi_6cac = 0;
}

#include "etiss/IntegratedLibrary/PrintInstruction.h"
#include "etiss/CPUArch.h"

using namespace etiss::plugin;

void PrintInstruction::initCodeBlock(etiss::CodeBlock & block)const{
	block.fileglobalCode().insert("extern void PrintInstruction_print(const char *,uint64_t);"); // add print function
}

void PrintInstruction::finalizeInstrSet(etiss::instr::ModedInstructionSet & mis) const {

	mis.foreach([](etiss::instr::VariableInstructionSet & vis){ vis.foreach([](etiss::instr::InstructionSet & set){ set.foreach([](etiss::instr::Instruction & instr){
			instr.addCallback([&instr](etiss::instr::BitArray & ba, etiss::CodeSet & cs,etiss::instr::InstructionContext & ic){

				std::stringstream ss;

				ss << "PrintInstruction_print(\"";

				ss << "0x" << std::hex << std::setfill('0') << std::setw(16) << ic.current_address_ << ": ";
	
				ss << instr.printASM(ba);

				ss << "\\n";
				
				ss << "\",cpu->instructionPointer);\n";
				

				cs.append(CodePart::INITIALREQUIRED).code() = ss.str();

				return true;

			},0);
	});});});

}


std::string PrintInstruction::_getPluginName() const{
	return "PrintInstruction";
}

void* PrintInstruction::getPluginHandle(){
	return nullptr;
}

extern "C" {
	void PrintInstruction_print(const char * c,uint64_t addr){
		std::cout << c;
		if (addr == 0x6cac){
			//std::cout << "TCOUNT: " << std::dec << ++pi_6cac << "\n";
		}
	}
}
