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

	@brief implementation of etiss/ETISS.h except for etiss::preloadLibraries

	@detail

*/



#include "etiss/ETISS.h"
#include "etiss/fault/Stressor.h"
#include "etiss/IncludedFiles.h"

#include <csignal>
#include <cstring>
#include <functional>
#include <fstream>

#if ETISS_USE_DLSYM
#include <dlfcn.h>
#endif

using namespace etiss;

std::string etiss_defaultjit_;

std::list<std::shared_ptr<etiss::LibraryInterface> > etiss_libraries_;
std::recursive_mutex etiss_libraries_mu_;

std::set<std::string> etiss::listCPUArchs() {
	std::set<std::string> ret;
	std::lock_guard<std::recursive_mutex> lock(etiss_libraries_mu_);
	for (auto iter = etiss_libraries_.begin();iter != etiss_libraries_.end();iter++) {
		if ((*iter).get() != 0){
			if (!(*iter)->isEmpty()){
				for (unsigned i = 0;i<(*iter)->countCPUArchs();i++){
					std::string jit = (*iter)->nameCPUArch(i);
					if (ret.find(jit) != ret.end()){
						etiss::log(etiss::ERROR,"CPUArch provided by multiple libraries: \""+jit+"\"");
					} else {
						ret.insert(jit);
					}
				}
			}
		}
	}
	return ret;
}

std::set<std::string> etiss::listJITs(){
	std::set<std::string> ret;
	std::lock_guard<std::recursive_mutex> lock(etiss_libraries_mu_);
	for (auto iter = etiss_libraries_.begin();iter != etiss_libraries_.end();iter++) {
		if ((*iter).get() != 0){
			if (!(*iter)->isEmpty()){
				for (unsigned i = 0;i<(*iter)->countJITs();i++){
					std::string jit = (*iter)->nameJIT(i);
					if (ret.find(jit) != ret.end()){
						etiss::log(etiss::ERROR,"JIT provided by multiple libraries: \""+jit+"\"");
					} else {
						ret.insert(jit);
					}
				}
			}
		}
	}
	return ret;
}

std::set<std::string> etiss::listPlugins(){
	std::set<std::string> ret;
	std::lock_guard<std::recursive_mutex> lock(etiss_libraries_mu_);
	for (auto iter = etiss_libraries_.begin();iter != etiss_libraries_.end();iter++) {
		if ((*iter).get() != 0){
			if (!(*iter)->isEmpty()){
				for (unsigned i = 0;i<(*iter)->countPlugins();i++){
					std::string jit = (*iter)->namePlugin(i);
					if (ret.find(jit) != ret.end()){
						etiss::log(etiss::ERROR,"JIT provided by multiple libraries: \""+jit+"\"");
					} else {
						ret.insert(jit);
					}
				}
			}
		}
	}
	return ret;
}

std::shared_ptr<JIT> etiss::getJIT(std::string name,std::map<std::string,std::string> options){
	std::shared_ptr<JIT> jit;
	std::string ujit;
	std::lock_guard<std::recursive_mutex> lock(etiss_libraries_mu_);
	for (auto iter = etiss_libraries_.begin();iter != etiss_libraries_.end();iter++) {
		std::shared_ptr<LibraryInterface> lib = *iter;
		if (lib.get() != 0){
			if (!lib->isEmpty()){
				for (unsigned i = 0;i<lib->countJITs();i++){
					if (lib->nameJIT(i) == name){
						if (jit.get() != 0){
							etiss::log(etiss::ERROR,"JIT provided by multiple libraries: using \""+name+"\" from library \""+ujit+"\" [also provided by library \""+lib->getName()+"\"]");
						} else {
							etiss::JIT * ca = lib->createJIT(i,options);
							if (ca == 0){
								etiss::log(etiss::ERROR,"Failed to create JIT via library interface \""+lib->getName()+"\"");
							} else {
								jit = std::shared_ptr<JIT>(ca,[lib](JIT* j){lib->deleteJIT(j);});
								ujit = lib->getName();
							}
						}
					}
				}
			}
		}
	}
	return jit;
}
std::shared_ptr<CPUArch> etiss::getCPUArch(std::string name,std::map<std::string,std::string> options){
	std::shared_ptr<CPUArch> arch;
	std::string uarch;
	std::lock_guard<std::recursive_mutex> lock(etiss_libraries_mu_);
	for (auto iter = etiss_libraries_.begin();iter != etiss_libraries_.end();iter++) {
		std::shared_ptr<LibraryInterface> lib = *iter;
		if (lib.get() != 0){
			if (!lib->isEmpty()){
				for (unsigned i = 0;i<lib->countCPUArchs();i++){
					if (lib->nameCPUArch(i) == name){
						if (arch.get() != 0){
							etiss::log(etiss::ERROR,"CPU Architecture provided by multiple libraries: using \""+name+"\" from library \""+uarch+"\" [also provided by library \""+lib->getName()+"\"]");
						} else {
							etiss::CPUArch * ca = lib->createCPUArch(i,options);
							if (ca == 0){
								etiss::log(etiss::ERROR,"Failed to create CPUArch via library interface \""+lib->getName()+"\"");
							} else {
								arch = std::shared_ptr<CPUArch>(ca,[lib](CPUArch * a){lib->deleteCPUArch(a);});
								uarch = lib->getName();
							}
						}
					}
				}
			}
		}
	}
	return arch;
}

std::shared_ptr<Plugin> etiss::getPlugin(std::string name,std::map<std::string,std::string> options){
	std::shared_ptr<Plugin> arch;
	std::string uarch;
	std::lock_guard<std::recursive_mutex> lock(etiss_libraries_mu_);
	for (auto iter = etiss_libraries_.begin();iter != etiss_libraries_.end();iter++) {
		std::shared_ptr<LibraryInterface> lib = *iter;
		if (lib.get() != 0){
			if (!lib->isEmpty()){
				for (unsigned i = 0;i<lib->countPlugins();i++){
					if (lib->namePlugin(i) == name){
						if (arch.get() != 0){
							etiss::log(etiss::ERROR,"Plugin provided by multiple libraries: using \""+name+"\" from library \""+uarch+"\" [also provided by library \""+lib->getName()+"\"]");
						} else {
							etiss::Plugin * ca = lib->createPlugin(i,options);
							if (ca == 0){
								etiss::log(etiss::ERROR,"Failed to create Plugin via library interface \""+lib->getName()+"\"");
							} else {
								arch = std::shared_ptr<Plugin>(ca,[lib](Plugin * p){lib->deletePlugin(p);});
								uarch = lib->getName();
							}
						}
						break;
					}
				}
			}
		}
	}
	return arch;
}

bool etiss::loadLibrary(std::string path,std::string name){

	auto lib = etiss::LibraryInterface::openSharedLibrary(path,name);
	if (lib.get()){
        addLibrary(lib);
        return true;
	}

    return false;
}
void etiss::addLibrary(std::shared_ptr<etiss::LibraryInterface> interface){

	etiss::LibraryInterface * lif = interface.get();

	if (lif == 0){
		return;
	}

	etiss::forceInitialization();

	std::string wd = cfg().get<std::string>("etiss_wd","");
	for (int i = 0;i<lif->getFileCount();i++){
		// check if file is already present
		{
			std::ifstream tf;
			tf.open((wd+lif->getFileName(i)).c_str());
			if (tf.is_open()){
				tf.close();
				continue;
			}
		}
#if ETISS_USE_LINUX_MKDIR
		if (system((std::string("mkdir -p $(dirname \"")+wd+lif->getFileName(i)+ "\")").c_str()) != 0){
			etiss::log(etiss::WARNING,std::string("Failed to create folder of file: ")+wd+lif->getFileName(i));
		}
#else
		// NOTE the appended /../ is a hack. use with caution
		if (system((std::string("mkdir \"") + wd + lif->getFileName(i) + "/../\"").c_str()) != 0){
			if (system((std::string("mkdir -p \"") + wd + lif->getFileName(i) + "/../\"").c_str()) != 0){
				etiss::log(etiss::WARNING, std::string("Failed to create folder of file: ") + wd + lif->getFileName(i));
			}
		}
#endif
		std::ofstream f;
		f.open((wd+lif->getFileName(i)).c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
		if (!f.is_open()){
			etiss::log(etiss::ERROR,std::string("Failed to create file: ")+lif->getFileName(i));
			continue;
		}
		int filesize = lif->getFileSize(i); // get file size
		if (filesize != 0){ // there is something to write
            if (filesize<0){ // zero terminated string
                f << lif->getFileData(i);
            } else {
                f.write(lif->getFileData(i),filesize);
            }
		}

		f.flush();
		f.close();
	}
	{
		std::lock_guard<std::recursive_mutex> lock(etiss_libraries_mu_);
		etiss_libraries_.push_back(interface);
	}
	// if no default jit is present, try to use one from this library
	for (unsigned i = 0;(etiss_defaultjit_.size() <= 0) && (i<interface->countJITs());i++){

		etiss_defaultjit_ = interface->nameJIT(i);

	}
}
std::set<std::string> etiss::listLibraries(){
	std::lock_guard<std::recursive_mutex> lock(etiss_libraries_mu_);
	std::set<std::string> ret;
	for (auto iter = etiss_libraries_.begin();iter != etiss_libraries_.end();iter++){
		ret.insert((*iter)->getName() + "[" +(*iter)->versionInfo() + "]");
	}
	return ret;
}

std::set<std::string> etiss::listLibraryPrefixes(){
	std::lock_guard<std::recursive_mutex> lock(etiss_libraries_mu_);
	std::set<std::string> ret;
	for (auto iter = etiss_libraries_.begin(); iter != etiss_libraries_.end(); iter++){
		ret.insert((*iter)->getName());
	}
	return ret;
}

std::shared_ptr<etiss::JIT> etiss::getDefaultJIT() {
	return getJIT(etiss_defaultjit_);
}




// transfer controll to etiss console on SIGINT
void (*etiss_prev_SIGINT_handler)(int)  = 0;
bool etiss_SIGINT_handler_enabled = false;

void etiss_SIGINT_handler(int sig){
	if (sig == SIGINT){
		std::cout << std::endl << "\033[0;31m" << std::endl;
		///TODO etiss::transferCMDControll();
		std::cout << std::endl << "\033[0m" << std::endl;
	} else { // false handler assignment
		signal(sig,SIG_DFL);
		raise(sig);
		return;
	}
}
//__attribute__((constructor))
static void etiss_initialize_SIGINT() {
  if (!etiss_SIGINT_handler_enabled){
	  etiss_prev_SIGINT_handler = signal (SIGINT, etiss_SIGINT_handler);
	  etiss_SIGINT_handler_enabled = true;
  }
}

//__attribute__((destructor))
static void etiss_remove_SIGINT() {
  if (etiss_SIGINT_handler_enabled){
	  etiss_prev_SIGINT_handler = signal (SIGINT, etiss_prev_SIGINT_handler);
	  etiss_SIGINT_handler_enabled = false;
  }
}
/// replaces __attribute__((destructor)) in a portable way
static class helper_class_etiss_2{
public:
	~helper_class_etiss_2(){
		etiss_remove_SIGINT();
	}
} helper_class_etiss_2;



// initialize
void etiss_initialize(std::vector<std::string> args,bool forced = false){

	static std::mutex mu_;
	static bool initialized_(false);
	{
		std::lock_guard<std::mutex> lock(mu_);
		if (initialized_){
			if (!forced){
				etiss::log(etiss::WARNING,"Multiple calls to etiss::initialize");
			} else {
				return;
			}
		} else {
			if (forced){
				etiss::log(etiss::WARNING,"etiss::initialize has not been called before using ETISS library functions. Please add the line \'etiss::initialize(argc,argv);\' at the beginning of \'int main(int argc,char**argv);\'");
			}
		}
		initialized_ = true;
	}



	std::list<std::string> flaglist;
	for (auto iter = args.begin();iter != args.end();iter++){
		flaglist.push_back(*iter);
	}

	flaglist = etiss::cfg().set(flaglist);

	//log level
	{
		int ll = cfg().get<int>("loglevel",etiss::WARNING);
		if (ll >= 0 && ll <= etiss::VERBOSE){ // valid log level
			etiss::verbosity() = (Verbosity)ll;
			etiss::log(etiss::VERBOSE,"Log level set to VERBOSE");
		} else {
			etiss::verbosity() = etiss::WARNING;
			etiss::log(etiss::ERROR,"Specified log level is not valid. must range between 0 (= silent) and 5 (= verbose)");
		}
	}

	// create etiss_wd (work dir)
	cfg().makeFinal("etiss_wd"); // etiss_wd may not be changed during runtime
	if (system(std::string(std::string("mkdir ") + cfg().get<std::string>("etiss_wd", "")).c_str()) != 0)
		if (system(std::string(std::string("mkdir -p ")+cfg().get<std::string>("etiss_wd","")).c_str()) != 0)
			etiss::log(etiss::ERROR,std::string("Failed to create etiss workdir (etiss_wd): ")+cfg().get<std::string>("etiss_wd",""));

	// copy etiss C header files (needed by jits)
	if (cfg().get<bool>("copy-headers",true)){
		std::string wd = cfg().get<std::string>("etiss_wd","");
		for (int i = 0;i<(int)etiss::storedfiles::count;i++){
			// check if file already present
			{
				std::ifstream tf;
				tf.open((wd+etiss::storedfiles::names[i]).c_str());
				if (tf.is_open()){
					tf.close();
					continue;
				}
			}
#if ETISS_USE_LINUX_MKDIR
		if (system((std::string("mkdir -p $(dirname \"")+wd+etiss::storedfiles::names[i]+ "\")").c_str()) != 0){
			etiss::log(etiss::WARNING,std::string("Failed to create folder of file: ")+wd+etiss::storedfiles::names[i]);
		}
#else
		// NOTE the appended /../ is a hack. use with caution
		if (system((std::string("mkdir \"") + wd + etiss::storedfiles::names[i] + "/../\"").c_str()) != 0){
			if (system((std::string("mkdir -p \"") + wd + etiss::storedfiles::names[i] + "/../\"").c_str()) != 0){
				etiss::log(etiss::WARNING, std::string("Failed to create folder of file: ") + wd + etiss::storedfiles::names[i]);
			}
		}
#endif
			std::ofstream f;
			f.open((wd+etiss::storedfiles::names[i]).c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
			if (!f.is_open()){
				etiss::log(etiss::ERROR,std::string("Failed to create file: ")+wd+etiss::storedfiles::names[i]);
				continue;
			}
			f << etiss::storedfiles::data[i];
			f.flush();
			f.close();
		}
	}

	etiss::py::init(); // init python

	// configure console
	if (cfg().get<bool>("sigint-console",false)){
		etiss_initialize_SIGINT();
	} else {
		etiss_remove_SIGINT();
	}

	// load all found libraries
	if (cfg().get<bool>("library-loading",true)){
		preloadLibraries();
	}


	// load integrated library
	if (cfg().get<bool>("integrated-library",true)){
	    etiss::addLibrary(LibraryInterface::openIntegratedLibrary());
	}

	// check if some required files can be found
	{
		std::string path = cfg().get<std::string>("etiss_wd","./");
		std::vector<std::string> requiredFiles;

		// required files
		requiredFiles.push_back(path + "/include_c/etiss/jit/CPU.h");

		//check
		for (auto iter = requiredFiles.begin();iter!=requiredFiles.end();iter++){
			std::ifstream f(iter->c_str());
			if (!f.is_open()){
				etiss::log(etiss::WARNING,std::string("Could not find file: ")+*iter+"\n"+"\t please specify etiss_path to point to the etiss directory (e.g \"-oetiss_path /somepath/etiss/\")");
			} else {
				f.close();
			}
		}

	}

	// load fault files
	{
	    std::string faults = cfg().get<std::string>("faults.xml","");
	    if (!faults.empty()){
            std::list<std::string> ffs = etiss::split(faults,';');
            for (auto ff : ffs){
                etiss::fault::Stressor::loadXML(ff);
            }
	    }
	}

	if (cfg().get<bool>("pyconsole",false))
			etiss::py::console();


}

void etiss::initialize(std::vector<std::string> args){

	etiss_initialize(args,false);

}

void etiss::forceInitialization(){

	std::vector<std::string> args;
	etiss_initialize(args,true);

}


//__attribute__((destructor))
static void etiss_shutdown() {

	etiss::shutdown(); //TODO: verify with spec. assuming shared library close after __attribute__((destructor)) functions have been called

	// force close open libraries
	//{
	//	std::lock_guard<std::recursive_mutex> lock(etiss_libraries_mu_);
	//	etiss_libraries_.clear();
	//}

}
/// replaces __attribute__((destructor)) in a portable way
static class helper_class_etiss_1{
public:
	~helper_class_etiss_1(){
		etiss_shutdown();
	}
} helper_class_etiss_1;

bool etiss_shutdownOk = false;

void etiss::shutdown() {

	if (etiss_shutdownOk) // only on shutdown
		return;

	etiss_shutdownOk = true;

	etiss::fault::Stressor::clear();

	// unload libraries
	{

		std::list<std::weak_ptr<LibraryInterface> > libraries_weak;
		{
			std::lock_guard<std::recursive_mutex> lock(etiss_libraries_mu_);
			for (auto iter = etiss_libraries_.begin();iter != etiss_libraries_.end();iter++){
				libraries_weak.push_back(std::weak_ptr<LibraryInterface>(*iter));
			}
			etiss_libraries_.clear();
		}
		for (auto iter = libraries_weak.begin();iter != libraries_weak.end();iter++){
			std::shared_ptr<LibraryInterface> li = iter->lock();
			if (li.get() != 0){
				std::stringstream ss;
				ss << "Failed to unload library \"" << li.get()->getName() << "\": ";
				ss << li.use_count()-1 << " references " << std::endl;
				etiss::log(etiss::ERROR,ss.str());
			}
		}
	}

	// check for existing cpu core instances
	{
		std::list<std::string> cores = CPUCore::list();
		if (cores.size() > 0){
			for (auto iter = cores.begin();iter != cores.end();iter++){
				etiss::log(etiss::ERROR,std::string("CPU core has not been deleted before etiss::shutdown() call: ")+*iter);
			}
		}
	}


	etiss::py::shutdown();
	
	

}

/**
	@brief check if etiss::shutdown() was called before exiting main.
*/
//__attribute__((destructor))
static void etiss_check_shutdown() {
	if (!etiss_shutdownOk){
		etiss::log(etiss::ERROR,"To prevent segmentation faults it is neccessary to call \"etiss::shutdown();\" at the end of main and free any resource acquired through ETISS.");
	}
}
/// replaces __attribute__((destructor)) in a portable way
static class helper_class_etiss_3{
public:
	~helper_class_etiss_3(){
		etiss_check_shutdown();
	}
} helper_class_etiss_3;



etiss::Initializer::~Initializer(){
	etiss::shutdown();
}


std::string etiss::errorMessage(etiss::int32 code,CPUArch * arch){
	if (code <= 0){ // global code
		const char * msg = etiss::RETURNCODE::getErrorMessages()[code];
		if (msg == 0)
			return std::string();
		return std::string(msg);
	} else { // cpu arch dependent code
		if (arch != 0){
			std::string ret = arch->getName() + ": ";
			///TODO: cpu arch error message function
			return ret;
		} else {
			return "Unknown CPU architecture dependent error code.";
		}
	}
}

