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

	@brief contains a simple class that represents and resolves injector addresses as used by triggers (\see etiss::fault::Trigger) and actions (\see etiss::fault::Action)

	@detail

*/
#ifndef ETISS_FAULT_INJECTORADDRESS_H_
#define ETISS_FAULT_INJECTORADDRESS_H_

#include <stdint.h>
#include <iostream>
#include <string>

#ifndef NO_ETISS
#include "etiss/Misc.h"
#include "etiss/fault/Defs.h"
#include "etiss/fault/XML.h"
#else
#include "fault/Defs.h"
#include "fault/XML.h"
#endif

namespace etiss
{
namespace fault
{

class InjectorAddress : public etiss::ToString{
private:
	std::string path_;
	mutable Injector_ptr iptr_;
public: // ctors
    InjectorAddress();
	InjectorAddress(const std::string & address);
	InjectorAddress(const InjectorAddress & );
	InjectorAddress & operator=(const InjectorAddress & );
#if CXX0X_UP_SUPPORTED
	InjectorAddress(InjectorAddress && );
	InjectorAddress & operator=(InjectorAddress && );
#endif

public:
    const std::string & getInjectorPath() const;
    const Injector_ptr & getInjector() const;

    bool isResolved() const;

    inline std::string toString() const {
        return getInjectorPath();
    }


};

#if ETISS_FAULT_XML

namespace xml {

template <>
bool parse<etiss::fault::InjectorAddress>(pugi::xml_node node,etiss::fault::InjectorAddress & dst,Diagnostics & diag);
template <>
bool write<etiss::fault::InjectorAddress>(pugi::xml_node node,const etiss::fault::InjectorAddress & src,Diagnostics & diag);

template <>
bool parse<etiss::fault::InjectorAddress*>(pugi::xml_node node,etiss::fault::InjectorAddress * & dst,Diagnostics & diag);
template <>
bool write<const etiss::fault::InjectorAddress*>(pugi::xml_node node,const etiss::fault::InjectorAddress * const & src,Diagnostics & diag);

}

#endif


}

}

#endif
