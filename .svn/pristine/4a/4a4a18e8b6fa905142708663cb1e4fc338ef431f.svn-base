
#include "SystemCInterface.h"


SystemCInterface::IRQ::IRQ(sc_module_name name,unsigned index,SystemCInterface & parent) : index_(index),parent_(parent){

	SC_METHOD(method);
	sensitive << in;
	
}

void SystemCInterface::IRQ::method(){
	parent_.updateIRQState(index_,in.read());
}

SystemCInterface::Reset::Reset(sc_module_name name,SystemCInterface & parent) : parent_(parent){

	SC_METHOD(method);
	sensitive << in;
	
}

void SystemCInterface::Reset::method(){
	parent_.reset(in.read());
}

SystemCInterface::SystemCInterface(sc_module_name name,unsigned irqcount)  : sc_core::sc_module(name),irqcount(irqcount){
	reset_ = 0;
	irqs_ = new SystemCInterface::IRQ * [irqcount];
	for (unsigned i = 0;i<irqcount;i++){
		irqs_[i] = 0;
	}
}

SystemCInterface::~SystemCInterface() {
	for (unsigned i = 0;i<irqcount;i++){
		delete irqs_[i];
	}
	delete irqs_;
	delete reset_;
}

sc_core::sc_in<bool> * SystemCInterface::allocateReset(){
	if(reset_ == 0){
		reset_ = new SystemCInterface::Reset("reset",*this);
		return & (reset_->in);
	}
	return 0;
}

sc_core::sc_in<bool> * SystemCInterface::getReset(){
	if (reset_){
		return & (reset_->in);
	}
	return 0;
}

sc_core::sc_in<bool> * SystemCInterface::allocateIRQ(unsigned x) {
	if (x < irqcount){
		if (irqs_[x] == 0){
			irqs_[x] = new SystemCInterface::IRQ("irq",x,*this);
			return &(irqs_[x]->in);
		}
	}
	return 0;
}

sc_core::sc_in<bool> * SystemCInterface::getIRQ(unsigned x) {
	if (x <irqcount){
		if (irqs_[x] != 0){
			return &(irqs_[x]->in);
		}
	}
	return 0;
}
