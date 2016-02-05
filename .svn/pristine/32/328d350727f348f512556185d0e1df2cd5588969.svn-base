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

	@brief header file to include in a project that uses ETISS




*/

#ifndef ETISS_INCLUDE_ETISS_H_
#define ETISS_INCLUDE_ETISS_H_

#include "etiss/config.h"


#include <map>
#include <string>
#include <mutex>
#include <memory>
#include <type_traits>

#include "etiss/Misc.h"
#include "etiss/CPUCore.h"


#include "etiss/LibraryInterface.h"



namespace etiss
{

/** \addtogroup ETISS_Frontend
 *  @{
 */

/**
	@brief list present cpu arch names
*/
  std::set<std::string> listCPUArchs();

/**
	@brief list present JIT instances
*/
  std::set<std::string> listJITs();

/**
	@brief list present JIT instances
*/
  std::set<std::string> listPlugins();

/**
	@brief searches and tries to load libraries. called automatically by CPUCore::create(1)
	@see ETISSInit.cpp
*/
  void preloadLibraries();

/**
	@brief get present JIT instance
*/
  std::shared_ptr<JIT> getJIT(std::string name, std::map<std::string, std::string> options = std::map<std::string, std::string>());
/**
	@brief get a present cpu arch
*/
  std::shared_ptr<CPUArch> getCPUArch(std::string name, std::map<std::string, std::string> options = std::map<std::string, std::string>());
/**
	@brief get a present plugin
*/
  std::shared_ptr<Plugin> getPlugin(std::string name, std::map<std::string, std::string> options = std::map<std::string, std::string>());
/**
	@brief load a library that provides CPUArch/JIT/Plugin implementations
*/
  bool loadLibrary(std::string path, std::string name);
/**
	@brief adds a LibraryInterface to the ETISS environment
*/
  void addLibrary(std::shared_ptr<etiss::LibraryInterface> interface); // now declared in LibraryInterface.h
  /**
  @brief returns a list of library names with some information appended in square brackets. use listLibraryPrefixes for the raw library name
  */
  std::set<std::string> listLibraries();

  /**
  @brief list of library names. the library names are also required to be used as prefixes to symbols (library name + '_': e.g. ETISSINCLUDED_exportedSymbol)
  */
  std::set<std::string> listLibraryPrefixes();


/**
	@brief initialize and configure ETISS
	@attention it is recommende to use etiss::Initializer instead of calling etiss::initialize / etiss::shutdown manually
*/

  void initialize(std::vector<std::string> args);

/**
	@brief get default jit implementation. returned reference may be used to override default. usually first loaded jit.
*/
  std::shared_ptr<etiss::JIT> getDefaultJIT();

/**
	@brief must be called at the end of main() if etiss::initialize instead of etiss::Initializer has been used. ensures propper order of library unloading and cleanup
	@attention it is recommende to use etiss::Initializer instead of calling etiss::initialize / etiss::shutdown manually
*/
  void shutdown();

/**
    create an instance at the beginning of main to ensure propper initialization and cleanup.
    \code
    int main(int argc,char ** argv){
        etiss::Initializer etiss_initializer(argc,argv);

        // program/simulation

    } //<- the etiss::Initializer instance will be destroied here and performs cleanup operations
    \endcode

    Use this classe instead of etiss::initialize() / etiss::shutdown() for convenience reasons.
*/
class    Initializer
{
private:
	template <typename T, typename... lisT>
	void toList(std::vector<std::string> & vec,T t,lisT... args)
	{
		vec.push_back(etiss::toString(t));
		toList(vec,args...);
	}
	inline void toList(std::vector<std::string> & vec) {}
public:
	template <typename... lisT>
	/**
		@brief takes a length parameter and an array of char strings like it is passed to main(int argc,char**argv). additional arguments can simply be added at the end of the argument list.If an argument is not a string it will be converted to a string with the help of std::stringstream.
	*/
	Initializer(int argc,const char **argv,lisT... args_append)
	{
		std::vector<std::string> args;
		for (int i = 0; i<argc; i++)
		{
			args.push_back(std::string(argv[i]));
		}
		toList(args,args_append...);
		initialize(args);
	}
	template <typename... listT>
	/**
		@brief template initializer to pass arguments. If an argument is not a string it will be converted to a string with the help of etiss::toString(). e.g. etiss::Initializer initializer("-foption1","-fno-option2","-osomevallue",123,"etc.");

	*/
	Initializer(listT... args)
	{
		std::vector<std::string> argv;
		toList(argv,args...);
		initialize(argv);
	}
	/**
        calls etiss::shutdown()
	*/
	~Initializer();
};

/**
	@brief tries to return an error message associated with the given code in the context of a cpu architecture
	@todo add error message interface to etiss::CPUArch
*/
  std::string errorMessage(etiss::int32 code, CPUArch * arch = 0);

/**
 *  @}
 */// end of \addtogoup

/**
    \addtogroup ETISS_Internals
	@brief used by some etiss functions to force initialization if it has not occured.

	@see etiss::initialize
*/

  void forceInitialization();

namespace py
{
void init();
void shutdown();
void console();
bool supported();
void runString(std::string s);
void run(std::function<void(void)> func);
void runEXT(std::function<void(void)> func);
}



} // namespace etiss


#endif
