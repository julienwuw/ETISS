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

	@brief contains the fault injector interface class.

	@detail

*/
#ifndef ETISS_INJECTOR_H_
#define ETISS_INJECTOR_H_

#ifndef NO_ETISS
#include "etiss/fault/Fault.h"
#else
#include "fault/Fault.h"
#endif

#if CXX0X_UP_SUPPORTED
#include <functional>
#include <memory>
#include <mutex>
#endif

#include <fstream>


namespace etiss{

namespace fault{

class Stressor;

class Injector{
public:
#if CXX0X_UP_SUPPORTED
    typedef std::shared_ptr<Injector> ptr;
#else
    typedef Injector * ptr;
#endif

public: // override in inheriting classes
	Injector();
    /**
        list all fields directly reachable by this injector
        @see etiss::VirtualStruct for example implemention
    */
    virtual std::list<std::string> listFields() = 0;
    /**
        list all sub injectors.
        @see etiss::VirtualStruct for example implemention
    */
    virtual std::list<std::string> listSubInjectors() = 0;


    /**
        get a sub injector. in case of c++11 this function returns a smart pointer (std::shared_ptr<Injector>)
        @see etiss::VirtualStruct for example implemention
    */
    virtual ptr getSubInjector(const std::string & name) = 0;
    /**
        get a the parent injector (root returns 0). in case of c++11 this function returns a smart pointer (std::shared_ptr<Injector>)
        @see etiss::VirtualStruct for example implemention
    */virtual ptr getParentInjector() = 0;

public: // callbacks

	virtual bool needsCallbacks();
    virtual void cycleAccurateCallback(uint64_t time_ps);
    virtual void instructionAccurateCallback(uint64_t time_ps);

public: // currently public functions but might become protected later on

    /**
        @attention MUST NOT be called from without the callback functions cycleAccurateCallback() and instructionAccurateCallback(). The assumption of a singlethreaded access/use of these functions MUST hold.
        @return 0 in case of failure. otherwise an internal pointer shall be retuned that allows to access a field in a quick manner. freefastFieldAccessPtr MUST be called after use.
    */
    virtual void * fastFieldAccessPtr(const std::string & name,std::string & errormsg) = 0;
    /**
        MUST be called to cleanup a pointer acquired with fastFieldAccessPtr()
        default implementation is nop
        @attention MUST NOT be called from outside the callback functions cycleAccurateCallback() and instructionAccurateCallback(). The assumption of a singlethreaded access/use of these functions MUST hold.
    */
    virtual void freeFastFieldAccessPtr(void *);
    /**
        read the value of a field
        @return true if read succeded
        @attention MUST NOT be called from outside the callback functions cycleAccurateCallback() and instructionAccurateCallback(). The assumption of a singlethreaded access/use of these functions MUST hold.

    */
    virtual bool readField(void * fastfieldaccessptr,uint64_t & val,std::string & errormsg) = 0;
    /**
        @return true if action could be applied
        @attention MUST NOT be called from without the callback functions cycleAccurateCallback() and instructionAccurateCallback(). The assumption of a singlethreaded access/use of these functions MUST hold.
    */
    virtual bool applyAction(const etiss::fault::Fault & fault,const etiss::fault::Action & action,std::string & errormsg) = 0;

	virtual bool acceleratedTrigger(const etiss::fault::Trigger &,int32_t fault_id);

public: // static
	/**
        @param injectorPath the full path/name to/off an injector. in case of using ETISS/VirtualStruct please have a look at the doc of etiss::VirtualStruct for examples of the path syntax
        @attention this function needs to be implemented in case of not using ETISS/VirtualStruct
    */
	static ptr get(const std::string & injectorPath);


	/**
        returns the path of the current object.
        by default the path will consists of the injector names from getSubInjectors() seperated by "::" (see etiss::VirtualStruct).
        override this function to match other/custom syntax

	*/
	virtual std::string getInjectorPath();

private:
#if CXX0X_UP_SUPPORTED
    std::mutex sync;
#endif
    volatile bool has_pending_triggers;
    std::list<std::pair<Trigger,int32_t> > pending_triggers;
    std::list<std::pair<Trigger,int32_t> > unknown_triggers;
    /// TODO specialized lists. e.g. time triggers should be sorted and only the earliest time should be checked

public: // interface fot stressor

    void addTrigger(const Trigger & t,int32_t fault_id);

};

}

}


#endif
