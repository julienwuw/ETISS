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

	@brief contains the fault container class that stores triggers and actions for fault injection

	@detail

*/
#ifndef ETISS_FAULT_FAULT_H_
#define ETISS_FAULT_FAULT_H_

#include <stdint.h>
#include <iostream>
#include <vector>
#include <list>
#include <limits>
#include <exception>
#include <sstream>

#ifndef NO_ETISS
#include "etiss/fault/Defs.h"
#include "etiss/fault/XML.h"
#include "etiss/fault/Trigger.h"
#include "etiss/fault/Action.h"
#else
#include "fault/Defs.h"
#include "fault/XML.h"
#include "fault/Trigger.h"
#include "fault/Action.h"
#endif




/// if true then mutex will be used to create unique ids for faults in a threadsafe way
#define MUTEX_SUPPORTED CXX0X_UP_SUPPORTED


namespace etiss
{
namespace fault
{

typedef uint64_t INT;

class Action;

class Fault : public etiss::ToString
{
public:
    std::string name_;
    int32_t id_; ///< @attention negative ids are reserverd
public:
    std::vector<Trigger> triggers;
public:
    std::vector<Action> actions;
public:
    Fault();

    std::string toString() const;

    void resolveTime(uint64_t time);
    bool isResoved() const;

};

#if ETISS_FAULT_XML

bool parseXML(std::vector<Fault> & vec,std::istream & input,std::ostream & diagnostics_out = std::cout);

bool writeXML(const std::vector<Fault> & vec,std::ostream & out,std::ostream & diagnostics_out = std::cout);

namespace xml {

template<>
bool parse<etiss::fault::Fault>(pugi::xml_node node,etiss::fault::Fault & f,Diagnostics & diag);
template<>
bool write<etiss::fault::Fault>(pugi::xml_node node,const etiss::fault::Fault & f,Diagnostics & diag);

}

#endif

}
}

#endif
