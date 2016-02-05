
#ifndef NO_ETISS
    #include "etiss/fault/Fault.h"
    #include "etiss/fault/Trigger.h"
    #include "etiss/fault/Injector.h"
    #include "etiss/fault/xml/pugixml.hpp"
#else
    #include "fault/Fault.h"
    #include "fault/Trigger.h"
    #include "fault/Injector.h"
    #include "fault/xml/pugixml.hpp"
#endif

#if MUTEX_SUPPORTED
#include <mutex>
#endif


#if CXX0X_UP_SUPPORTED == 0
#define static_assert(x,y)
#endif

namespace etiss{
namespace fault{
namespace xml{

/**
    Parser/writer structure:

    class and field structure is closely modeled by the xml structure. each class is a node and each field is either a sub node or an attribute.
    This allows for a simple parsing concept. the template function parse() is implemented for each type that needs to be read and is called recursively for fields of different types.
    parsed values are written directly into the fields. This requires all fields to be public/accessible
    e.g.
\code
    C++:

        class Fault {
            class Trigger {
                [...]
            };
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
            getAttribute("name",...)

\endcode

*/


static bool getAttribute(const pugi::xml_node & node,const std::string & attr_name,std::string & dst,Diagnostics & diag){
    bool first = true;
    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()){
        if (hasName(attr,attr_name)){
            if (first){
                dst = attr.value();
                first = false;
            } else {
                diag.unexpectedNode(node,std::string("Duplicated attribute: ")+attr_name);
            }
        }
    }
    return !first;
}
static bool setAttribute(pugi::xml_node & node,const std::string & attr_name,const std::string & src,Diagnostics & diag){
    node.append_attribute(attr_name.c_str()).set_value(src.c_str());
    return true;
}
static bool getAttribute(const pugi::xml_node & node,const std::string & attr_name,int32_t & dst,Diagnostics & diag){
    std::string val;
    if (!getAttribute(node,attr_name,val,diag))
        return false;
    std::stringstream(val) >> dst; /// TODO propper conversion
    return true;
}
static bool setAttribute(pugi::xml_node & node,const std::string & attr_name,const int32_t & src,Diagnostics & diag){
    static_assert(sizeof(int32_t) <= sizeof(long long),"pugixml cannot handle int32_t natively. custom string conversion required");
    node.append_attribute(attr_name.c_str()).set_value((long long)src);
    return true;
}



template<>
bool parse<std::vector<etiss::fault::Fault> >(pugi::xml_node node,std::vector<etiss::fault::Fault> & dst,Diagnostics & diag){

    bool ret = true;
    for (pugi::xml_node cnode = node.first_child(); cnode; cnode = cnode.next_sibling()){
        if (hasName(cnode,"fault")){ // handle fault node
            Fault f;
            if (parse<etiss::fault::Fault>(cnode,f,diag)){
                dst.push_back(f);
            } else {
                ret = false;
            }
        } else {
            diag.ignoredNode(cnode,"non \"fault\" node in fault list.");
        }
    }
    return ret;
}

template<>
bool write<std::vector<etiss::fault::Fault> >(pugi::xml_node node,const std::vector<etiss::fault::Fault> & src,Diagnostics & diag){

    bool ret = true;
    for (size_t i = 0;i<src.size();++i){
        ret = ret && write(node.append_child("fault"),src[i],diag);
    }
    return ret;
}

}

static int32_t uniqueFaultId(){
#if MUTEX_SUPPORTED
    static std::mutex mu;
    std::lock_guard<std::mutex> lock(mu);
#endif
    static int32_t cid = -1;
    return cid--;
}
Fault::Fault(){
    id_ = uniqueFaultId();
}
std::string Fault::toString() const{

    pugi::xml_document doc;
    doc.load("<?xml version=\"1.0\"?>");

    etiss::fault::xml::Diagnostics diag;

    etiss::fault::xml::write<etiss::fault::Fault>(doc.append_child("fault"),*this,diag);

    std::stringstream ss;

    doc.save(ss);

    return ss.str();

}

void Fault::resolveTime(uint64_t time){
    for (std::vector<Trigger>::iterator iter = triggers.begin();iter != triggers.end();++iter){
        iter->resolveTime(time);
    }
}
bool Fault::isResoved() const{
	for (std::vector<Trigger>::const_iterator iter = triggers.begin(); iter != triggers.end(); ++iter){
		if (!iter->isResolved())
			return false;
	}
	return true;
}

#if ETISS_FAULT_XML

bool parseXML(std::vector<Fault> & vec,std::istream & input,std::ostream & diagnostics_out){

    pugi::xml_document doc; // xml document

    pugi::xml_parse_result pr = doc.load(input); // load from stream

    if (!pr){ // load failure
        diagnostics_out << "failed to load xml from stream: " << pr.description()<< std::endl;
        return false;
    }

    etiss::fault::xml::Diagnostics diag;

    bool ret = parse(doc.document_element(),vec,diag); // parse document

    diag.print(diagnostics_out);

    return ret;

}

bool writeXML(const std::vector<Fault> & vec,std::ostream & out,std::ostream & diagnostics_out){
    pugi::xml_document doc;

    doc.load("<?xml version=\"1.0\"?>");

    etiss::fault::xml::Diagnostics diag;

    bool ret = write(doc.append_child("faults"),vec,diag); // write document

    doc.save(out);

    diag.print(diagnostics_out);

    return ret;
}

namespace xml {


template<>
bool parse<etiss::fault::Fault>(pugi::xml_node node,etiss::fault::Fault & f,Diagnostics & diag){
    bool ret = true;
    /*ret = ret &*/ getAttribute(node,"name",f.name_,diag); // optional
    /*ret = ret &*/ getAttribute(node,"id_",f.id_,diag); // optional
    for (pugi::xml_node cnode = node.first_child(); cnode; cnode = cnode.next_sibling()){
        if (hasName(cnode,"triggers")){
            for (pugi::xml_node ccnode = cnode.first_child(); ccnode; ccnode = ccnode.next_sibling()){
                if (hasName(ccnode,"trigger")){
                    etiss::fault::Trigger t;
                    if (parse<etiss::fault::Trigger>(ccnode,t,diag)){
                        f.triggers.push_back(t);
                    } else {
                        ret = false;
                    }
                } else {
                    diag.ignoredNode(ccnode,"\"trigger\" node expected");
                }
            }
        } else if (hasName(cnode,"actions")) {
            for (pugi::xml_node ccnode = cnode.first_child(); ccnode; ccnode = ccnode.next_sibling()){
                if (hasName(ccnode,"action")){
                    etiss::fault::Action t;
                    if (parse<etiss::fault::Action>(ccnode,t,diag)){
                        f.actions.push_back(t);
                    } else {
                        ret = false;
                    }
                } else {
                    diag.ignoredNode(ccnode,"\"trigger\" node expected");
                }
            }
        } else {
            diag.ignoredNode(cnode,"unknown node");
        }
    }

    return ret;
}
template<>
bool write<etiss::fault::Fault>(pugi::xml_node node,const etiss::fault::Fault & f,Diagnostics & diag){
    bool ok = true;
    ok = ok && setAttribute(node,"name",f.name_,diag);
    ok = ok && setAttribute(node,"id",f.id_,diag);
    pugi::xml_node triggers = node.append_child("triggers");
    for (std::vector<etiss::fault::Trigger>::const_iterator iter = f.triggers.begin();iter != f.triggers.end();++iter) {
        ok = ok && write<etiss::fault::Trigger>(triggers.append_child("trigger"),*iter,diag);
    }
    pugi::xml_node actions = node.append_child("actions");
    for (std::vector<etiss::fault::Action>::const_iterator iter = f.actions.begin();iter != f.actions.end();++iter) {
        ok = ok && write<etiss::fault::Action>(actions.append_child("action"),*iter,diag);
    }
    return ok;
}

}


#endif

}
}
