#ifndef ETISS_SYSTEMC_SYSTEMCBRIDGE_H_
#define ETISS_SYSTEMC_SYSTEMCBRIDGE_H_
#include "SystemCInterface.h"
#include "ResourceCheckout.h"
#include "etiss/ETISS.h"
/**
	@brief implements SystemCInterface and etiss::System for an etiss::CPUCore. Memory accesses and time synchronization are mapped to systemc/tml objects and functions
*/
class SystemCBridge : public etiss::System, public SystemCInterface{
private:
	/**
		@brief simple helper plugin to return etiss::RETURNCODE::CPUFINISHED at end of the systemc simulation for gracefull termination
	*/
	class TerminationHelper : public etiss::CoroutinePlugin {
	public:
		TerminationHelper(SystemCBridge * parent);
		virtual ~TerminationHelper();
		/**
			@return etiss::RETURNCODE::CPUFINISHED if SystemCBridge gets deleted
		*/
		virtual etiss::int32 execute();
		virtual std::string _getPluginName() const;
	private:
		SystemCBridge * parent_;
	};
	friend class TerminationHelper;
public:
	SC_HAS_PROCESS(SystemCBridge);
	SystemCBridge(sc_module_name name,unsigned irqcount,std::shared_ptr<etiss::CPUCore> cpu,etiss::InterruptType type = etiss::EDGE_TRIGGERED,bool threadsafe = false);
	virtual ~SystemCBridge();

	// memory access
	virtual etiss::int32 iread(ETISS_CPU * cpu, etiss::uint64 addr,etiss::uint32 len);
	virtual etiss::int32 iwrite(ETISS_CPU * cpu, etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len);
	virtual etiss::int32 dread(ETISS_CPU * cpu, etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len);
	virtual etiss::int32 dwrite(ETISS_CPU * cpu, etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len);
	virtual etiss::int32 dbg_read(etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len);
	virtual etiss::int32 dbg_write(etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len);
	// synchronize time
	virtual void syncTime(ETISS_CPU * cpu);
	// reset cpu
	virtual void reset(bool state);
protected:
	virtual void updateIRQState(unsigned index,bool state);
	virtual void cpuThread();
private:
	sc_core::sc_process_b* threadid; // currently not used
	bool terminate;
	bool terminated;
	bool pendingreset;
	std::shared_ptr<etiss::InterruptHandler> irqhandler;
	std::shared_ptr<etiss::CPUCore> cpu_;
	ResourceCheckout<tlm::tlm_generic_payload> rescout;
	std::shared_ptr<etiss::Plugin> terminationHelper_;
};
#endif
