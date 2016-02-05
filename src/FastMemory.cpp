

#include "etiss/FastMemory.h"
#include <cstring>
#include "etiss/jit/ReturnCode.h"

static etiss_int32 system_call_iread (void * handle, ETISS_CPU * cpu, etiss_uint64 addr,etiss_uint32 length)
{
    return 0;
}
static etiss_int32 system_call_iwrite (void * handle, ETISS_CPU * cpu, etiss_uint64 addr,etiss_uint8 * buffer,etiss_uint32 length)
{
    return etiss::RETURNCODE::IBUS_WRITE_ERROR;
}

static etiss_int32 system_call_dread (void * handle, ETISS_CPU * cpu, etiss_uint64 addr,etiss_uint8 * buffer,etiss_uint32 length)
{
	memcpy(buffer,((uint8_t*)handle)+(size_t)addr,length);
    return 0;
}
static etiss_int32 system_call_dwrite (void * handle, ETISS_CPU * cpu, etiss_uint64 addr,etiss_uint8 * buffer,etiss_uint32 length)
{
    memcpy(((uint8_t*)handle)+(size_t)addr,buffer,length);
    return 0;
}


static etiss_int32 system_call_dbg_read (void * handle, etiss_uint64 addr,etiss_uint8 * buffer,etiss_uint32 length)
{
    memcpy(buffer,((uint8_t*)handle)+(size_t)addr,length);
    return 0;
}

static etiss_int32 system_call_dbg_write (void * handle, etiss_uint64 addr,etiss_uint8 * buffer,etiss_uint32 length)
{
    memcpy(((uint8_t*)handle)+(size_t)addr,buffer,length);
    return 0;
}

static void system_call_syncTime (void * handle,ETISS_CPU * cpu)
{
    
}


std::shared_ptr<ETISS_System> etiss::createFastMemory(size_t size){
	
	ETISS_System * ret = new ETISS_System();
	memset(ret,0,sizeof(ETISS_System));
	
	ret->iread = &system_call_iread;
    ret->iwrite = &system_call_iwrite;

    ret->dread = &system_call_dread;
    ret->dwrite = &system_call_dwrite;

    ret->dbg_read = &system_call_dbg_read;
    ret->dbg_write = &system_call_dbg_write;

    ret->syncTime = &system_call_syncTime;

    ret->handle = new uint8_t[size];
	
}
