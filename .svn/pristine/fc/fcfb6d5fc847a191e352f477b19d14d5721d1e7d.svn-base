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
	
	@brief implementation of etiss/IntegratedLibrary/gdb/GDBCore.h

	@detail 

*/

#include "etiss/IntegratedLibrary/gdb/GDBCore.h"

using namespace etiss::plugin::gdb;

GDBCore::~GDBCore(){

}
std::string GDBCore::mapRegister(unsigned index){
	return "";
}
unsigned GDBCore::mapRegister(std::string name){
	return INVALIDMAPPING;
}
unsigned GDBCore::mappedRegisterCount(){
	return 0;
}
bool GDBCore::isLittleEndian(){
	return false;
}
etiss::uint64 GDBCore::getInstructionPointer(ETISS_CPU * cpu){
	return cpu->instructionPointer;
}
