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

	@brief general configuration and logging

	@detail




*/

#ifndef ETISS_INCLUDE_MISC_H_
#define ETISS_INCLUDE_MISC_H_



#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <typeinfo>
#include <mutex>
#include <functional>

#include "etiss/config.h"

#include "etiss/jit/types.h"

// some msvc pathces
#ifdef _MSC_VER
typedef std::make_signed<size_t>::type ssize_t;
#endif


#define ETISS_TOSTRING2(X) #X
#define ETISS_TOSTRING(X) ETISS_TOSTRING2(X)

#define etiss_log(LEVEL,MSG) etiss::log(etiss::LEVEL, std::string("On line " ETISS_TOSTRING(__LINE__) " in file " ETISS_TOSTRING(__FILE__) ": ") + (MSG));

#define etiss_del_copy(CLASS) CLASS (const CLASS &) = delete; CLASS & operator=(const CLASS &) = delete;
#define etiss_del_move(CLASS) CLASS & operator=( CLASS && ) = delete; CLASS ( CLASS && ) = delete;

#define etiss_del_como(CLASS) etiss_del_copy(CLASS) etiss_del_move(CLASS)


// special define that creates a STRUCT whose STRUCT::value is true if EXPRESSION is valid given template parameter T (note expression may not have a ';': e.g. ((T*)0)->toString() NOT ((T*)0)->toString();
#define ETISS_TEMPLATE_EXPRESSION_IS_VALID(STRUCT,EXPRESSION) \
				template<typename> struct STRUCT##Void { typedef void type; }; \
				template<typename T, typename Sfinae = void> \
				struct STRUCT : std::false_type {}; \
				template<typename T> \
				struct STRUCT<T, typename STRUCT##Void<decltype( EXPRESSION )>::type> : std::true_type {};


namespace etiss
{

/**
	@brief log levels
*/
enum Verbosity
{
    SILENT = 0,
    FATALERROR = 1,
    ERROR = 2,
    WARNING = 3,
    INFO = 4,
    VERBOSE = 5
};

/**
	simple marker interface for toString() support
*/
class ToString{
public:
	inline ToString(){}
	virtual inline ~ToString(){}
};


template <typename T>
typename std::enable_if < std::is_base_of < etiss::ToString, T > ::value, std::ostream & >::type operator << (std::ostream& os, const T & val){
	os << val.toString();
	return os;
}



/**
	@brief get reference to log level. may be used to change log level in certain cases. otherwise set by etiss::initialize

*/
Verbosity & verbosity();

template <typename T>
/**
	@brief conversion of type T to std::string. default implementation uses std::stringstream. this function also works if std::string/const char* T::toString() exists
*/
std::string toString( const T & val )
{
    std::stringstream ss;
    ss << val;
    return ss.str();
}


 std::list<std::string> split(const std::string & str, std::function<size_t(const std::string & /**<str*/, size_t /**<from*/, size_t & /**<seperatorsize*/)> findsplit);
inline std::list<std::string> split(const std::string & str,char splitchar)
{
    return split(str,[splitchar](const std::string & str,size_t from,size_t & seperatorsize)
    {
        seperatorsize = 1;
        return str.find(splitchar,from);
    });
}
inline std::list<std::string> split(const std::string & str,const std::string & splitstring)
{
    return split(str,[splitstring](const std::string & str,size_t from,size_t & seperatorsize)
    {
        seperatorsize = 1;
        return str.find(splitstring,from);
    });
}


template <typename T,typename T2,typename... O>
/**
	@brief conversion of type T to std::string. default implementation uses std::stringstream
*/
std::string toString( const  T & val ,const T2 & val2,const O&... others)
{
    return toString(val) + ";"+toString(val2,others...);
}

/**
	@brief prints string representation of verbosity level
*/
 std::string toString(const Verbosity & val);

/**
	simple class that store source location information to pass to etiss::log(). use the macro ETISS_SRCLOC for simplicity:
		e.g. etiss::log(etiss::ERROR,"some error",ETISS_SRCLOC);
*/
class  SourceCodeLocation : public ToString
{
public:
    inline SourceCodeLocation(const std::string & file,size_t line) : file_(file),line_(line) {}
    inline std::string toString() const
    {
        return std::string("SourceCodeLocation { file=\"") + file_ + "\", line=" + etiss::toString(line_) +"}";
    }
    const std::string file_;
    const size_t line_;
};

#define ETISS_SRCLOC etiss::SourceCodeLocation(__FILE__,__LINE__)
#define ETISS_VARVAL(VAR) (std::string(ETISS_TOSTRING(VAR))+"={"+toLogString(VAR)+"}")


/**
	@brief write log message at the given level. if the current verbose level is lower then the message will not be printed
*/
  void log(Verbosity level, std::string msg);
/**
	@brief write log message at the given level. if the current verbose level is lower then the mesGen function will not be called.
*/
 void logC(Verbosity level, std::function<std::string(void)> msgGen);



template <typename T>
/**
currently toLogString only puts the result of toString() in curly brackets
*/
std::string toLogString(const T & t){
	return std::string("{") + etiss::toString(t) + "}";
}

template <typename T1,typename T2,typename ... O>
std::string toLogString(const T1 & t1,const T2 & t2, const O & ... os){
	return toLogString(t1) + "\n\t\t" + toLogString(t2,os...);
}

/**
	additional objects will be converted to a string with toString and are added to the message
*/
template <typename T,typename... O>
void log(Verbosity level,std::string msg,const T & t, const O &...  args)
{
    if (level <= (int)verbosity())
    {
        etiss::log(level,msg + " \n\t{\n\t\t" + toLogString(t,args...) + "\n\t}");
    }
}


 std::vector<std::string> parseCommands(const std::string & cmdline);

/**
	@brief simple class to hold configuration options
*/
class Configuration
{
public:
    Configuration();
    Configuration(std::string args);
    Configuration(const std::list<std::string> & args);
    /**
    	@brief access to the configuration map
    */
    std::map<std::string,std::string> & config();
    template <typename T>
    /**
    	@brief template function to read the value of a configuration key. use specialization to provide std::string value conversion
    */
    T get(const std::string & key,T default_,bool * default_used = 0)
    {
        etiss::log(etiss::ERROR,std::string("etiss::Configuration::get not implemented for requested type"));
        if (default_used)
            *default_used = true;
        return default_;
    }
    bool debug();
    template <typename T>
    /**
    	@brief template function to set the value of a configuration key. use specialization to provide to std::string conversion where a stringstream failes to convert the value
    	@return false if key is final
    */
    bool set(const std::string & key,T value)
    {
        std::stringstream ss;
        ss << value;
        std::lock_guard<std::mutex> lock(mu_);
        if (final_.find(key) != final_.end())
            return false;

        auto hlp = helpers_.find(key);
        if (hlp != helpers_.end())
        {
            cfg_[key] = (hlp->second)(ss.str());
        }
        else
        {
            cfg_[key] = ss.str();
        }
        return true;
    }
    /**
    	@brief return true if the value of an configuration key has been set
    */
    bool isSet(std::string val);
    /**
    	@brief removes a key value mapping
    */
    void remove(const std::string & key);
    /**
    	@brief parses a list of parameters to apply to this config. currently supported any boolean options in the style of -fOPTION (OPTION = true) and -fno-OPTION (OPTION = false) and string values in the form "-oOPTION value"
    	@return a list of input elements that have not been used in this function due to an unrecognized format
    */
    std::list<std::string> set(const std::list<std::string> & args);
    /**
    	@brief get a copy of the configuration as a map
    */
    std::map<std::string,std::string> listFullConfiguration();
    /**
    	@brief makes an option final (option can no longer be changed)
    */
    void makeFinal(const std::string & key);
    /**
    	@brief add a possible option to a list. this is just for documentation purposes and has no effect on the configuration itself
    */
    void announce(std::string key,std::string type = std::string(),std::string values = std::string(),std::string description = std::string());
    /**
    	@brief get a map copy with announced options
    */
    std::map<std::string,std::tuple<std::string,std::string,std::string> > getAnnounced() const;
private:
    std::map<std::string,std::string> cfg_;
    std::set<std::string> final_;
    std::map<std::string,std::function<std::string(std::string)> > helpers_;
    mutable std::mutex mu_;
    std::map<std::string,std::tuple<std::string,std::string,std::string> > announced_;
};

// template specializations
template<> std::string Configuration::get<std::string>(const std::string & key, std::string default_, bool * default_used);
template<> bool Configuration::get<bool>(const std::string & key, bool default_, bool * default_used);
template<> int Configuration::get<int>(const std::string & key, int default_, bool * default_used);
template<> uint64_t Configuration::get<uint64_t>(const std::string & key, uint64_t default_, bool * default_used);

/**
	@brief main configuration object
*/
 Configuration & cfg();

/**
	simple class to add a configuration option to the list of known options
*/
class ConfigAnnouncer
{
public:
    inline ConfigAnnouncer(Configuration & config,std::string key,std::string type = std::string(),std::string values = std::string(),std::string description = std::string())
    {
        config.announce(key,type,values,description);
    }
    inline ConfigAnnouncer(std::string key,std::string type = std::string(),std::string values = std::string(),std::string description = std::string())
    {
        cfg().announce(key,type,values,description);
    }
};



enum endian_t :
uint32_t
{
    _LITTLE_ENDIAN_ = ETISS_LITTLE_ENDIAN,
    _BIG_ENDIAN_ = ETISS_BIG_ENDIAN,
    _UNKNOWN_ENDIAN_ = ETISS_UNKNOWN_ENDIAN
};

/**
	@brief evaluates the endianness of the current build as a constexpr.
	@todo test on big endian machine
*/
#if ETISS_USE_CONSTEXPR
constexpr
#else
inline
#endif
endian_t getEndianness()
{
    return ((0xFFFFFFFF & 1) == _LITTLE_ENDIAN_)?_LITTLE_ENDIAN_:((0xFFFFFFFF & 1) == _BIG_ENDIAN_)?_BIG_ENDIAN_: _UNKNOWN_ENDIAN_;
}







}


#include "etiss/ClassDefs.h"

#endif
