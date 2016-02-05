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

@date December 15, 2014

@version 0.4

*/
/**
	@file

	@brief contains general definitions used by other fault library code

	@detail

*/

#ifndef ETISS_FAULT_DEFS_H_
#define ETISS_FAULT_DEFS_H_

#include <stdint.h>
#include <iostream>

///if this code and other parts of the fault injection interface is used standalone (not as a part of ETISS) then NO_ETISS must be defined in the compiler command. The makefile include (fault_xml_module.mk) defines this by default.
//

///set to 1 to enable xml support
#define ETISS_FAULT_XML 1

/// if true then C++0x or newer will be used
#if defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L || !defined(NO_ETISS)
#define CXX0X_UP_SUPPORTED 1
#else
#define CXX0X_UP_SUPPORTED 0
#endif

#if CXX0X_UP_SUPPORTED
#include <memory>
#endif



namespace etiss
{
namespace fault
{

class Injector;

#if CXX0X_UP_SUPPORTED
    typedef std::shared_ptr<Injector> Injector_ptr;
#else
    typedef Injector * Injector_ptr;
#endif



}

}

#ifdef NO_ETISS
namespace etiss{
class ToString {
public:
	inline ToString(){}
	virtual inline ~ToString(){}
	virtual inline std::string toString(){return "";}
};
}
#endif


#endif
