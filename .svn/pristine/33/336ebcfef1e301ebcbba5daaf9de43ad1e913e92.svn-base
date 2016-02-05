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

	@brief implementation of etiss::preloadLibraries

	@detail

*/


#include <dlfcn.h>

#include "etiss/ETISS.h"
#include "etiss/config.h"

using namespace etiss;

#include <string>
#include <sstream>
#include <vector>
#include <fstream>


using namespace std;

namespace etiss {

	std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	    std::stringstream ss(s);
	    std::string item;
	    while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	    }
	    return elems;
	}

}


static bool loadLibraryList(const std::string & path){
	bool ret = false;
    ifstream lcfg((path+"/list.txt").c_str());
	if (lcfg.is_open()){
		string line;
		while ( getline (lcfg,line) )
		{
			//std::cout << "Line: " << line << std::endl;
			if (line.find(',') == std::string::npos){ // relative path
				if (etiss::loadLibrary(path,line))
					ret = true;
			} else { // absolute path 
				vector<string> def;
				etiss::split(line,',',def);
				if (def.size() == 3){
					if (string(def[0])==string(def[2]) && def[1].length() > 0 && def[2].length() > 0 ){
						if (etiss::loadLibrary(string(def[1]),string(def[2])))
							ret = true;
					} else {
						etiss::log(etiss::ERROR,"Invalid line in plugin list file",line);
					}
				} else {
					etiss::log(etiss::ERROR,"Invalid line in plugin list file",line);
				}
			}
		}
		lcfg.close();
	} else {
        etiss::log(etiss::ERROR,std::string("Failed to open file: ")+(path+"/list.txt"));
	}
	return ret;
}

bool etiss_preload_libraries = false;

void etiss::preloadLibraries(){

	if (etiss_preload_libraries){
		return;
	} else {
		etiss_preload_libraries = true;
	}
	
	loadLibraryList(std::string(ETISS_INSTALL_DIR)+"/lib/plugins/");
    
#if ETISS_USE_DLADDR
    // search for list.tx relative to this library
    Dl_info dl_info;
    if (dladdr((void *)etiss::preloadLibraries, &dl_info)){ 
    	if (dl_info.dli_fname){
    		size_t pos = std::string(dl_info.dli_fname).find_last_of('/');
    		if (pos != std::string::npos){
    			//std::cout << "LIBRARY: " << std::string(dl_info.dli_fname).substr(0,pos) << std::endl << std::endl;
	    		loadLibraryList(std::string(dl_info.dli_fname).substr(0,pos)+"/plugins/");
    		}
    	}    
    }
#endif


	std::string etisspath = etiss::cfg().get<std::string>("etiss_wd","~/");

	// check if make file exists
	ifstream makeR("./Printlibs.mk");
	if (makeR.is_open()){
		makeR.close();
	} else {	// create make file
		ofstream make("./Printlibs.mk");
		if (make.is_open()){
			make << "# Copyright (c) 2014 Institute for Electronic Design Automation, TU Munich\n"
				"# \n"
				"# \tThe above copyright notice and this permission notice shall be included in\n"
				"# \tall copies or substantial portions of the Software.\n"
				"# \n"
				"# \tTHE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
				"# \tIMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
				"# \tFITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n"
				"# \tAUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"
				"# \tLIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
				"# \tOUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN\n"
				"# \tTHE SOFTWARE.";
			make << "\n\n";
			make << "LIBS__=$(wildcard lib*.so)\n";
			make << "\n";
			make << "LIBS__+=$(wildcard ArchImpl/*/lib*.so)\n";
			make << "\n";
			make << "LIBS__+=$(wildcard JITImpl/*/lib*.so)\n";
			make << "\n";
			make << "LIBS__+=$(wildcard PluginImpl/*/lib*.so)\n";
			make << "\n";
			make << "LIBS__+=$(wildcard "<<etisspath<<"/ArchImpl/*/lib*.so)\n";
			make << "\n";
			make << "LIBS__+=$(wildcard "<<etisspath<<"/JITImpl/*/lib*.so)\n";
			make << "\n";
			make << "LIBS__+=$(wildcard "<<etisspath<<"/PluginImpl/*/lib*.so)\n";
			make << "\n";
			make << "LIBS__+=$(foreach dir,$(PATH::= ),$(wildcard $(dir)/ArchImpl/*/lib*.so))\n";
			make << "\n";
			make << "LIBS__+=$(foreach dir,$(PATH::= ),$(wildcard $(dir)/JITImpl/*/lib*.so))\n";
			make << "\n";
			make << "LIBS__+=$(foreach dir,$(PATH::= ),$(wildcard $(dir)/PluginImpl/*/lib*.so))\n";
			make << "\n";
			make << "LIBS_=$(sort $(LIBS__))\n";
			make << "\n";
			make << "LIBS=$(filter-out libETISS.so , $(LIBS_))\n";
			make << "\n";
			make << ".PHONY: all\n";
			make << "all: printlibs\n";
			make << "\n";
			make << ".PHONY: $(LIBS)\n";
			make << "$(LIBS):\n";
			make << "\t@echo $(patsubst lib%.so,%,$(notdir $@)),$(realpath $(dir $@)),$(patsubst lib%.so,%,$(notdir $@)) #write library name 2 times for output verification\n";
			make << "\n";
			make << ".PHONY: printlibs\n";
			make << "printlibs: $(LIBS)\n";
			make << "\n";
			make.close();
		} else {
			// failure
		}
	}

	// run makefile
	int rc = system("make --no-print-directory -f ./Printlibs.mk > ./ETISSLibraries.cfg");

	if (rc != 0) {
		std::cout << "Warning: failed to run \"make --no-print-directory -f ./Printlibs.mk > ./ETISSLibraries.cfg\"" << std::endl;
	}

	// read output
	ifstream lcfg("./ETISSLibraries.cfg");
	if (lcfg.is_open()){
		string line;
		while ( getline (lcfg,line) )
		{
			//std::cout << "Line: " << line << std::endl;
			vector<string> def;
			etiss::split(line,',',def);
			if (def.size() == 3){
				if (string(def[0])==string(def[2]) && def[1].length() > 0 && def[2].length() > 0 ){
					etiss::loadLibrary(string(def[1]),string(def[2]));
				}
			}
		}
		lcfg.close();
	}

    

}



