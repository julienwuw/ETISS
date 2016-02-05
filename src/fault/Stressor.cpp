
#ifndef NO_ETISS
#include "etiss/Misc.h"
#include "etiss/fault/Stressor.h"
#include "etiss/fault/Injector.h"
#else
#include "fault/Stressor.h"
#include "fault/Injector.h"
#endif

#include <map>
#include <iostream>
#include <fstream>

#if CXX0X_UP_SUPPORTED
#include <mutex>
#endif

namespace etiss {

namespace fault {


bool Stressor::loadXML(const std::string & file){

    std::vector<Fault> faults;

    std::ifstream in;
    in.open(file.c_str());
    if (!in.is_open()){
        #ifdef NO_ETISS
                std::cout << "Failed open file " << file << std::endl;
        #else
                etiss::log(etiss::ERROR,std::string("Failed to open file ")+file);
        #endif
        return false;
    }
    if (!etiss::fault::parseXML(faults,in,std::cout)){
        #ifdef NO_ETISS
                std::cout << "Failed parse file " << file << std::endl;
        #else
                etiss::log(etiss::ERROR,std::string("Failed to parse file ")+file);
        #endif
        return false;
    }
    bool ok = true;
    for (size_t i = 0;i<faults.size();++i){
        if (!addFault(faults[i])){
            #ifdef NO_ETISS
                    std::cout << "Failed to add Fault: " << faults[i].name_ << std::endl;
            #else
                    etiss::log(etiss::ERROR,std::string("Failed to add Fault "),faults[i]);
            #endif
            ok = false;
        }
    }
    return ok;
}


#if CXX0X_UP_SUPPORTED
static std::mutex & faults_sync(){
    static std::mutex mu;
    return mu;
}
#endif
static std::map<int32_t,Fault> & faults(){
    static std::map<int32_t,Fault> map;
    return map;
}
void Stressor::clear(){
#if CXX0X_UP_SUPPORTED
    std::lock_guard<std::mutex> lock(faults_sync());
#endif
	faults().clear();
}

bool Stressor::addFault(const Fault & f){


#if CXX0X_UP_SUPPORTED
    std::lock_guard<std::mutex> lock(faults_sync());
#endif

    std::map<int32_t,Fault>::iterator find = faults().find(f.id_);
    if (find != faults().end())
        return false;

    faults().insert(std::pair<int32_t,Fault>(f.id_,f));

    for (std::vector<Trigger>::const_iterator iter = f.triggers.begin();iter != f.triggers.end();++iter){
            Injector::ptr iptr = iter->getInjector();
            if (iptr){
                iptr->addTrigger(*iter,f.id_);
                std::cout << "added trigger " << iter->toString() << std::endl;
            } else {
                /// TODO signal error and roll back
            }
    }

    return true;

}

bool Stressor::firedTrigger(const Trigger & triggered,int32_t fault_id,Injector * injector,uint64_t time_ps)
{

#if CXX0X_UP_SUPPORTED
    std::lock_guard<std::mutex> lock(faults_sync());
#endif
    std::map<int32_t,Fault>::iterator find = faults().find(fault_id);
    if (find != faults().end()){
        for (std::vector<etiss::fault::Action>::iterator iter = find->second.actions.begin();iter != find->second.actions.end();++iter){
            if (iter->getType() == etiss::fault::Action::INJECTION){
                addFault(iter->getFault());
            } else {
                if (iter->getInjectorAddress().getInjector()){
#if CXX0X_UP_SUPPORTED
                    if (iter->getInjectorAddress().getInjector().get() != injector)
#else
                    if (iter->getInjectorAddress().getInjector() != injector)
#endif
                    {
#ifndef NO_ETISS
                        etiss::log(etiss::WARNING,"action injector is not the injector that triggered this event. threadsafety must be ensured by user.",find->second,*iter);
#endif
                    }
                    std::string err;
                    if (!iter->getInjectorAddress().getInjector()->applyAction(find->second,*iter,err)){
#ifdef NO_ETISS
                    std::cout << "Failed to apply action. Fault: " << fault_id  << " [" << err << "]"<< std::endl;
#else
                    etiss::log(etiss::ERROR,std::string("Failed to apply action "),find->second,*iter,err);
#endif
                    }
                    return true;
                } else {
#ifdef NO_ETISS
                    std::cout << "Failed to find action target. Fault: " << fault_id << std::endl;
#else
                    etiss::log(etiss::ERROR,std::string("Failed to find action target"),find->second,*iter);
#endif
                }
            }
        }
    } else {
#ifdef NO_ETISS
                std::cout << "Failed to find triggered Fault: " << fault_id << std::endl;
#else
                etiss::log(etiss::ERROR,std::string("Failed to find triggered Fault: "),fault_id);
#endif
    }

    return true;
}

}

}

