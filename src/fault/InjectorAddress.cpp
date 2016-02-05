
#ifndef NO_ETISS
#include "etiss/fault/InjectorAddress.h"
#include "etiss/fault/Injector.h"
#else
#include "fault/InjectorAddress.h"
#include "fault/Injector.h"
#endif

namespace etiss
{
namespace fault
{

InjectorAddress::InjectorAddress(){
    path_ = ":";
    iptr_ = 0;
}
InjectorAddress::InjectorAddress(const std::string & address){
	path_ = address;
	iptr_ = 0;
}
InjectorAddress::InjectorAddress(const InjectorAddress & cpy){
	*this = cpy;
}
InjectorAddress & InjectorAddress::operator=(const InjectorAddress & cpy){
	path_ = cpy.path_;
	iptr_ = cpy.iptr_;
	return *this;
}

#if CXX0X_UP_SUPPORTED

InjectorAddress::InjectorAddress(InjectorAddress && ia){
	operator=(ia);
}
InjectorAddress & InjectorAddress::operator=(InjectorAddress && ia){
	operator=((const InjectorAddress &) ia);
	return *this;
}

#endif

const std::string & InjectorAddress::getInjectorPath() const{
    return path_;
}
const Injector_ptr & InjectorAddress::getInjector() const{
    if (!iptr_)
        iptr_ = Injector::get(path_);
    return iptr_;
}

bool InjectorAddress::isResolved() const{
    return (bool)iptr_;
}

#if ETISS_FAULT_XML
namespace xml {

template <>
bool parse<etiss::fault::InjectorAddress>(pugi::xml_node node,etiss::fault::InjectorAddress & dst,Diagnostics & diag){
    std::string val;
    if (!parse<std::string>(node,val,diag)){
        return false;
    }
    dst = InjectorAddress(val);
    return true;
}
template <>
bool write<etiss::fault::InjectorAddress>(pugi::xml_node node,const etiss::fault::InjectorAddress & src,Diagnostics & diag){
    return write<std::string>(node,src.getInjectorPath(),diag);
}

template <>
bool parse<etiss::fault::InjectorAddress*>(pugi::xml_node node,etiss::fault::InjectorAddress * & dst,Diagnostics & diag){
    InjectorAddress val;
    if (!parse<etiss::fault::InjectorAddress>(node,val,diag)){
        dst = 0;
        return false;
    }
    dst = new InjectorAddress(val);
    return true;
}
template <>
bool write<const etiss::fault::InjectorAddress*>(pugi::xml_node node,const etiss::fault::InjectorAddress * const & src,Diagnostics & diag){
    if (!src)
        return false;
    return write(node,*src,diag);
}

}
#endif



}

}

