#include "cpu_etiss_sc.h"

// ETISS_System callbacks

static void system_call_syncTime (void * handle,ETISS_CPU * cpu)
{
    sc_core::sc_time cputime(cpu->cpuTime_ps,SC_PS);
	sc_core::sc_time simtime = sc_core::sc_time_stamp();
	if (cputime > simtime){
		sc_core::sc_time diff = cputime-simtime;
		wait(diff);
	}
}

template <bool read,bool instr>
inline etiss_int32 bus_access(CpuETISSSC & ecpu,void * handle, ETISS_CPU * cpu, etiss_uint64 addr,etiss_uint8 * buffer,etiss_uint32 length){

    if (ecpu.pendingreset){
		ecpu.pendingreset = false;
		//std::cout << "resetting" << std::endl;
		return etiss::RETURNCODE::RESET;
	}

    // sync time before bus access
	system_call_syncTime(handle,cpu);

	// allocate resource
	tlm::tlm_generic_payload tr;
	sc_core::sc_time delay;

	// configure packet
	unsigned char eptr = 0xFF;
	tr.set_command(read?tlm::TLM_READ_COMMAND:tlm::TLM_WRITE_COMMAND);
	tr.set_address(addr);
	tr.set_data_ptr((unsigned char *)buffer); // NOTE: unsigned char* must be 8bit // NOTE: endianness is handled by the cpu. binary images don't need conversion
	tr.set_data_length(length);
	if (!((CpuETISSSC *)handle)->no_byte_enable_){
		tr.set_byte_enable_length(1);
		tr.set_byte_enable_ptr(&eptr);
	}
	tr.set_streaming_width(length);
	tr.set_dmi_allowed(false);
	tr.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

    if (instr){
        ecpu.instr_isock->b_transport(tr, delay);
    } else {
    	//std::cout << (read?"dread: ":"dwrite: ") << std::hex << addr << std::endl;
        ecpu.data_isock->b_transport(tr, delay);
    }


	//update cpu time
	etiss::uint64 d = (etiss::uint64)(delay.to_seconds() * 1000000000000.0);
	etiss::uint64 cycles = d / cpu->cpuCycleTime_ps;
	if (d > cycles*cpu->cpuCycleTime_ps)
		cycles++;
	cpu->cpuTime_ps += cycles * cpu->cpuCycleTime_ps;


	// copy response
	int response = tr.get_response_status();

	// translate response
	if (response != tlm::TLM_OK_RESPONSE) {
		return etiss::RETURNCODE::DBUS_READ_ERROR;
	}

	return etiss::RETURNCODE::NOERROR;

}

static etiss_int32 system_call_iread (void * handle, ETISS_CPU * cpu, etiss_uint64 addr,etiss_uint32 length)
{
    uint8_t buffer[32]; // assuming no read access larger than 256 bits
#if ETISS_DEBUG
    if (unlikely(length > 32)){
        etiss::log(etiss::FATALERROR,"Buffer for instruction read is too small.",ETISS_SRCLOC);
    }
#endif
    return bus_access<true,true>(*(CpuETISSSC *)handle,handle, cpu,addr,buffer,length);

}
static etiss_int32 system_call_iwrite (void * handle, ETISS_CPU * cpu, etiss_uint64 addr,etiss_uint8 * buffer,etiss_uint32 length)
{
    return bus_access<false,true>(*(CpuETISSSC *)handle,handle, cpu,addr,buffer,length);
}

static etiss_int32 system_call_dread (void * handle, ETISS_CPU * cpu, etiss_uint64 addr,etiss_uint8 * buffer,etiss_uint32 length)
{
    return bus_access<true,false>(*(CpuETISSSC *)handle,handle, cpu,addr,buffer,length);
}
static etiss_int32 system_call_dwrite (void * handle, ETISS_CPU * cpu, etiss_uint64 addr,etiss_uint8 * buffer,etiss_uint32 length)
{
    return bus_access<false,false>(*(CpuETISSSC *)handle,handle, cpu,addr,buffer,length);
}


static etiss_int32 system_call_dbg_read (void * handle, etiss_uint64 addr,etiss_uint8 * buffer,etiss_uint32 length)
{

    tlm::tlm_generic_payload  tr;

	// configure packet
	unsigned char eptr = 0xFF;
	tr.set_command(tlm::TLM_READ_COMMAND);
	tr.set_address(addr);
	tr.set_data_ptr((unsigned char *)buffer); // NOTE: unsigned char* must be 8bit // NOTE: endianness is handled by the cpu. binary images don't need conversion
	tr.set_data_length(length);
	if (!((CpuETISSSC *)handle)->no_byte_enable_){
		tr.set_byte_enable_length(1);
		tr.set_byte_enable_ptr(&eptr);
	}
	tr.set_streaming_width(length);
	tr.set_dmi_allowed(false);
	tr.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

	//std::cout << "iread: " << std::hex << addr << std::endl;
	unsigned int response_len = ((CpuETISSSC *)handle)->instr_isock->transport_dbg(tr);
	
	// translate response
	if (response_len != length) {
		return etiss::RETURNCODE::IBUS_READ_ERROR;
	}

	return etiss::RETURNCODE::NOERROR;
}

static etiss_int32 system_call_dbg_write (void * handle, etiss_uint64 addr,etiss_uint8 * buffer,etiss_uint32 length)
{
    tlm::tlm_generic_payload  tr;

	// configure packet
	unsigned char eptr = 0xFF;
	tr.set_command(tlm::TLM_WRITE_COMMAND);
	tr.set_address(addr);
	tr.set_data_ptr((unsigned char *)buffer); // NOTE: unsigned char* must be 8bit // NOTE: endianness is handled by the cpu. binary images don't need conversion
	tr.set_data_length(length);
	if (!((CpuETISSSC *)handle)->no_byte_enable_){
		tr.set_byte_enable_length(1);
		tr.set_byte_enable_ptr(&eptr);
	}
	tr.set_streaming_width(length);
	tr.set_dmi_allowed(false);
	tr.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

	unsigned int response_len = ((CpuETISSSC *)handle)->instr_isock->transport_dbg(tr);

	// translate response
	if (response_len != length) {
		return etiss::RETURNCODE::IBUS_READ_ERROR;
	}

	return etiss::RETURNCODE::NOERROR;
}



// /ETISS_System callbacks

CpuETISSSC::TerminationHelper::TerminationHelper(CpuETISSSC * parent) :  parent_(parent){

}
CpuETISSSC::TerminationHelper::~TerminationHelper(){

}
etiss::int32 CpuETISSSC::TerminationHelper::execute(){
	if (parent_->pendingreset){
		parent_->pendingreset = false;
		//std::cout << "resetting" << std::endl;
		return etiss::RETURNCODE::RESET;
	}
	if (parent_->terminate){
		return etiss::RETURNCODE::CPUFINISHED;
	}
	return etiss::RETURNCODE::NOERROR;
}
std::string CpuETISSSC::TerminationHelper::_getPluginName()const{
	return "CpuETISSSC::TerminationHelper";
}


CpuETISSSC::CpuETISSSC(std::shared_ptr<etiss::CPUCore> cpu,etiss::InterruptType type,bool threadsafe) :
	CpuSystemCInterfaceSC(cpu?cpu->getName().c_str():"INVALID",cpu?(cpu->getInterruptVector()?cpu->getInterruptVector()->width():0):0),
	core_(cpu),
	core(cpu.get()),
	terminate(false),
	terminated(true),
	pendingreset(false),
	no_byte_enable_(false)
{
	if (!core){
#if __cpp_exceptions
		throw "Failed to init ETISS processor wrapper (CpuETISSSC)";
#else
		// using std::cerr+abort due to possible -fno-exceptions.
		std::cerr << "Failed to init ETISS processor wrapper (CpuETISSSC)" << std::endl;
		abort();
#endif
	}

	terminationHelper = std::shared_ptr<TerminationHelper>(new TerminationHelper(this),[](TerminationHelper*th){delete th;}); // add plugin for graceful cpu termination
	core->addPlugin(terminationHelper);
	irqhandler = std::shared_ptr<etiss::InterruptHandler>(new etiss::InterruptHandler(core->getInterruptVector(),core->getArch(),type,threadsafe)); // allocate irq handler
	sc_spawn_options opt;
    opt.set_stack_size(1024*1024*10);
	threadid = sc_spawn( sc_bind(&CpuETISSSC::cpuThread, this), 0 ,&opt); // spawn cpu execution thread

	// init ETISS_System
	handle = this;
	
	this->iread = system_call_iread;
	this->iwrite = system_call_iwrite;
	this->dread = system_call_dread;
	this->dwrite = system_call_dwrite;
	this->dbg_read = system_call_dbg_read;
	this->dbg_write = system_call_dbg_write;
	this->syncTime = system_call_syncTime;

}
CpuETISSSC::~CpuETISSSC(){
	if (!terminated){ // check if etiss::CPUCore::execute has been properly terminated
		sc_core::sc_time cputime(core->getState()->cpuTime_ps,SC_PS);
		sc_core::sc_time simtime = sc_core::sc_time_stamp();
		if (cputime+sc_get_time_resolution() > simtime){
			sc_core::sc_time diff = cputime-simtime;
			diff = diff + sc_get_time_resolution();
			terminate = true;
			sc_start(diff);	// continue simulation until etiss::CPUCore::execute can exit
			terminate = false;
			if (!terminated){
				etiss::log(etiss::ERROR,"SystemCBridge: failed to continue simulation until etiss::CPUCore::execute could exit");
			}
		} else {
			etiss::log(etiss::ERROR,"SystemCBridge failed to evaluate a possible cpu termination time. etiss::CPUCore::execute is assumed to not have been gracefully terminated. Skipping cleanup!");
			return;
		}

	}
	if (terminated){
		core->removePlugin(irqhandler);
		core->removePlugin(terminationHelper);
	}
}

void CpuETISSSC::reset(bool state) {
	pendingreset = state;
}
void CpuETISSSC::updateIRQState(unsigned index,bool state){
	std::cout << "updated irq"<<index<<": " << state<< std::endl;
	irqhandler->setLine(index,state,(etiss::uint64)(sc_core::sc_time_stamp().to_seconds()*1000000000000.0));
}
void CpuETISSSC::cpuThread(){
	if (core==0)
		return;
	terminated = false;
	etiss::int32 rc = core->execute(*this); // execute cpu
	terminated = true;
	const char * msg  = etiss::RETURNCODE::getErrorMessages()[rc];
	const char * rcn = etiss::RETURNCODE::getErrorNames()[rc];
	std::cout << core->getName() << " exited with code 0x" << std::hex << rc << std::dec << "(" << (rcn?rcn:"") << ": "<< (msg?msg:"") << ")" << std::endl;
}
