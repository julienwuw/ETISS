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

	@brief example implementation of a dynamic library interface that is used to provide access to integrated plugins. Other dynamic libraries should be implemented like this

	@detail

*/


#define ETISS_LIBNAME ETISSINCLUDED

#include "etiss/helper/CPUArchLibrary.h"
#include "etiss/helper/JITLibrary.h"
#include "etiss/helper/PluginLibrary.h"

#include "etiss/LibraryInterface.h"

#include "etiss/IntegratedLibrary/errorInjection/Plugin.h"
#include "etiss/IntegratedLibrary/gdb/GDBServer.h"
#include "etiss/IntegratedLibrary/PrintInstruction.h"
#include "etiss/IntegratedLibrary/Logger.h"

extern "C" {

// implement version function
ETISS_LIBRARYIF_VERSION_FUNC_IMPL

unsigned ETISSINCLUDED_countJIT(){
	return 0;
}

unsigned ETISSINCLUDED_countCPUArch(){
	return 0;
}

unsigned ETISSINCLUDED_countPlugin(){
	return 4;
}


const char *  ETISSINCLUDED_nameJIT(unsigned index){
	return 0;
}

const char *  ETISSINCLUDED_nameCPUArch(unsigned index){
	return 0;
}

const char *  ETISSINCLUDED_namePlugin(unsigned index){
	switch (index){
	case 0:
		return "BlockAccurateHandler";
	case 1:
		return "gdbserver";
	case 2:
		return "PrintInstruction";
	case 3:
		return "Logger";
	}
	return 0;
}

etiss::JIT * ETISSINCLUDED_createJIT(unsigned index,std::map<std::string,std::string> options){
	return 0;
}

etiss::CPUArch * ETISSINCLUDED_createCPUArch(unsigned index,std::map<std::string,std::string> options){
	return 0;
}

etiss::Plugin * ETISSINCLUDED_createPlugin(unsigned index,std::map<std::string,std::string> options){
	switch (index) {
	case 0:
	{
		/// expected option format: -rREGISTERNAME -> FILEPATH (e.g. -rR4 -> /home/you/registerErrors.txt)
		etiss::plugin::errorInjection::BlockAccurateHandler * ret = new etiss::plugin::errorInjection::BlockAccurateHandler();
		for (auto iter = options.begin();iter != options.end();iter++){
			if (iter->first.length()>2 && iter->first[0] == '-' && iter->first[1] == 'r'){
				std::string regname = iter->first.substr(2);
				ret->parseFile(iter->second,regname);
			} else {
				etiss::log(etiss::WARNING,std::string("IntegratedLibrary: failed to parse option for BlockAccurateHandler: ")+iter->first+"->"+iter->second);
			}
		}
		return ret;
	}
	case 1:
		return etiss::plugin::gdb::Server::createTCPServer(options);
	case 2:
		return new etiss::plugin::PrintInstruction();
	case 3:
		etiss::Configuration cfg;
		cfg.config() = options;
		return new etiss::plugin::Logger(cfg.get<uint64_t>("logaddr",0x80000000),cfg.get<uint64_t>("logmask",0xF0000000));
	}
	return 0;
}

void ETISSINCLUDED_deleteJIT(etiss::JIT *o){
	delete o;
}

void ETISSINCLUDED_deleteCPUArch(etiss::CPUArch *o){
	delete o;
}

void ETISSINCLUDED_deletePlugin(etiss::Plugin *o){
	delete o;
}

}

// not part of the example implementation
unsigned etiss::LibraryInterface::getCurrentLibraryVersion(){
	return ETISSINCLUDED_etissversion();
}
