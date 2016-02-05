
#include "SimpleMemory.h"

void SimpleMemory::b_transport_i(int id, tlm::tlm_generic_payload &gp, sc_core::sc_time &t)
{

	dbg_transport(0,gp);
	
	//t = t + sc_time(100,SC_NS);
	
	return;
	
}

void SimpleMemory::b_transport_d(int id, tlm::tlm_generic_payload &gp, sc_core::sc_time &t)
{
	dbg_transport(0,gp);
	
	//t = t + sc_time(100,SC_NS);
	
	return;
}

unsigned SimpleMemory::dbg_transport(int,tlm::tlm_generic_payload &gp){

	sc_dt::uint64 addr = gp.get_address();
	unsigned char * data = gp.get_data_ptr();
	unsigned int     len = gp.get_data_length();
	
	// check address
	if (addr >= DEBUGSYSTEM_MEMBLOCKSIZE*2 || addr+len >= DEBUGSYSTEM_MEMBLOCKSIZE*2){ 
		gp.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
		return 0;
	}
	
	// handle command
	if (gp.get_command() == tlm::TLM_READ_COMMAND){
		memcpy(data,mem+addr,len);
	} else if (gp.get_command() == tlm::TLM_WRITE_COMMAND){
		memcpy(mem+addr,data,len);
	} else {
		gp.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
		return 0;
	}
	
	gp.set_response_status(tlm::TLM_OK_RESPONSE);
	
	return len;

}

SimpleMemory::SimpleMemory(sc_module_name nm): sc_module(nm)
{
	tsktForCPU_i.register_transport_dbg(this, &SimpleMemory::dbg_transport,0);
	tsktForCPU_i.register_b_transport(this, &SimpleMemory::b_transport_i,0);
	tsktForCPU_d.register_transport_dbg(this, &SimpleMemory::dbg_transport,0);
	tsktForCPU_d.register_b_transport(this, &SimpleMemory::b_transport_d,0);
}

bool SimpleMemory::load(etiss::uint64 addr,const char * file){
	std::ifstream in;
	in.open(file,std::ifstream::binary);
	if (!in.is_open())
		return false;
	etiss::uint8 byte;
	while (in.good()){
		byte = (etiss::uint8) in.get();
		if (in.good()){
			if (addr< DEBUGSYSTEM_MEMBLOCKSIZE*2){
				mem[addr] = byte;
			} else {
				std::cout << "ERROR: failed to load data to debug system memory: invalid address (" << std::hex << addr << std::dec << ")" << std::endl;
				in.close();
				return false;
			}
			addr++;
		}
	}
	in.close();
	return true;
}
