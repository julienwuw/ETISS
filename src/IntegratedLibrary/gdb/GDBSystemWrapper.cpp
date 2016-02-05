/**

@copyright 
<pre>


	Copyright (c) 2014 Institute for Electronic Design Automation, TU Munich

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.


</pre>
@author Marc Greim <marc.greim@mytum.de>

@date July 29, 2014

@version 0.1

*/
/**
	@file
	
	@brief implements a ETISS_System wrapper to enable breakpoints

	@detail 

*/
#include <malloc.h>

#include "etiss/IntegratedLibrary/gdb/GDBServer.h"

using namespace etiss::plugin::gdb;

struct ETISS_GDBSystem {

	struct ETISS_System system;
	
	ETISS_System * sys_;
	
	etiss::plugin::gdb::Server * server_;

};

typedef struct ETISS_GDBSystem ETISS_GDBSystem;


etiss_int32 gdb_system_call_iread (void * handle, ETISS_CPU * cpu, etiss_uint64 addr,etiss_uint32 length){
	ETISS_GDBSystem* gdbsys = ((ETISS_GDBSystem*)handle);
	ETISS_System* sys = gdbsys->sys_;
	etiss::int32 exception = gdbsys->server_->preMemoryAccessCallback(addr,length,false,true);
	if (unlikely(exception != 0)){
		return exception;
	}
	return sys->iread(sys->handle,cpu,addr,length);
}
etiss_int32 gdb_system_call_iwrite (void * handle, ETISS_CPU * cpu, etiss_uint64 addr,etiss_uint8 * buffer,etiss_uint32 length){
	ETISS_GDBSystem* gdbsys = ((ETISS_GDBSystem*)handle);
	ETISS_System* sys = gdbsys->sys_;
	etiss::int32 exception = gdbsys->server_->preMemoryAccessCallback(addr,length,false,false);
	if (unlikely(exception != 0)){
		return exception;
	}
	return sys->iwrite(sys->handle,cpu,addr,buffer,length);
}

etiss_int32 gdb_system_call_dread (void * handle, ETISS_CPU * cpu, etiss_uint64 addr,etiss_uint8 * buffer,etiss_uint32 length){
	ETISS_GDBSystem* gdbsys = ((ETISS_GDBSystem*)handle);
	ETISS_System* sys = gdbsys->sys_;
	etiss::int32 exception = gdbsys->server_->preMemoryAccessCallback(addr,length,true,true);
	if (unlikely(exception != 0)){
		return exception;
	}
	return sys->dread(sys->handle,cpu,addr,buffer,length);
}
etiss_int32 gdb_system_call_dwrite (void * handle, ETISS_CPU * cpu, etiss_uint64 addr,etiss_uint8 * buffer,etiss_uint32 length){
	ETISS_GDBSystem* gdbsys = ((ETISS_GDBSystem*)handle);
	ETISS_System* sys = gdbsys->sys_;
	etiss::int32 exception = gdbsys->server_->preMemoryAccessCallback(addr,length,true,false);
	if (unlikely(exception != 0)){
		return exception;
	}
	return sys->dwrite(sys->handle,cpu,addr,buffer,length);
}


etiss_int32 gdb_system_call_dbg_read (void * handle, etiss_uint64 addr,etiss_uint8 * buffer,etiss_uint32 length){
	ETISS_GDBSystem* gdbsys = ((ETISS_GDBSystem*)handle);
	ETISS_System* sys = gdbsys->sys_;
	return sys->dbg_read(sys->handle,addr,buffer,length);
}

etiss_int32 gdb_system_call_dbg_write (void * handle, etiss_uint64 addr,etiss_uint8 * buffer,etiss_uint32 length){
	ETISS_GDBSystem* gdbsys = ((ETISS_GDBSystem*)handle);
	ETISS_System* sys = gdbsys->sys_;
	return sys->dbg_write(sys->handle,addr,buffer,length);
}

void gdb_system_call_syncTime (void * handle,ETISS_CPU * cpu){
	ETISS_GDBSystem* gdbsys = ((ETISS_GDBSystem*)handle);
	ETISS_System* sys = gdbsys->sys_;
	sys->syncTime(sys->handle,cpu);
}


ETISS_System * Server::wrap(ETISS_CPU * cpu,ETISS_System * sys){
	
	if (sys == 0)
		return 0;
		
	//return sys;
	
	ETISS_GDBSystem * ret = new ETISS_GDBSystem();
	
	ETISS_System * retsys = (ETISS_System *) ret;
	
	retsys->iread = gdb_system_call_iread;
	retsys->iwrite = gdb_system_call_iwrite;
	
	retsys->dread = gdb_system_call_dread;
	retsys->dwrite = gdb_system_call_dwrite;
	
	retsys->dbg_read = gdb_system_call_dbg_read;
	retsys->dbg_write = gdb_system_call_dbg_write;
	
	retsys->syncTime = gdb_system_call_syncTime;
	
	retsys->handle = (void*) ret;
	
	ret->server_ = this; 
	
	ret->sys_ = sys;
	
	return (ETISS_System *) ret;

}

ETISS_System * Server::unwrap(ETISS_CPU * cpu,ETISS_System * system){
	ETISS_GDBSystem * ret = (ETISS_GDBSystem *)system;
	system = ret->sys_;
	delete ret;
	return system;
}

