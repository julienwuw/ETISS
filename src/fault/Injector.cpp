
#ifndef NO_ETISS
#include "etiss/Misc.h"
#include "etiss/fault/Injector.h"
#include "etiss/fault/Stressor.h"
#else
#include "fault/Injector.h"
#include "fault/Stressor.h"
#endif

#include <iostream>


namespace etiss {

namespace fault {

int x;
Injector::Injector(){
	has_pending_triggers = false;
}

void Injector::freeFastFieldAccessPtr(void *){}

bool Injector::needsCallbacks(){
	return has_pending_triggers;
}

void Injector::cycleAccurateCallback(uint64_t time_ps){
    // copy pending triggers in a threadsafe manner
    if (has_pending_triggers){
#if CXX0X_UP_SUPPORTED
        std::lock_guard<std::mutex> lock(sync);
#endif
        unknown_triggers.insert(unknown_triggers.end(), pending_triggers.begin(), pending_triggers.end());
        pending_triggers.clear();
    }
    // check triggers
    if (!unknown_triggers.empty()){
        for (std::list<std::pair<Trigger,int32_t> >::iterator iter = unknown_triggers.begin();iter != unknown_triggers.end();){
            if (iter->first.fired(time_ps,this)){ // trigger fired
                //signal fired trigger
                if (Stressor::firedTrigger(iter->first,iter->second,this,time_ps)){
                    //remove fired trigger
                    unknown_triggers.erase(iter++);
                } else {
                    ++iter;
                }
            } else {
                ++iter;
            }
        }
    }
}
void Injector::instructionAccurateCallback(uint64_t time_ps){
	cycleAccurateCallback(time_ps); /// todo
}
#if CXX0X_UP_SUPPORTED
template <typename T>
/**
    helper function for pointer comparison
*/
bool operator==(const std::shared_ptr<T> & p1,const T * const & p2){
    return p1.get() == p2;
}
#endif


std::string Injector::getInjectorPath(){

    std::string path;
    ptr iptr = getParentInjector();
    ptr cur;
    if (!iptr)
        return path;
    std::list<std::string> si = iptr->listSubInjectors();
    for (std::list<std::string>::const_iterator iter = si.begin();iter != si.end();++iter){
        cur = iptr->getSubInjector(*iter);
        if (cur == this){
            path = *iter;
            break;
        }
    }
    if (!cur){
#ifdef NO_ETISS
                std::cout << "Failed to find injector" << std::endl;
#else
                etiss::log(etiss::ERROR,"Failed to find injector to create path name",ETISS_SRCLOC);
#endif
        return "";
    }
    cur = iptr;
    iptr = iptr->getParentInjector();
    while (iptr){
        std::list<std::string> si = iptr->listSubInjectors();
        bool ok = false;
        for (std::list<std::string>::const_iterator iter = si.begin();iter != si.end();++iter){
            ptr tmp = iptr->getSubInjector(*iter);
            if (tmp == cur){
                path = *iter + "::" + path;
                ok = true;
                break;
            }
        }
        if (!ok){
#ifdef NO_ETISS
                std::cout << "Failed to find injector" << std::endl;
#else
                etiss::log(etiss::ERROR,"Failed to find injector to create path name",ETISS_SRCLOC);
#endif
            return "";
        }
        cur = iptr;
        iptr = iptr->getParentInjector();

    }

    return path;

}

void Injector::addTrigger(const Trigger & t,int32_t fault_id){
#if CXX0X_UP_SUPPORTED
    std::lock_guard<std::mutex> lock(sync);
#endif
	if (acceleratedTrigger(t,fault_id)){
		// trigger is handled internally without callbacks
	} else {
		pending_triggers.push_back(std::pair<Trigger,int32_t>(t,fault_id));
		has_pending_triggers = true;
    }
}

bool Injector::acceleratedTrigger(const etiss::fault::Trigger &,int32_t fault_id){
	std::cout << "Injector::acceleratedTrigger called" << std::endl; 
	return false;
}


}

}
