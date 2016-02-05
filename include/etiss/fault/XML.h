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

	@brief contains XML related functions. pugixml is used as a backend for parsing.

	@detail \see parse() and \see write() and their specializations.

*/
#ifndef ETISS_FAULT_XML_H_
#define ETISS_FAULT_XML_H_

#include <list>
#include <string>


#ifndef NO_ETISS
#include "etiss/fault/xml/pugixml.hpp"
#include "etiss/fault/Defs.h"
#else
#include "fault/xml/pugixml.hpp"
#include "fault/Defs.h"
#endif

#include <cstdio>



namespace etiss
{

namespace fault
{

#if ETISS_FAULT_XML

/**
    Parser/writer structure:

    class and field structure is closely modeled by the xml structure. each class is a node and each field is either a sub node or an attribute.
    This allows for a simple parsing concept. the template function parse() is implemented for each type that needs to be read and is called recursively for fields of different types.
    e.g.
<pre>
    C++:
        class Trigger {
            [...]
        };
        class Fault {
            std::vector<Trigger> triggers;
            const char * name;
        };

    XML:

        <fault name="...">
            <triggers>
                <trigger>
                    [...]
                </trigger>
            </triggers>
        </fault>

    example parser recursion:

        parse<Fault>(...)
            parse<std::vector<Trigger> >(...)
                parse<Trigger>(...)
                    [...]
            parse_attr("name",...)

</pre>


*/
namespace xml
{


/**
    prints information about parsing problems
*/
class Diagnostics
{
public:
    std::list<std::string> warnings;
    std::list<std::string> errors;
    void ignoredNode(const pugi::xml_node & node,const std::string & msg);
    void unexpectedNode(const pugi::xml_node & node,const std::string & msg);
    void print(std::ostream & out) const;

};

///////// basic parser templates /////////////////
#if CXX0X_UP_SUPPORTED
template <typename T>
bool parse(pugi::xml_node node,T & dst,Diagnostics & diag)
{
    static_assert((sizeof(T) == -1),"etiss::fault::xml::parse needs to be specialized.");
    return false;
}
template <typename T>
bool write(pugi::xml_node node,const T & src,Diagnostics & diag)
{
    static_assert((sizeof(T) == -1),"etiss::fault::xml::write needs to be specialized.");
    return false;
}
#else
template <typename T>
bool parse(pugi::xml_node node,T & dst,Diagnostics & diag);
template <typename T>
bool write(pugi::xml_node node,const T & src,Diagnostics & diag);
#endif

#if CXX0X_UP_SUPPORTED
template <typename T>
bool parse_attr(pugi::xml_node node,const std::string & attr_name,T & dst,Diagnostics & diag)
{
    static_assert((sizeof(T) == -1),"etiss::fault::xml::parse_attr needs to be specialized.");
    return false;
}
template <typename T>
bool write_attr(pugi::xml_node node,const std::string & attr_name,const T & src,Diagnostics & diag)
{
    static_assert((sizeof(T) == -1),"etiss::fault::xml::write_attr needs to be specialized.");
    return false;
}
#else
template <typename T>
bool parse_attr(pugi::xml_node node,const std::string & attr_name,T & dst,Diagnostics & diag);
template <typename T>
bool write_attr(pugi::xml_node node,const std::string & attr_name,const T & src,Diagnostics & diag);
#endif

///////////////////////////////////////////////



template <>
bool parse<std::string>(pugi::xml_node node,std::string & dst,Diagnostics & diag);
template <>
bool write<std::string>(pugi::xml_node node,const std::string & src,Diagnostics & diag);

template <>
bool parse<uint64_t>(pugi::xml_node node,uint64_t & dst,Diagnostics & diag);
template <>
bool write<uint64_t>(pugi::xml_node node,const uint64_t & src,Diagnostics & diag);

template <>
bool parse<unsigned>(pugi::xml_node node,unsigned & dst,Diagnostics & diag);
template <>
bool write<unsigned>(pugi::xml_node node,const unsigned & src,Diagnostics & diag);

template <>
bool parse_attr<std::string>(pugi::xml_node node,const std::string & attr_name,std::string & dst,Diagnostics & diag);
template <>
bool write_attr<std::string>(pugi::xml_node node,const std::string & attr_name,const std::string & src,Diagnostics & diag);


///////////////////////////helper functions
template <typename T>
/// conversion of string to type t
bool fromString(const std::string & s,T & val);

template <>
bool fromString<uint64_t>(const std::string & s,uint64_t & val);
template <>
bool fromString<unsigned>(const std::string & s,unsigned & val);

bool hasName(const pugi::xml_node & node,const std::string & name);
bool hasName(const pugi::xml_attribute & attr,const std::string & name);

pugi::xml_node findSingleNode(pugi::xml_node node,const std::string & name,Diagnostics & diag);

////////////////////////////////////////////

}
#endif
}

}

#endif
