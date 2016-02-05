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

	@brief contains the Trigger class that defines conditions under which actions of a Fault need to be applied.

	@detail

*/
#ifndef ETISS_FAULT_TRIGGER_H_
#define ETISS_FAULT_TRIGGER_H_

#include <stdint.h>
#include <iostream>


#if CXX0X_UP_SUPPORTED
#include <memory>
#endif

#ifndef NO_ETISS
#include "etiss/Misc.h"
#include "etiss/fault/XML.h"
#include "etiss/fault/InjectorAddress.h"
#else
#include "fault/XML.h"
#include "fault/InjectorAddress.h"
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

	class Trigger : public etiss::ToString
{
public:
    enum Type
    {
        META_COUNTER,
        VARIABLEVALUE,
        TIME,
        /// needs to be resolved. this can only be used in connection with an injection action
        TIMERELATIVE,
        NOP
    };
private: // variables
    Type type_;
    std::string field_;
    Trigger * sub_;
    InjectorAddress inj_;
    void * fieldptr_;
    uint64_t param1_;
    uint64_t param2_;

private:

    void ensure(Type type) const;

public: // constructor

    Trigger();
    Trigger(const Trigger & sub,uint64_t count);
    Trigger(const InjectorAddress & target_injector,const std::string & field,uint64_t value);
    Trigger(const InjectorAddress & target_injector,uint64_t time_ps ,bool relative = false);

    Trigger(const Trigger & cpy);
    Trigger & operator=(const Trigger & cpy);

#if CXX0X_UP_SUPPORTED
    Trigger(Trigger && cpy);
    Trigger & operator=(Trigger && cpy);
#endif

    ~Trigger();

public:

    uint64_t getTriggerCount() const;
    Trigger & getSubTrigger();
    const Trigger & getSubTrigger() const;
    uint64_t getTriggerTime() const;
    const InjectorAddress & getInjectorAddress() const;
    const Injector_ptr & getInjector() const;
    bool isNOP() const;
    const std::string & getTriggerField() const;
    const uint64_t & getTriggerFieldValue() const;

    Type getType() const;

    bool fired(uint64_t time_ps,etiss::fault::Injector * target_injector);

    void resolveTime(uint64_t time);
    bool isResolved() const;


public:
    std::string toString() const;


};


#if ETISS_FAULT_XML
namespace xml{

    template<>
    bool parse<etiss::fault::Trigger*>(pugi::xml_node node,etiss::fault::Trigger* & f,Diagnostics & diag);
    template<>
    bool write<const etiss::fault::Trigger*>(pugi::xml_node node,const etiss::fault::Trigger * const & f,Diagnostics & diag);

    template<>
    bool parse<etiss::fault::Trigger>(pugi::xml_node node,etiss::fault::Trigger & f,Diagnostics & diag);
    template<>
    bool write<etiss::fault::Trigger>(pugi::xml_node node,const etiss::fault::Trigger & f,Diagnostics & diag);

}
#endif

}
}


#endif //ETISS_FAULT_TRIGGER_H_
