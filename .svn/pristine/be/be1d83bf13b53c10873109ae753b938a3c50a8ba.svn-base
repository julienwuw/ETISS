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

	@brief class for simple library access. Libraries can be integrated or loaded at runtime fom a dynamic library

	@detail




*/

#ifndef ETISS_INCLUDE_LIBRARY_H_
#define ETISS_INCLUDE_LIBRARY_H_

#include <memory>
#include <mutex>

#include "etiss/Misc.h"

#include "etiss/JIT.h"
#include "etiss/CPUArch.h"
#include "etiss/Plugin.h"
#include "etiss/ClassDefs.h"


namespace etiss{

	/**
		@brief interface class for libraries. override functions as needed.
		@detail it is neccessary to override all function of the same category. e.g. for plugins: countPlugins(),namePlugin(1),createPlugin(1),deletePlugin(1).
			isEmpty() uses countXXXXXX() functions to assess its return value and doesn't need to be implemented.

			to implement a dynamic library do NOT use this class. Refer to etiss/helper/CPUArchLibrary.h , etiss/helper/JITLibrary.h , etiss/helper/PluginLibrary.h for library functions to implement and use etiss::LibraryInterface::openSharedLibrary to load the dynamic library


	*/
	class LibraryInterface {
	private:
		//friend void etiss::addLibrary(std::shared_ptr<etiss::LibraryInterface> interface);
	public:
		/**
			@param name name of the library
			@param path location of the library and its files
		*/
		LibraryInterface(std::string name);

		virtual ~LibraryInterface();

        /// simple version info string. intended to present information in a human readable way.
        virtual std::string versionInfo();

		virtual unsigned countPlugins();
		virtual unsigned countCPUArchs();
		virtual unsigned countJITs();

		virtual std::string nameJIT(unsigned index);
		virtual std::string namePlugin(unsigned index);
		virtual std::string nameCPUArch(unsigned index);

	public:

		virtual etiss::JIT * createJIT(unsigned index,std::map<std::string,std::string> options = std::map<std::string,std::string>());
		virtual etiss::CPUArch * createCPUArch(unsigned index,std::map<std::string,std::string> options = std::map<std::string,std::string>());
		virtual etiss::Plugin * createPlugin(unsigned index,std::map<std::string,std::string> options = std::map<std::string,std::string>());

		virtual void deleteJIT(etiss::JIT *);
		virtual void deleteCPUArch(etiss::CPUArch *);
		virtual void deletePlugin(etiss::Plugin *);
	public:
		/**
			@brief returns true if this library provides nothing
		*/
		virtual bool isEmpty();
		/**
			@return name of this library
		*/
		virtual const std::string & getName();

		virtual int getFileCount();
		virtual const char * getFileName(int index);
		virtual const char * getFileData(int index);
		/**
            @attention by default this function will return a value smaller than 0. in this case the char pointer of getFileData will be treated as a zero terminated string
		*/
		virtual int getFileSize(int index);

	public:

		static std::shared_ptr<LibraryInterface> openSharedLibrary(std::string path,std::string name);

		static std::shared_ptr<LibraryInterface> openIntegratedLibrary();

		static unsigned getCurrentLibraryVersion();



	private:
		std::string name_;
	};


}

#endif
