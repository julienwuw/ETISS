#ifndef CPU_SYSTEMCINTERFACE_SC_H
#define CPU_SYSTEMCINTERFACE_SC_H
#include "systemc.h"
#include "tlm.h"
#include <tlm_utils/multi_passthrough_initiator_socket.h>

#ifndef CPU_SYSTEMCINTERFACE_BUS_WIDTH
	#define CPU_SYSTEMCINTERFACE_BUS_WIDTH 32
#endif

class CpuSystemCInterfaceSC : public sc_core::sc_module //, tlm::tlm_bw_transport_if<> 
{
	
        /**
		@brief this class allows sc_in<bool> instantiations on demand
	*/
	class IrqSC : public sc_core::sc_module {
	private:
		unsigned index_;
		CpuSystemCInterfaceSC & parent_;
	public:
		SC_HAS_PROCESS(IrqSC);
		IrqSC(sc_module_name name,unsigned index,CpuSystemCInterfaceSC & parent);
	public:
		sc_core::sc_in<bool> irq_in;
	private:
		void method();
	};
	friend class CpuSystemCInterfaceSC::IrqSC;
	/**
		@brief this class allows sc_in<bool> instantiation for a reset on demand
	*/
	
        class ResetSC : public sc_core::sc_module {
	private:
		CpuSystemCInterfaceSC & parent_;
	public:
		SC_HAS_PROCESS(ResetSC);
		ResetSC(sc_module_name name,CpuSystemCInterfaceSC & parent);
	public:
		sc_core::sc_in<bool> reset_in;
	private:
		void method();
	};
	friend class CpuSystemCInterfaceSC::ResetSC;
public:
	SC_HAS_PROCESS(CpuSystemCInterfaceSC);
	
	CpuSystemCInterfaceSC(sc_module_name name,unsigned irqcount);
	virtual ~CpuSystemCInterfaceSC();
	
	
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

        /*virtual tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload &trans,tlm::tlm_phase&phase,sc_core::sc_time& t) 
        {
		return tlm::TLM_COMPLETED;
        }

        virtual void invalidate_direct_mem_ptr(sc_dt::uint64 start_range, sc_dt::uint64 end_range)
        {

        }*/

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
	CpuSystemCInterfaceSC::IrqSC ** irqs_sc_;
	CpuSystemCInterfaceSC::ResetSC * reset_sc_;
public:
	const unsigned irqcount;
public:
	//tlm::tlm_initiator_socket<CPU_SYSTEMCINTERFACE_BUS_WIDTH> data_isock;
	//tlm::tlm_initiator_socket<CPU_SYSTEMCINTERFACE_BUS_WIDTH> instr_isock;
	tlm_utils::multi_passthrough_initiator_socket<CpuSystemCInterfaceSC> data_isock;
	tlm_utils::multi_passthrough_initiator_socket<CpuSystemCInterfaceSC> instr_isock;
};
#endif
