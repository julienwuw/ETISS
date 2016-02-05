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

	@brief contains an action class that describes actions associated with a fault

	@detail

*/
#ifndef ETISS_FAULT_ACTION_H_
#define ETISS_FAULT_ACTION_H_

#include <stdint.h>
#include <iostream>

#ifndef NO_ETISS
#include "etiss/fault/Defs.h"
#include "etiss/fault/Fault.h"
#include "etiss/fault/XML.h"
#include "etiss/fault/InjectorAddress.h"
#else
#include "fault/Defs.h"
#include "fault/Fault.h"
#include "fault/XML.h"
#include "fault/InjectorAddress.h"
#endif


namespace etiss
{
namespace fault
{

class Fault;

class Action : public etiss::ToString
{
public:
    enum Type
    {
        /// applies a bit flip to a bit in a specified field
        BITFLIP,
        /// commands are targetet at Injectors, not fields. in case a command is targetet at a certain field that information must be passed within the command string
        COMMAND,
        /// NO Operation. used by default constructor
        NOP,
        /// an action that injects a fault definition (trigger + actions)
        INJECTION
    };
private:
    Type type_;
    InjectorAddress inj_;
    std::string command_;
    std::string field_;
    unsigned bit_;
    std::vector<Fault> fault_;
private:
    void ensure(Type );
public: // ctors
    /**
        Type: NOP (no operation)
    */
    Action();
    /**
    	Type: Command

    	abstract string command will be passed to the targeted injector
    */
    Action(const InjectorAddress & inj,const std::string & command);
    /**
    	Type: BitFlip

    	the bit at the given position of the given field of the given injector will be flipped
    */
    Action(const InjectorAddress & inj,const std::string & field,unsigned bit);
    /**
        Type: Injection

        injects a fault. this is especially usefull with Triggers of type TIMERELATIVE
    */
    Action(const Fault & fault);

public: // getters

    Type getType() const;
    const InjectorAddress & getInjectorAddress() const;

    /// COMMAND only
    const std::string & getCommand() const;

    /// BITFLIP only
    const std::string & getTargetField() const;
    unsigned getTargetBit() const;

    /// INJECTION only
    const Fault & getFault() const;

public:
    std::string toString() const;

};

#if ETISS_FAULT_XML

namespace xml {

template<>
bool parse<etiss::fault::Action>(pugi::xml_node node,etiss::fault::Action & f,Diagnostics & diag);
template<>
bool write<etiss::fault::Action>(pugi::xml_node node,const etiss::fault::Action & f,Diagnostics & diag);



}

#endif


}

}

#endif
