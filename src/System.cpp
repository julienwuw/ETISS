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

@date November 5, 2014

@version 0.1

*/
/**
	@file

	@brief implements etiss/System.h. manly consists of the implementation of std::shared_ptr<ETISS_System> etiss::wrap(etiss::System * sys)

	@detail

*/

#include <malloc.h>

#include "etiss/System.h"


static etiss_int32 system_call_iread (void * handle, ETISS_CPU * cpu, etiss_uint64 addr,etiss_uint32 length)
{
    return ((etiss::System*)handle)->iread(cpu,addr,length);
}
static etiss_int32 system_call_iwrite (void * handle, ETISS_CPU * cpu, etiss_uint64 addr,etiss_uint8 * buffer,etiss_uint32 length)
{
    return ((etiss::System*)handle)->iwrite(cpu,addr,buffer,length);
}

static etiss_int32 system_call_dread (void * handle, ETISS_CPU * cpu, etiss_uint64 addr,etiss_uint8 * buffer,etiss_uint32 length)
{
    return ((etiss::System*)handle)->dread(cpu,addr,buffer,length);
}
static etiss_int32 system_call_dwrite (void * handle, ETISS_CPU * cpu, etiss_uint64 addr,etiss_uint8 * buffer,etiss_uint32 length)
{
    return ((etiss::System*)handle)->dwrite(cpu,addr,buffer,length);
}


static etiss_int32 system_call_dbg_read (void * handle, etiss_uint64 addr,etiss_uint8 * buffer,etiss_uint32 length)
{
    return ((etiss::System*)handle)->dbg_read(addr,buffer,length);
}

static etiss_int32 system_call_dbg_write (void * handle, etiss_uint64 addr,etiss_uint8 * buffer,etiss_uint32 length)
{
    return ((etiss::System*)handle)->dbg_write(addr,buffer,length);
}

static void system_call_syncTime (void * handle,ETISS_CPU * cpu)
{
    ((etiss::System*)handle)->syncTime(cpu);
}

std::shared_ptr<ETISS_System> etiss::wrap(etiss::System * sys)
{
    if (sys == 0)
        return 0;
    ETISS_System * ret = new ETISS_System();

    ret->iread = &system_call_iread;
    ret->iwrite = &system_call_iwrite;

    ret->dread = &system_call_dread;
    ret->dwrite = &system_call_dwrite;

    ret->dbg_read = &system_call_dbg_read;
    ret->dbg_write = &system_call_dbg_write;

    ret->syncTime = &system_call_syncTime;

    ret->handle = (void*) sys;

    return std::shared_ptr<ETISS_System>(ret);

}

#ifdef __cplusplus
extern "C" {
#endif
    int ETISS_System_isvalid(ETISS_System * sys)
    {
        return sys->iread != 0 && sys->iwrite != 0 && sys->dread != 0 && sys->dwrite != 0 && sys->syncTime != 0;
    }

#ifdef __cplusplus
}
#endif


namespace etiss
{

etiss::int32 SimpleSystem::iread(ETISS_CPU * cpu, etiss::uint64 addr,etiss::uint32 len)
{
	// disabled since this read function is only intended for timing purpose
	//if (!read(false,cpu,addr,0,len))
	//	return IBUS_READ_ERROR;

	return 0;
}
etiss::int32 SimpleSystem::iwrite(ETISS_CPU * cpu, etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len)
{
	if (!write(false,cpu,addr,buf,len))
		return etiss::RETURNCODE::IBUS_WRITE_ERROR;

	return 0;
}
etiss::int32 SimpleSystem::dread(ETISS_CPU * cpu, etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len)
{
	if (!read(false,cpu,addr,buf,len))
		return etiss::RETURNCODE::DBUS_READ_ERROR;

	return 0;
}
etiss::int32 SimpleSystem::dwrite(ETISS_CPU * cpu, etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len)
{
	if (!write(false,cpu,addr,buf,len))
		return etiss::RETURNCODE::IBUS_WRITE_ERROR;

	return 0;
}
etiss::int32 SimpleSystem::dbg_read(etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len)
{
	if (!read(true,0,addr,buf,len))
		return etiss::RETURNCODE::DBUS_READ_ERROR;

	return 0;
}
etiss::int32 SimpleSystem::dbg_write(etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len)
{
	if (!write(true,0,addr,buf,len))
		return etiss::RETURNCODE::DBUS_WRITE_ERROR;

	return 0;
}
void SimpleSystem::syncTime(ETISS_CPU * cpu)
{
	// NOP
}

}

