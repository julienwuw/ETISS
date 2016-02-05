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

	@brief contains general definitions needed for library function definitions. Doesn't need to be included by user.

	@see PluginLibrary.h
	@see JITLibrary.h
	@see CPUArchLibrary.h

	@detail




*/
#ifndef ETISS_INCLUDE_HELPER_MISC_H_
#define ETISS_INCLUDE_HELPER_MISC_H_

#include "etiss/pluginexport.h"
#include <string>
#include <map>

#include "etiss/config.h"


#define etiss_helper_merge_l2(X1,X2) X1##X2
#define etiss_helper_merge(X1,X2) etiss_helper_merge_l2(X1,X2)


extern "C" {


	/**
		 must be implemented like this:

			#include "helper/Misc.h"
			ETISS_LIBRARYIF_VERSION_FUNC_IMPL

	*/
	ETISS_PLUGIN_EXPORT unsigned etiss_helper_merge(ETISS_LIBNAME, _etissversion)();

}

#define ETISS_LIBRARYIF_VERSION_FUNC_IMPL ETISS_PLUGIN_EXPORT unsigned etiss_helper_merge(ETISS_LIBNAME,_etissversion)(){ \
							return (ETISS_VERSION_MAJOR << 16) + (ETISS_VERSION_MINOR); \
						}

#endif





