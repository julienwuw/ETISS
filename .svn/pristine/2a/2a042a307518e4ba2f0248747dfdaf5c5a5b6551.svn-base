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

@date July 28, 2014

@version 0.1

*/
/**
	@file

	@brief conatins a convinience class that can be wrapped as a ETISS_System structure

	@detail

*/

#ifndef ETISS_INCLUDE_SYSTEM_H_
#define ETISS_INCLUDE_SYSTEM_H_
#include "etiss/jit/CPU.h"
#include "etiss/jit/System.h"
#include "etiss/jit/ReturnCode.h"

#include <memory>

namespace etiss
{
/**
	basic system io and time sync. to increase performance use ETISS_System structure
*/
class  System
{
public:
    inline virtual ~System() {}
    /**
    	@return 0 if no error occurred
    */
    virtual etiss::int32 iread(ETISS_CPU * cpu, etiss::uint64 addr,etiss::uint32 len) = 0;
    /**
    	@return 0 if no error occurred
    */
    virtual etiss::int32 iwrite(ETISS_CPU * cpu, etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len) = 0;
    /**
    	@return 0 if no error occurred
    */
    virtual etiss::int32 dread(ETISS_CPU * cpu, etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len) = 0;
    /**
    	@return 0 if no error occurred
    */
    virtual etiss::int32 dwrite(ETISS_CPU * cpu, etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len) = 0;
    /**
    	@return 0 if no error occurred
    */
    virtual etiss::int32 dbg_read(etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len) = 0;
    /**
    	@return 0 if no error occurred
    */
    virtual etiss::int32 dbg_write(etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len) = 0;
    /**
    	@brief syncs simulation time
    */
    virtual void syncTime(ETISS_CPU * cpu) = 0;
};

class SimpleSystem : public System
{
public:
    inline virtual ~SimpleSystem() {}
    virtual etiss::int32 iread(ETISS_CPU * cpu, etiss::uint64 addr,etiss::uint32 len);
    virtual etiss::int32 iwrite(ETISS_CPU * cpu, etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len);
    virtual etiss::int32 dread(ETISS_CPU * cpu, etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len);
    virtual etiss::int32 dwrite(ETISS_CPU * cpu, etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len);
    virtual etiss::int32 dbg_read(etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len);
    virtual etiss::int32 dbg_write(etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len);
    virtual void syncTime(ETISS_CPU * cpu);

    virtual bool read(bool debug,ETISS_CPU * cpu,etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len) = 0;
    virtual bool write(bool debug,ETISS_CPU * cpu,etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len) = 0;
};

/**
	@brief wraps a etiss::System in a ETISS_System structure.
	@see
*/
extern std::shared_ptr<ETISS_System> wrap(etiss::System * sys);

}

#endif
