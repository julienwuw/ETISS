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

	@brief implements etiss/Plugin.h

	@detail

*/

#include "etiss/Plugin.h"

using namespace etiss;

Plugin::Plugin(unsigned type) : plugin_cpu_(nullptr),plugin_system_(nullptr),plugin_arch_(nullptr),plugin_core_(nullptr),type_(type),name_(""),tplugin_(0),splugin_(0),cplugin_(0),rplugin_(0),trplugin_(0){}
Plugin::~Plugin(){}

void Plugin::init(ETISS_CPU * cpu,ETISS_System * system,CPUArch * arch){

}
void Plugin::cleanup(){

}

InterruptListenerPlugin::InterruptListenerPlugin() {
	this->type_ |= Plugin::INTERRUPTLISTENER;
	this->tplugin_ = this;
}

InterruptListenerPlugin::~InterruptListenerPlugin(){

}

TranslationPlugin::TranslationPlugin(){
	this->type_ |= Plugin::TRANSLATION;
	this->trplugin_ = this;
}
TranslationPlugin::~TranslationPlugin(){

}
void TranslationPlugin::initInstrSet(etiss::instr::ModedInstructionSet & ) const{

}
void TranslationPlugin::finalizeInstrSet(etiss::instr::ModedInstructionSet & ) const{

}
void TranslationPlugin::initCodeBlock(etiss::CodeBlock & ) const {

}
void TranslationPlugin::finalizeCodeBlock(etiss::CodeBlock & ) const {

}

void * TranslationPlugin::getPluginHandle(){
	return this;
}

std::string TranslationPlugin::getPointerCode() const{
	return pointerCode;
}


CoroutinePlugin::CoroutinePlugin(){
	this->type_ |= Plugin::COROUTINE;
	this->cplugin_ = this;
}
CoroutinePlugin::~CoroutinePlugin(){

}
void CoroutinePlugin::executionEnd(int32_t code){

}

SystemWrapperPlugin::SystemWrapperPlugin() {
	this->type_ |= Plugin::SYSTEMWRAPPER;
	this->splugin_ = this;
}
SystemWrapperPlugin::~SystemWrapperPlugin(){

}

RegisterDevicePlugin::RegisterDevicePlugin(){
	this->type_ |= Plugin::REGISTERDEVICE;
	this->rplugin_ = this;
}
RegisterDevicePlugin::~RegisterDevicePlugin(){

}
