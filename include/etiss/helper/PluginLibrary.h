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

	@brief defines the functions needed for a library that provides etiss::CPUArch implementations

	@see IntegratedLibrary.h shows how this header should be used

	@detail




*/
#ifndef ETISS_INCLUDE_HELPER_PLUGINLIBRARY_H_
#define ETISS_INCLUDE_HELPER_PLUGINLIBRARY_H_


#include "etiss/helper/Misc.h"

#include "etiss/Plugin.h"

extern "C" {

	ETISS_PLUGIN_EXPORT unsigned etiss_helper_merge(ETISS_LIBNAME, _countPlugin)(); ///< function to get number of plugin types supplied by a library
	ETISS_PLUGIN_EXPORT const char * etiss_helper_merge(ETISS_LIBNAME, _namePlugin)(unsigned index); ///< function to get the name of a plugin type at index
	ETISS_PLUGIN_EXPORT etiss::Plugin* etiss_helper_merge(ETISS_LIBNAME, _createPlugin)(unsigned index, std::map<std::string, std::string> options); ///< create new instance of the plugin type at index
	ETISS_PLUGIN_EXPORT void etiss_helper_merge(ETISS_LIBNAME, _deletePlugin)(etiss::Plugin*); ///< delete instance


}

#endif

