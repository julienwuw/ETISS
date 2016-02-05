

#include "etiss/IntegratedLibrary/Logger.h"
#include <cstring>

namespace etiss{

namespace plugin {

// NOTE: no "pragma pack" needed since ETISS_System is already packed and this structure will not be accessed from runtime compiled code


// callbacks for system structure
//namespace {

struct LoggerSystem
{

    struct ETISS_System sys;

    Logger * this_;

    ETISS_System * orig;

    uint64_t mask;
    uint64_t addr;

};

etiss_int32 iread (void * handle, ETISS_CPU * cpu, etiss_uint64 addr,etiss_uint32 length){
	LoggerSystem * lsys = ((LoggerSystem*)handle);
	if ((addr&lsys->mask) == lsys->addr){
		return lsys->this_->log(true,addr&~lsys->mask,0,length);
	}
	ETISS_System* sys = lsys->orig;
	return sys->iread(sys->handle,cpu,addr,length);
}
etiss_int32 iwrite (void * handle, ETISS_CPU * cpu, etiss_uint64 addr,etiss_uint8 * buffer,etiss_uint32 length){
	LoggerSystem * lsys = ((LoggerSystem*)handle);
	if ((addr&lsys->mask) == lsys->addr){
		return lsys->this_->log(false,addr&~lsys->mask,buffer,length);
	}
	ETISS_System* sys = lsys->orig;
	return sys->iwrite(sys->handle,cpu,addr,buffer,length);
}

etiss_int32 dread (void * handle, ETISS_CPU * cpu, etiss_uint64 addr,etiss_uint8 * buffer,etiss_uint32 length){
	LoggerSystem * lsys = ((LoggerSystem*)handle);
	if ((addr&lsys->mask) == lsys->addr){
		return lsys->this_->log(true,addr&~lsys->mask,buffer,length);
	}
	ETISS_System* sys = lsys->orig;
	return sys->dread(sys->handle,cpu,addr,buffer,length);
}
etiss_int32 dwrite (void * handle, ETISS_CPU * cpu, etiss_uint64 addr,etiss_uint8 * buffer,etiss_uint32 length){
	LoggerSystem * lsys = ((LoggerSystem*)handle);
	if ((addr&lsys->mask) == lsys->addr){
		return lsys->this_->log(false,addr&~lsys->mask,buffer,length);
	}
	ETISS_System* sys = lsys->orig;
	return sys->dwrite(sys->handle,cpu,addr,buffer,length);
}


etiss_int32 dbg_read (void * handle, etiss_uint64 addr,etiss_uint8 * buffer,etiss_uint32 length){
	LoggerSystem * lsys = ((LoggerSystem*)handle);
	if ((addr&lsys->mask) == lsys->addr){
		return lsys->this_->log(true,addr&~lsys->mask,buffer,length);
	}
	ETISS_System* sys = lsys->orig;
	return sys->dbg_read(sys->handle,addr,buffer,length);
}

etiss_int32 dbg_write (void * handle, etiss_uint64 addr,etiss_uint8 * buffer,etiss_uint32 length){
	LoggerSystem * lsys = ((LoggerSystem*)handle);
	if ((addr&lsys->mask) == lsys->addr){
		return lsys->this_->log(false,addr&~lsys->mask,buffer,length);
	}
	ETISS_System* sys = lsys->orig;
	return sys->dbg_write(sys->handle,addr,buffer,length);
}

void syncTime (void * handle,ETISS_CPU * cpu){
	LoggerSystem * lsys = ((LoggerSystem*)handle);
	ETISS_System* sys = lsys->orig;
	sys->syncTime(sys->handle,cpu);
}

//}

Logger::Logger(uint64_t addr_value,uint64_t addr_mask) : addr(addr_value&addr_mask),mask(addr_mask) {
	if (mask == 0 && addr == 0){
		etiss::log(etiss::WARNING,"Logger instantiated with mask and address set to 0. this will redirect all read/writes exclusively to this logger instance.");
	}
}

ETISS_System * Logger::wrap(ETISS_CPU * cpu,ETISS_System * system){

	LoggerSystem * ret = new LoggerSystem();

	ret->sys.iread = &iread;
	ret->sys.iwrite = &iwrite;
	ret->sys.dread = &dread;
	ret->sys.dwrite = &dwrite;
	ret->sys.dbg_read = &dbg_read;
	ret->sys.dbg_write = &dbg_write;
	ret->sys.syncTime = &syncTime;

	ret->sys.handle = (void*)ret;

	ret->this_ = this;

	ret->orig = system;

	ret->addr = addr;
	ret->mask = mask;

	return (ETISS_System *)ret;

}

ETISS_System * Logger::unwrap(ETISS_CPU * cpu,ETISS_System * system){

	ETISS_System * ret = ((LoggerSystem*)system)->orig;

	delete system;

	return ret;

}

int32_t Logger::log(bool isread,uint64_t local_addr,uint8_t * buf,unsigned len){
	if (isread){
		memset(buf,0,len);
		return 0;
	}

	if (len <= 0)
		return 0;

	if (buf == 0)
		return 0;

	std::cout << (char) buf[len-1];

	std::flush(std::cout);

	return 0;

}

}

}

