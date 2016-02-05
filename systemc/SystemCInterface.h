#ifndef ETISS_SYSTEMC_SYSTEMCINTERFACE_H_
#define ETISS_SYSTEMC_SYSTEMCINTERFACE_H_
#include "systemc.h"

#include "tlm.h"
#include "tlm_utils/tlm_quantumkeeper.h"
#include "tlm_utils/simple_initiator_socket.h"


class SystemCInterface : public sc_core::sc_module {
	/**
		@brief this class allows sc_in<bool> instantiations on demand
	*/
	class IRQ : public sc_core::sc_module {
	private:
		unsigned index_;
		SystemCInterface & parent_;
	public:
		SC_HAS_PROCESS(IRQ);
		IRQ(sc_module_name name,unsigned index,SystemCInterface & parent);
	public:
		sc_core::sc_in<bool> in;
	private:
		void method();
	};
	friend class SystemCInterface::IRQ;
	/**
		@brief this class allows sc_in<bool> instantiation for a reset on demand
	*/
	class Reset : public sc_core::sc_module {
	private:
		SystemCInterface & parent_;
	public:
		SC_HAS_PROCESS(Reset);
		Reset(sc_module_name name,SystemCInterface & parent);
	public:
		sc_core::sc_in<bool> in;
	private:
		void method();
	};
	friend class SystemCInterface::Reset;
public:
	SC_HAS_PROCESS(SystemCInterface);
	
	SystemCInterface(sc_module_name name,unsigned irqcount);
	virtual ~SystemCInterface();
	
	
	/**
		@brief allocates the reset port
	*/
	virtual sc_core::sc_in<bool> * allocateReset();
	/**
		@brief returns the priviously allocated reset port
	*/
	virtual sc_core::sc_in<bool> * getReset();
	
	/**
		@brief allocates the interrupt line with the given index
	*/
	virtual sc_core::sc_in<bool> * allocateIRQ(unsigned x);
	/**
		@brief return a previously allocated interrupt line at the given index
	*/
	virtual sc_core::sc_in<bool> * getIRQ(unsigned x);

protected:
	/**
		@brief called when the state of the reset line changes
	*/
	virtual void reset(bool state) = 0;
	/**
		@brief called when the state of an interrupt line changes
	*/
	virtual void updateIRQState(unsigned index,bool state) = 0;
private:	
	SystemCInterface::IRQ ** irqs_;
	SystemCInterface::Reset * reset_;
public:
	const unsigned irqcount;
public:
	tlm_utils::simple_initiator_socket_tagged<SystemCInterface> d_bus;
	tlm_utils::simple_initiator_socket_tagged<SystemCInterface> i_bus;
};
#endif
