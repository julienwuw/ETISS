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
	
	@brief JIT compiler interface definition

	@detail 
		
		
		

*/
#ifndef ETISS_INCLUDE_JIT_H_
#define ETISS_INCLUDE_JIT_H_

#include "etiss/Misc.h"

namespace etiss {
	
	/**
		@brief compiler interface for just in time compilation of generated C code
	*/
	class  JIT {
	public:
		JIT(std::string name);
		virtual ~JIT();
		/**
			@brief translate C code to executable code and return a handle/pointer that identifies the compilation result
			@param code generated code
			@param headerpaths paths where required header files are located
			@param librarypaths paths where required libraries are located (usually not needed since libraries don't require full linking)
			@param libraries file names of required libraries (usually not needed since libraries don't require full linking)
			@param error string to return additional error information
			@param debug if true then compilation should try to enable gdb to jump into compiled functions
		*/
		virtual void * translate(std::string code,std::set<std::string> headerpaths,std::set<std::string> librarypaths,std::set<std::string> libraries,std::string & error,bool debug = false) = 0;
		/**
			@brief returns a function pointer to a compiled function from the handle returned by etiss::JIT::translate
		*/
		virtual void * getFunction(void * handle,std::string name,std::string & error) = 0;
		/**
			@brief clean up handled returned by etiss::JIT::translate
		*/
		virtual void free(void * handle) = 0;
		/**
			@brief returns the JIT instance name previously passed to the constructor
		*/
		std::string getName();
		
	private:
		std::string name_;
		
	};

}



#endif
