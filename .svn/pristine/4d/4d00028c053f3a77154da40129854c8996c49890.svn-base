#include "etiss/interfaces/Delegate.h"

namespace etiss
{
namespace interfaces
{

Delegate::Delegate(ETISS_System & system,ETISS_CPU & cpu) : system(system),cpu(cpu)
{

}

void Delegate::syncTime(uint64_t time_ps)
{
#if DEBUG
    if (time_ps < cpu.cpuTime_ps)
    {
        etiss::log(etiss::FATALERROR,"The cpu simulation time went backwards");
    }
#endif

    cpu.cpuTime_ps = time_ps;

    system.syncTime(system.handle,&cpu);

}

bool Delegate::read(bool ibus,uint64_t & time_ps,uint64_t addr,uint8_t * buf,unsigned len)
{

    //std::cout << "\nread at address 0x" << std::hex << addr << std::endl;

    if (injectedRead)
    {

        bool cont = false;

        bool handleNormal = false;

        bool ret = injectedRead(ibus,time_ps,addr,buf,len,cont,handleNormal);

        if (!cont)
            injectedRead = nullptr;

		if (!handleNormal){ // injectedRead may signal that read() should handle this call
            if (unlikely(snoopRead)){
                snoopRead(true,time_ps,addr,buf,len);
            }
			return ret;
		}

    }

#if DEBUG
    if (time_ps < cpu.cpuTime_ps)
    {
        etiss::log(etiss::FATALERROR,"The cpu simulation time went backwards");
    }
#endif

    cpu.cpuTime_ps = time_ps;

    bool ok = false;

    if (ibus)
    {

        int32_t code = system.iread(system.handle,&cpu,addr,len); // simulate read

        if ((code == etiss::RETURNCODE::NOERROR) || (code == etiss::RETURNCODE::GDBNOERROR)) // check return code
        {
            ok = true;
        }

        if (ok)
        {

            code = system.dbg_read(system.handle,addr,buf,len); // read data

            if ((code != etiss::RETURNCODE::NOERROR) && (code != etiss::RETURNCODE::GDBNOERROR))  // check return code
            {
                ok = false;
            }

        }

    }
    else
    {
        int32_t code = system.dread(system.handle,&cpu,addr,buf,len);  // read data

        if ((code == etiss::RETURNCODE::NOERROR) || (code == etiss::RETURNCODE::GDBNOERROR))  // check return code
        {
            ok = true;
        }

    }

    time_ps = cpu.cpuTime_ps;

    if (unlikely(snoopRead)){
        snoopRead(false,time_ps,addr,buf,len);
    }

    return ok;

}

bool Delegate::write(bool ibus,uint64_t & time_ps,uint64_t addr,uint8_t * buf,unsigned len)
{

	if (redirectedWrite)
    {

        bool cont = false;

        bool handleNormal = false;

        bool ret = redirectedWrite(ibus,time_ps,addr,buf,len,cont,handleNormal);

        if (!cont)
			redirectedWrite = std::function<bool(bool, uint64_t &, uint64_t, uint8_t *, unsigned, bool &, bool&)>();

		if (!handleNormal) // redirectedWrite may signal that write() should handle this call
			return ret;

    }

#if DEBUG
    if (time_ps < cpu.cpuTime_ps)
    {
        etiss::log(etiss::FATALERROR,"The cpu simulation time went backwards");
    }
#endif

    cpu.cpuTime_ps = time_ps;

    bool ok = false;

    if (ibus)
    {

        int32_t code = system.iwrite(system.handle,&cpu,addr,buf,len);  // read data

        if ((code == etiss::RETURNCODE::NOERROR) || (code == etiss::RETURNCODE::GDBNOERROR))  // check return code
        {
            ok = true;
        }

    }
    else
    {
        int32_t code = system.dwrite(system.handle,&cpu,addr,buf,len);  // read data

        if ((code == etiss::RETURNCODE::NOERROR) || (code == etiss::RETURNCODE::GDBNOERROR))  // check return code
        {
            ok = true;
        }

    }

    time_ps = cpu.cpuTime_ps;

    return ok;

}

} // namespace interfaces
} // namespace etiss

