#include "SystemCBridge.h"


SystemCBridge::TerminationHelper::TerminationHelper(SystemCBridge * parent) : parent_(parent){

}
SystemCBridge::TerminationHelper::~TerminationHelper(){

}
etiss::int32 SystemCBridge::TerminationHelper::execute(){
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
std::string SystemCBridge::TerminationHelper::_getPluginName()const{
	return "SystemCBridge::TerminationHelper";
}


SystemCBridge::SystemCBridge(sc_module_name name,unsigned irqcount,std::shared_ptr<etiss::CPUCore> cpu,etiss::InterruptType type,bool threadsafe) :
	SystemCInterface(name,irqcount) ,
	terminate(false),
	terminated(false),
	cpu_(cpu),
	terminationHelper_(new SystemCBridge::TerminationHelper(this))
{

	irqhandler = std::shared_ptr<etiss::InterruptHandler>(new etiss::InterruptHandler(cpu->getInterruptVector(),cpu->getArch(),type,threadsafe)); // allocate irq handler

	cpu_->addPlugin(irqhandler); // add irq handler to cpu

    sc_spawn_options opt;
    opt.set_stack_size(1024*1024*10);

	threadid = sc_spawn( sc_bind(&SystemCBridge::cpuThread, this),0,&opt ); // spawn cpu execution thread

	pendingreset = false; // no initial reset

	cpu->addPlugin(terminationHelper_); // helper function to cleanly exit etiss::CPUCore::execute
}
SystemCBridge::~SystemCBridge(){
	if (!terminated){ // check if etiss::CPUCore::execute has been properly terminated
		sc_core::sc_time cputime(cpu_->getState()->cpuTime_ps,SC_PS);
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
	cpu_->removePlugin(irqhandler);
	cpu_->removePlugin(terminationHelper_);
}
etiss::int32 SystemCBridge::iread(ETISS_CPU * cpu, etiss::uint64 addr,etiss::uint32 len){
	return etiss::RETURNCODE::NOERROR; // currently not used. if instruction cache timing needs to simulated then this function needs to be implemented (same as dread but with i_bus socket) AND
}
etiss::int32 SystemCBridge::iwrite(ETISS_CPU * cpu, etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len){
	return etiss::RETURNCODE::IBUS_WRITE_ERROR; // not supported
}
void _syncTime(ETISS_CPU * cpu){
	sc_core::sc_time cputime(cpu->cpuTime_ps,SC_PS);
	sc_core::sc_time simtime = sc_core::sc_time_stamp();
	if (cputime > simtime){
		sc_core::sc_time diff = cputime-simtime;
		wait(diff);
	}
}
etiss::int32 SystemCBridge::dread(ETISS_CPU * cpu, etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len){

	if (pendingreset){
		pendingreset = false;
		//std::cout << "resetting" << std::endl;
		return etiss::RETURNCODE::RESET;
	}

	_syncTime(cpu);

	// allocate resource
	tlm::tlm_generic_payload * tr = rescout.checkout();
	sc_core::sc_time delay;

	// configure packet
	tr->set_command(tlm::TLM_READ_COMMAND);
	tr->set_address(addr);
	tr->set_data_ptr((unsigned char *)buf); // NOTE: unsigned char* must be 8bit // NOTE: endianness is handled by the cpu. binary images don't need conversion
	tr->set_data_length(len);
	tr->set_streaming_width(len);
	tr->set_dmi_allowed(false);
	tr->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);


	SystemCInterface::d_bus->b_transport(*tr, delay);


	//update cpu time
	etiss::uint64 d = (etiss::uint64)(delay.to_seconds() * 1000000000000.0);
	etiss::uint64 cycles = d / cpu->cpuCycleTime_ps;
	if (d > cycles*cpu->cpuCycleTime_ps)
		cycles++;
	//cpu->cpuTime_ps += cycles * cpu->cpuCycleTime_ps;


	// copy response
	int response = tr->get_response_status();

	//deallocate resource
	rescout.checkin(tr);

	// translate response
	if (response != tlm::TLM_OK_RESPONSE) {
		return etiss::RETURNCODE::DBUS_READ_ERROR;
	}

	return etiss::RETURNCODE::NOERROR;

}
etiss::int32 SystemCBridge::dwrite(ETISS_CPU * cpu, etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len){

	if (pendingreset){
		pendingreset = false;
		//std::cout << "resetting" << std::endl;
		return etiss::RETURNCODE::RESET;
	}

	_syncTime(cpu);

	// allocate resource
	tlm::tlm_generic_payload * tr = rescout.checkout();
	sc_core::sc_time delay;

	// configure packet
	tr->set_command(tlm::TLM_WRITE_COMMAND);
	tr->set_address(addr);
	tr->set_data_ptr((unsigned char *)buf); // NOTE: unsigned char* must be 8bit // NOTE: endianness is handled by the cpu. binary images don't need conversion
	tr->set_data_length(len);
	tr->set_streaming_width(len);
	tr->set_dmi_allowed(false);
	tr->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);


	SystemCInterface::d_bus->b_transport(*tr, delay);


	//update cpu time
	etiss::uint64 d = (etiss::uint64)(delay.to_seconds() * 1000000000000.0);
	etiss::uint64 cycles = d / cpu->cpuCycleTime_ps;
	if (d > cycles*cpu->cpuCycleTime_ps)
		cycles++;
	//cpu->cpuTime_ps += cycles * cpu->cpuCycleTime_ps;


	// copy response
	int response = tr->get_response_status();

	//deallocate resource
	rescout.checkin(tr);

	// translate response
	if (response != tlm::TLM_OK_RESPONSE) {
		return etiss::RETURNCODE::DBUS_WRITE_ERROR;
	}

	return etiss::RETURNCODE::NOERROR;

}
etiss::int32 SystemCBridge::dbg_read(etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len){
	// allocate resource
	tlm::tlm_generic_payload * tr = rescout.checkout();

	// configure packet
	tr->set_command(tlm::TLM_READ_COMMAND);
	tr->set_address(addr);
	tr->set_data_ptr((unsigned char *)buf); // NOTE: unsigned char* must be 8bit // NOTE: endianness is handled by the cpu. binary images don't need conversion
	tr->set_data_length(len);
	tr->set_streaming_width(len);
	tr->set_dmi_allowed(false);
	tr->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);


	unsigned int response_len = SystemCInterface::i_bus->transport_dbg(*tr);


	//deallocate resource
	rescout.checkin(tr);

	// translate response
	if (response_len != len) {
		return etiss::RETURNCODE::IBUS_READ_ERROR;
	}

	return etiss::RETURNCODE::NOERROR;
}
etiss::int32 SystemCBridge::dbg_write(etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len){
	return etiss::RETURNCODE::IBUS_WRITE_ERROR;
}

void SystemCBridge::syncTime(ETISS_CPU * cpu) {
	sc_core::sc_time cputime(cpu->cpuTime_ps,SC_PS);
	sc_core::sc_time simtime = sc_core::sc_time_stamp();
	//std::cout << "TIME: " << cputime << std::endl;
	if (cputime > simtime){
		sc_core::sc_time diff = cputime-simtime;
		wait(diff);
	}
}
void SystemCBridge::reset(bool state) {
	pendingreset = state;
}
void SystemCBridge::updateIRQState(unsigned index,bool state){
	//std::cout << "updated irq"<<+index<<": " << state<< std::endl;
	irqhandler->setLine(index,state,(etiss::uint64)(sc_core::sc_time_stamp().to_seconds()*1000000000000.0));
}
void SystemCBridge::cpuThread(){
	if (cpu_==0)
		return;
	terminated = false;
	etiss::int32 rc = cpu_->execute(*this); // execute cpu
	terminated = true;
	const char * msg  = etiss::RETURNCODE::getErrorMessages()[rc];
	const char * rcn = etiss::RETURNCODE::getErrorNames()[rc];
	std::cout << cpu_->getName() << " exited with code 0x" << std::hex << rc << std::dec << "(" << (rcn?rcn:"") << ": "<< (msg?msg:"") << ")" << std::endl;
	if (terminate){
		sc_stop();
	}
}

