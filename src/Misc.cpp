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

	@brief implements etiss/Misc.h

	@detail

*/

#define _CRT_SECURE_NO_WARNINGS 1

#include "etiss/Misc.h"

#include <iterator>
#include <regex>
#include <string>
#include <cstring>

using namespace etiss;


std::string etiss::toString(const Verbosity & val){
	switch (val){
	case SILENT:
		return "General";
	case FATALERROR:
		return "Fatal Error";
	case ERROR:
		return "Error";
	case WARNING:
		return "Warning";
	case INFO:
		return "Info";
	case VERBOSE:
		return "Verbose";
	default:
		return "INVALID_VERBOSITY_LEVEL";
	}
}

std::list<std::string> etiss::split(const std::string & str,std::function<size_t(const std::string & /**<str*/,size_t /**<from*/,size_t & /**<seperatorsize*/)> findsplit){
	std::list<std::string> ret;
	size_t find = 0;
	while (true){
		size_t sepsize = std::string::npos;
		size_t tmpfind = findsplit(str,find,sepsize);
		if (tmpfind >= find && tmpfind != std::string::npos){
			ret.push_back(str.substr(find,tmpfind-find));
			find = tmpfind+sepsize;
		} else {
			if (str.size()>find){
				ret.push_back(str.substr(find));
			}
			break;
		}

	}
	return ret;
}

Verbosity etiss_verbosity = etiss::INFO; ///< verbosity level variable

Verbosity & etiss::verbosity(){
	return etiss_verbosity;
}

void etiss::log(Verbosity level,std::string msg){
	if (level<=etiss_verbosity){
		std::cout << "ETISS: " << etiss::toString(level) << ": " << msg << std::endl;
	}
	if (level == FATALERROR){
        abort();
	}
}
void etiss::logC(Verbosity level,std::function<std::string(void)> msgGen){
	if (level<=etiss_verbosity){
		etiss::log(level,msgGen());
	}
}

std::vector<std::string> etiss::parseCommands(const std::string & cmdline){

	std::vector<std::string> ret;

	std::string tmp;
	unsigned state = 0;
	for (unsigned pos = 0;pos<cmdline.length();pos++){
		while (true){
			switch(state){
			case 0:
				switch (cmdline[pos]){
				case '\'':
				case '\"':
					state = 1;
				case ' ':
				case '\t':
					break;
				default:
					state = 2;
					continue;
				}
				break;
			case 1:
				switch (cmdline[pos]){
				case '\'':
				case '\"':
					ret.push_back(tmp);
					tmp = "";
					state = 0;
					break;
				case '\\':
					if (pos+1<cmdline.length()){
						pos++;
						tmp = tmp + cmdline[pos];
					}
					break;
				default:
					tmp = tmp + cmdline[pos];
					break;
				}
				break;
			case 2:
				switch (cmdline[pos]){
				case ' ':
				case '\t':
					ret.push_back(tmp);
					tmp = "";
					state = 0;
					break;
				case '\\':
					if (pos+1<cmdline.length()){
						pos++;
						tmp = tmp + cmdline[pos];
					}
					break;
				default:
					tmp = tmp + cmdline[pos];
					break;
				}
				if (pos+1>=cmdline.length()){
					ret.push_back(tmp);
					tmp = "";
				}
				break;
			default:
				std::cerr << "ERROR: etiss::parseCommand(1) parser failed" << std::endl;
				break;
			}
			break;
		}
	}

	return ret;

}

static std::string etiss_getenv_home(){
	// unix
	{
		const char * ptr = getenv("HOME");
		if (ptr && (strlen(ptr) > 0))
			return ptr;
	}
	// windows
	{
		const char * ptr1 = getenv("HOMEDRIVE");
		const char * ptr2 = getenv("HOMEPATH");
		if (ptr1 && ptr2){
			std::string ret(ptr1);
			ret = ret + ptr2;
			if (ret.size() > 0)
				return ret;
		}
	}
	etiss::log(etiss::ERROR, "Failed to get HOME environment variable. please set this variable to a read/write/(execute) enabled home folder.");
	return "";
}

etiss::Configuration::Configuration(){
	helpers_["etiss_wd"] = [](std::string s)->std::string{
		if (s.size() <= 0)
			s = ("~/.etiss/" ETISS_VERSION_INTERFACE "/");
		if (s[0] == '~'){
			s = etiss_getenv_home() + s.substr(1);
		}
		return s;
	};
	set("etiss_wd","");
}
etiss::Configuration::Configuration(std::string args){
	helpers_["etiss_wd"] = [](std::string s){
		if (s.size() <= 0)
			s = ("~/.etiss/" ETISS_VERSION_INTERFACE "/");
		if (s[0] == '~'){
			s = etiss_getenv_home() + s.substr(1);
		}
		return s;
	};
	std::vector<std::string> vec = etiss::parseCommands(args);
	std::list<std::string> list;
	list.insert(list.end(),vec.begin(),vec.end());
	set("etiss_wd","");
	set(list);
}
static bool etiss_cfg_inConstructor = false;
etiss::Configuration::Configuration(const std::list<std::string> & args){
	if (etiss_cfg_inConstructor){
		helpers_["etiss_wd"] = [](std::string s){
			if (s.size() <= 0)
				s = ("~/.etiss/" ETISS_VERSION_INTERFACE "/");
			if (s[0] == '~'){
				s = etiss_getenv_home() + s.substr(1);
			}
			return s;
		};
		set("etiss_wd","");
		set(args);
	}
}


std::map<std::string,std::string> & etiss::Configuration::config(){
	return cfg_;
}

namespace etiss {

template<> std::string Configuration::get<std::string>(const std::string & key,std::string default_,bool * default_used ){
	{
		std::lock_guard<std::mutex> lock(mu_);
		auto find = cfg_.find(key);
		if (find != cfg_.end()){
			if (default_used)
				*default_used = false;
			return find->second;
		}
	}

	if (this != &etiss::cfg()) { // use global config
		etiss::log(etiss::VERBOSE,std::string("using global configuration for key: ")+key);
		return etiss::cfg().get<std::string>(key,default_,default_used);
	} else {
		if (default_used)
			*default_used = true;
		return default_;
	}

}

template<> bool Configuration::get<bool>(const std::string & key,bool default_,bool * default_used ) {
	std::string val = get<std::string>(key,default_?"true":"false",default_used);
	// requires c++11 support
	try {
		std::regex rtrue("(\\s*[tT][rR][uU][eE]\\s*)|(\\s*[1-9][0-9]*\\s*)|(\\s*[oO][nN]\\s*)");
		std::regex rfalse("(\\s*[fF][aA][lL][sS][eE]\\s*)|(\\s*0+\\s*)|(\\s*[oO][fF][fF]\\s*)");
		if (std::regex_match(val.begin(),val.end(),rtrue)){
			return true;
		}
		if (std::regex_match(val.begin(),val.end(),rfalse)){
			return false;
		}
	} catch (const std::regex_error& e) {
		static bool error_printed = false;
		if (!error_printed) {
			etiss::log(etiss::ERROR,std::string("etiss::Configuration::get<bool>: ")+e.what());
			error_printed = true;
		}
		// simple fallback
		if (val == "true" || val == "1" || val == "on"){
			return true;
		}
		if (val == "false" || val == "0" || val == "off"){
			return false;
		}
	}




	etiss::log(etiss::VERBOSE,std::string("failed to parse value (")+val+") of configuration key ("+key+").");
	return default_;
}

template<> int Configuration::get<int>(const std::string & key,int default_,bool * default_used ) {
	std::string val = get<std::string>(key,toString(default_),default_used);
	try {
		return std::stoi(val,0,0); //see doc of std::stoi for last 0 parameter
	} catch (...) {
		if (default_used)
			*default_used = true;
		etiss::log(etiss::VERBOSE,std::string("failed to parse value (")+val+") of configuration key ("+key+").");
		return default_;
	}

}

template<> uint64_t Configuration::get<uint64_t>(const std::string & key,uint64_t default_,bool * default_used ){
	std::string val = get<std::string>(key,toString(default_),default_used);
	try {
		return std::stoull(val,0,0); //see doc of std::stoull for last 0 parameter
	} catch (...) {
		if (default_used)
			*default_used = true;
		etiss::log(etiss::VERBOSE,std::string("failed to parse value (")+val+") of configuration key ("+key+").");
		return default_;
	}

}

}

bool etiss::Configuration::debug(){
	return get<bool>("debug",false);
}

void etiss::Configuration::remove(const std::string & key){
	std::lock_guard<std::mutex> lock(mu_);
	if (final_.find(key) != final_.end())
		return;
	cfg_.erase(key);
}

bool etiss::Configuration::isSet(std::string key){
	std::lock_guard<std::mutex> lock(mu_);
	return cfg_.find(key) != cfg_.end();
}

std::list<std::string> etiss::Configuration::set(const std::list<std::string> & args){
	std::list<std::string> ret;
	for (auto iter = args.begin();iter!=args.end();iter++){
		const std::string & p = *iter;
		bool used = false;
		if (p.length() > 2){
			if (p[0] == '-' && p[1] == 'f'){
				used = true;

				size_t epos = p.find_first_of('=');

				if (p.length() > 5 && p[2] == 'n' && p[3] == 'o' && p[4] == '-'){
					if (epos == std::string::npos){
						std::string tmp = p.substr(5);
						set<std::string>(tmp,"false");
						etiss::log(etiss::VERBOSE,std::string("CONFIG: set ") + tmp + " to false");
					} else { // unusual case. assuming option shall be erased. value after '=' is ignored
						std::string tmp = p.substr(5,epos-5);
						remove(tmp);
						etiss::log(etiss::VERBOSE,std::string("CONFIG: removed ") + tmp );
					}
				} else {
					if (epos == std::string::npos){
						std::string tmp = p.substr(2);
						set<std::string>(tmp,"true");
						etiss::log(etiss::VERBOSE,std::string("CONFIG: set ") + tmp + " to true");
					} else {
						std::string tmp = p.substr(2,epos-2);
						std::string tval = p.substr(epos+1);
						set<std::string>(tmp,tval);
						etiss::log(etiss::VERBOSE,std::string("CONFIG: set ") + tmp + " to " + tval);
					}
				}
			}
			if (p[0] == '-' && p[1] == 'o'){
				used = true;
				std::string tmp = p.substr(2);
				iter++;
				if (iter != args.end()){
					set<std::string>(tmp,*iter);
				} else {
					etiss::log(etiss::WARNING,std::string("Expected option value after "+p));
				}
			}
		}
		if (!used){
			ret.push_back(p);
		}
	}
	return ret;
}

std::map<std::string,std::string> etiss::Configuration::listFullConfiguration(){
	if (this != &etiss::cfg()){
		std::map<std::string,std::string> ret = etiss::cfg().cfg_; // copy global config

		//apply local config
		for (auto iter = cfg_.begin();iter != cfg_.end();iter++){
			ret[iter->first] = iter->second;
		}

		return ret;
	} else {
		return cfg_;
	}
}

void etiss::Configuration::makeFinal(const std::string & key){
	std::lock_guard<std::mutex> lock(mu_);
	final_.insert(key);
}
	void etiss::Configuration::announce(std::string key,std::string type,std::string values,std::string description){
		std::lock_guard<std::mutex> lock(mu_);
		announced_[key] = std::tuple<std::string,std::string,std::string>(type,values,description);
	}
	std::map<std::string,std::tuple<std::string,std::string,std::string> > etiss::Configuration::getAnnounced() const{
		std::lock_guard<std::mutex> lock(mu_);
		return announced_;
	}

etiss::Configuration & etiss::cfg(){
	etiss_cfg_inConstructor = true;
	static etiss::Configuration cfg("-oetiss_wd ~/.etiss/" ETISS_VERSION_INTERFACE "/" );
	etiss_cfg_inConstructor = false;
	return cfg;
}

static etiss::ConfigAnnouncer etiss_wd("etiss_wd","path string","default: ~/.etiss/" ETISS_VERSION_INTERFACE "/" ,"the path may start with ~ which will be repaced with getenv(\"HOME\"). A path MUST end with / to function properly.");



// IMPORTANT: check if fpu configuration matches endianness
#include "etiss/fpu/386-GCC.h"
#if ETISS_USE_CONSTEXPR
#ifdef LITTLEENDIAN
	static_assert(getEndianness() == etiss::_LITTLE_ENDIAN_,"ETISS detected an invalid endianness configuartion of the floating point library. please change in the file etiss/fpu/386-GCC.h the line #define LITTLEENDIAN (or similar) to #define BIGENDIAN");
#endif
#ifdef BIGENDIAN
	static_assert(getEndianness() == etiss::_BIG_ENDIAN_,"ETISS detected an invalid endianness configuartion of the floating point library. please change in the file etiss/fpu/386-GCC.h the line #define BIGENDIAN (or similar) to #define LITTLEENDIAN");
#endif
#else
#pragma message("ETISS cannot check if endianess is configured correctly due to missing constexpr support")
#endif





