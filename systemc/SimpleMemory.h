#ifndef ETISS_SYSTEMC_SIMPLEMEMORY_H_
#define ETISS_SYSTEMC_SIMPLEMEMORY_H_

#include "etiss/DebugSystem.h"

#include "systemc.h"

#include "tlm.h"
#include <tlm_utils/simple_target_socket.h>

/**
	@brief simple memory implementation with tlm sockets
*/
class SimpleMemory : public sc_core::sc_module{
public:

	SimpleMemory(sc_module_name name);


	tlm_utils::simple_target_socket_tagged<SimpleMemory> tsktForCPU_i;
	tlm_utils::simple_target_socket_tagged<SimpleMemory> tsktForCPU_d;
	
	void b_transport_i(int id, tlm::tlm_generic_payload &gp, sc_core::sc_time &t);
	
	void b_transport_d(int id, tlm::tlm_generic_payload &gp, sc_core::sc_time &t);
	
	unsigned dbg_transport(int,tlm::tlm_generic_payload &gp);

	
	bool load(etiss::uint64 addr,const char * file);
private:
	etiss::uint8 mem[DEBUGSYSTEM_MEMBLOCKSIZE*2]; // mounted at 0 // DEBUGSYSTEM_MEMBLOCKSIZE defined in etiss/DebugSystem.h

};

#endif 
