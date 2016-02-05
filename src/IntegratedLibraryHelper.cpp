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

	@brief implements a LibraryInterface for the integrated library which is not loaded like other libraries but called directly

	@detail

*/


#include "etiss/LibraryInterface.h"


#define ETISS_LIBNAME ETISSINCLUDED


#include "etiss/helper/CPUArchLibrary.h"
#include "etiss/helper/JITLibrary.h"
#include "etiss/helper/PluginLibrary.h"

/**
	@brief LibraryInterface implementation for integrated JIT/CPUArch/Plugin implementations. wraps example implementation of library functions defined by helper/CPUArchLibrary.h,helper/JITLibrary.h,helper/PluginLibrary.h and implemented in IntegratedLibrary.cpp
*/
class IntegratedLibrary : public etiss::LibraryInterface {
public:
	IntegratedLibrary() : etiss::LibraryInterface("ETISSINCLUDED"){}
	virtual std::string versionInfo(){
        return ETISS_VERSION_FULL;
	}
	virtual unsigned countPlugins(){
		return ETISSINCLUDED_countPlugin();
	}
	virtual unsigned countCPUArchs(){
		return ETISSINCLUDED_countCPUArch();
	}
	virtual unsigned countJITs(){
		return ETISSINCLUDED_countJIT();
	}

	virtual std::string nameJIT(unsigned index){
		const char * name = ETISSINCLUDED_nameJIT(index);
		if (name != 0){
			return std::string(name);
		}
		return std::string();
	}
	virtual std::string namePlugin(unsigned index){
		const char * name = ETISSINCLUDED_namePlugin(index);
		if (name != 0){
			return std::string(name);
		}
		return std::string();
	}
	virtual std::string nameCPUArch(unsigned index){
		const char * name = ETISSINCLUDED_nameCPUArch(index);
		if (name != 0){
			return std::string(name);
		}
		return std::string();
	}

	virtual etiss::JIT * createJIT(unsigned index,std::map<std::string,std::string> options){
		return ETISSINCLUDED_createJIT(index,options);
	}
	virtual etiss::CPUArch * createCPUArch(unsigned index,std::map<std::string,std::string> options){
		return ETISSINCLUDED_createCPUArch(index,options);
	}
	virtual etiss::Plugin * createPlugin(unsigned index,std::map<std::string,std::string> options){
		return ETISSINCLUDED_createPlugin(index,options);
	}

	virtual void deleteJIT(etiss::JIT * o){
		delete o;
	}
	virtual void deleteCPUArch(etiss::CPUArch *o){
		delete o;
	}
	virtual void deletePlugin(etiss::Plugin * o){
		delete o;
	}

};

std::shared_ptr<etiss::LibraryInterface> etiss::LibraryInterface::openIntegratedLibrary(){
	return std::shared_ptr<etiss::LibraryInterface>(new IntegratedLibrary());
}
