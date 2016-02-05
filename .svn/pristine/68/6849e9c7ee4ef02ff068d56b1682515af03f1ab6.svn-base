
#include "cpu_systemcinterface_sc.h"


CpuSystemCInterfaceSC::IrqSC::IrqSC(sc_module_name name,unsigned index,CpuSystemCInterfaceSC & parent) : index_(index),parent_(parent){

	SC_METHOD(method);
	sensitive << irq_in;
	
}

void CpuSystemCInterfaceSC::IrqSC::method(){
	parent_.updateIRQState(index_,irq_in.read());
}

CpuSystemCInterfaceSC::ResetSC::ResetSC(sc_module_name name,CpuSystemCInterfaceSC & parent) : parent_(parent){

	SC_METHOD(method);
	sensitive << reset_in;
	
}

void CpuSystemCInterfaceSC::ResetSC::method(){
	parent_.reset(reset_in.read());
}

CpuSystemCInterfaceSC::CpuSystemCInterfaceSC(sc_module_name name,unsigned irqcount)  : 
	sc_core::sc_module(name),
	irqcount(irqcount),
        data_isock("data_isock"),
        instr_isock("instr_isock"){
	reset_sc_ = 0;
	irqs_sc_ = new CpuSystemCInterfaceSC::IrqSC * [irqcount];
	for (unsigned i = 0;i<irqcount;i++){
		irqs_sc_[i] = 0;
	}
}

CpuSystemCInterfaceSC::~CpuSystemCInterfaceSC() {
	for (unsigned i = 0;i<irqcount;i++){
		delete irqs_sc_[i];
	}
	delete irqs_sc_;
	delete reset_sc_;
}

sc_core::sc_in<bool> * CpuSystemCInterfaceSC::allocateReset(){
	if(reset_sc_ == 0){
		reset_sc_ = new CpuSystemCInterfaceSC::ResetSC("ResetSC",*this);
		return & (reset_sc_->reset_in);
	}
	return 0;
}

sc_core::sc_in<bool> * CpuSystemCInterfaceSC::getReset(){
	if (reset_sc_){
		return & (reset_sc_->reset_in);
	}
	return 0;
}

sc_core::sc_in<bool> * CpuSystemCInterfaceSC::allocateIRQ(unsigned x) {
	if (x < irqcount){
		if (irqs_sc_[x] == 0){
			irqs_sc_[x] = new CpuSystemCInterfaceSC::IrqSC("IrqSC",x,*this);
			return &(irqs_sc_[x]->irq_in);
		}
	}
	return 0;
}

sc_core::sc_in<bool> * CpuSystemCInterfaceSC::getIRQ(unsigned x) {
	if (x <irqcount){
		if (irqs_sc_[x] != 0){
			return &(irqs_sc_[x]->irq_in);
		}
	}
	return 0;
}
