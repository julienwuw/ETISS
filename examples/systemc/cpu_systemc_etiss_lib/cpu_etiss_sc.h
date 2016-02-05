#ifndef CPU_ETISS_SC_H
#define CPU_ETISS_SC_H
#include "cpu_systemcinterface_sc.h"
#include "etiss/ETISS.h"

class CpuETISSSC : public ETISS_System,public CpuSystemCInterfaceSC
{
private:
	/**
		@brief simple helper plugin to return etiss::RETURNCODE::CPUFINISHED at end of the systemc simulation for gracefull termination
	*/
	class TerminationHelper : public etiss::CoroutinePlugin {
	public:
		TerminationHelper(CpuETISSSC * parent);
		virtual ~TerminationHelper();
		/**
			@return etiss::RETURNCODE::CPUFINISHED if CpuETISSSC gets deleted
		*/
		virtual etiss::int32 execute();
		virtual std::string _getPluginName() const;
	private:
		CpuETISSSC * parent_;
	};
	friend class TerminationHelper;
private:
	std::shared_ptr<etiss::CPUCore> core_;
public:
	etiss::CPUCore * const core;	sc_core::sc_process_b* threadid; // currently not used
private:
	bool terminate;
	bool terminated;
public:
	bool pendingreset; ///< needs to be public but may not be modified by user
	bool no_byte_enable_; ///< may be chenged to disable byte enable pointer and length; byte enable is not used by ETISS
private:
	std::shared_ptr<etiss::InterruptHandler> irqhandler;
	std::shared_ptr<etiss::Plugin> terminationHelper;

public:
	SC_HAS_PROCESS(CpuETISSSC);
	CpuETISSSC(std::shared_ptr<etiss::CPUCore> cpu,etiss::InterruptType type = etiss::EDGE_TRIGGERED,bool threadsafe = false);
	virtual ~CpuETISSSC();

protected:
	virtual void reset(bool state);
	virtual void updateIRQState(unsigned index,bool state);

protected:
	virtual void cpuThread();

};
#endif
