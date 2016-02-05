#ifndef NO_ETISS
#include "etiss/fault/Action.h"
#else
#include "fault/Action.h"
#endif

#include <sstream>

namespace etiss
{
namespace fault
{


void Action::ensure(Type t)
{
    if (type_ != t)
        throw "wrong action type";

}

Action::Action() : type_(NOP)
{

}

Action::Action(const InjectorAddress & inj,const std::string & command) : type_(COMMAND),inj_(inj),command_(command)
{


}

Action::Action(const InjectorAddress & inj,const std::string & field,unsigned bit) : type_(BITFLIP),inj_(inj),field_(field),bit_(bit)
{

}
Action::Action(const Fault & fault) : type_(INJECTION){
    fault_.push_back(fault);
}

Action::Type Action::getType() const
{
    return type_;
}

const InjectorAddress & Action::getInjectorAddress() const
{
    return inj_;
}

const std::string & Action::getCommand() const
{
    return command_;
}

/// BITFLIP only
const std::string & Action::getTargetField() const
{
    return field_;
}

/// BITFLIP only
unsigned Action::getTargetBit() const
{
    return bit_;
}

const Fault & Action::getFault() const{
    if (type_ != INJECTION )
        throw "Action doesn't have the type INJECTION: cannot call getFault()";
    return fault_.front();
}

std::string Action::toString() const{
    pugi::xml_document doc;
    doc.load("<?xml version=\"1.0\"?>");

    etiss::fault::xml::Diagnostics diag;

    etiss::fault::xml::write<etiss::fault::Action>(doc.append_child("action"),*this,diag);

    std::stringstream ss;

    doc.save(ss);

    return ss.str();
}

#if ETISS_FAULT_XML
namespace xml{
template<>
bool parse<etiss::fault::Action>(pugi::xml_node node,etiss::fault::Action & f,Diagnostics & diag){

    std::string type;
    if (!parse_attr(node,"type",type,diag)){
        diag.unexpectedNode(node,"Failed to parse type of action");
        return false;
    }

    if (type == "NOP"){
        f = Action();
        return true;
    } else if (type == "BITFLIP") {
        etiss::fault::InjectorAddress inj;
        if (!parse<etiss::fault::InjectorAddress>(findSingleNode(node,"injector",diag),inj,diag)){
            diag.unexpectedNode(node,"Failed to parse target injector");
            return false;
        }
        std::string field;
        if (!parse<std::string>(findSingleNode(node,"field",diag),field,diag)){
            diag.unexpectedNode(node,"Failed to parse target field");
            return false;
        }
        unsigned bit;
        if (!parse<unsigned>(findSingleNode(node,"bit",diag),bit,diag)){
            diag.unexpectedNode(node,"Failed to parse target bit");
            return false;
        }
        f = Action(inj,field,bit);
        return true;
    } else if (type == "COMMAND") {
        etiss::fault::InjectorAddress inj;
        if (!parse<etiss::fault::InjectorAddress>(findSingleNode(node,"injector",diag),inj,diag)){
            diag.unexpectedNode(node,"Failed to parse target injector");
            return false;
        }
        std::string command;
        if (!parse<std::string>(findSingleNode(node,"command",diag),command,diag)){
            diag.unexpectedNode(node,"Failed to parse target command");
            return false;
        }
        f = Action(inj,command);
        return true;
    } else if (type == "INJECTION") {
        etiss::fault::Fault inj;
        if (!parse<Fault>(findSingleNode(node,"fault",diag),inj,diag)){
            diag.unexpectedNode(node,"Failed to parse fault to inject");
            return false;
        }
        f = Action(inj);
        return true;
    } else {
        diag.unexpectedNode(node,std::string("Unknown type of action: ")+type);
        return false;
    }
    return false;
}
template<>
bool write<etiss::fault::Action>(pugi::xml_node node,const etiss::fault::Action & f,Diagnostics & diag){
    bool ok = true;
    switch (f.getType()){
    case etiss::fault::Action::NOP:
        return write_attr<std::string>(node,"type","NOP",diag);
        break;
    case etiss::fault::Action::BITFLIP:
        ok = ok & write_attr<std::string>(node,"type","BITFLIP",diag);
        ok = ok & write(node.append_child("injector"),f.getInjectorAddress(),diag);
        ok = ok & write<std::string>(node.append_child("field"),f.getTargetField(),diag);
        ok = ok & write<unsigned>(node.append_child("bit"),f.getTargetBit(),diag);
        break;
    case etiss::fault::Action::COMMAND:
        ok = ok & write_attr<std::string>(node,"type","COMMAND",diag);
        ok = ok & write<std::string>(node.append_child("command"),f.getCommand(),diag);
        break;
    case etiss::fault::Action::INJECTION:
        ok = ok & write_attr<std::string>(node,"type","INJECTION",diag);
        ok = ok & write<Fault>(node.append_child("fault"),f.getFault(),diag);
        break;
    }
    return false;
}

}
#endif


}

}
