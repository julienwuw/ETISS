#include "etiss/IntegratedLibrary/InstructionAccurateCallback.h"
#include "etiss/Instruction.h"
#include "etiss/CPUCore.h"

extern "C"{
    void etiss_plugin_InstructionAccurateCallback(void*ptr){
        etiss::plugin::InstructionAccurateCallback & vvl = *(etiss::plugin::InstructionAccurateCallback*)ptr;
        vvl.call();
    }
}

namespace etiss
{

namespace plugin
{

InstructionAccurateCallback::InstructionAccurateCallback() {
    
}
InstructionAccurateCallback::~InstructionAccurateCallback(){

}

void InstructionAccurateCallback::initCodeBlock(etiss::CodeBlock & block)const
{
    block.fileglobalCode().insert("extern void etiss_plugin_InstructionAccurateCallback(void *); ");

}

void InstructionAccurateCallback::finalizeInstrSet(etiss::instr::ModedInstructionSet & mis) const{
    mis.foreach([this](etiss::instr::VariableInstructionSet & vis){
                vis.foreach([this](etiss::instr::InstructionSet & is){
                            is.foreach([this](etiss::instr::Instruction & i){
                                i.addCallback([this](etiss::instr::BitArray &,etiss::CodeSet & cs,etiss::instr::InstructionContext &){
                                                        etiss::CodePart & p = cs.append(etiss::CodePart::INITIALREQUIRED);
                                                        p.getRegisterDependencies().add("cpuTime_ps",8);
                                                        p.code() = std::string("etiss_plugin_InstructionAccurateCallback(") + getPointerCode() + ");";
                                                        return true;
                                                      },0);
                                       });
                            });
                });
}


std::string InstructionAccurateCallback::_getPluginName() const
{
    return std::string("InstructionAccurateCallback");
}

void InstructionAccurateCallback::call()
{
    plugin_core_->getStruct()->instructionAccurateCallback(plugin_cpu_->cpuTime_ps);
}

}

}
