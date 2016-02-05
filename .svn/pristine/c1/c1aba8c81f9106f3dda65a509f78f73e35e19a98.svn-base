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

	@brief simple test system implementation



*/

#ifndef ETISS_INCLUDE_DEBUGSYSTEM_H_
#define ETISS_INCLUDE_DEBUGSYSTEM_H_
#include "etiss/System.h"

namespace etiss {

#define DEBUGSYSTEM_MEMBLOCKSIZE 8*256*256

/**
	@brief simple etiss:System implementation for testing
*/
class  DebugSystem : public System{
public:
	DebugSystem();
	// memory access
	etiss::int32 iread(ETISS_CPU * cpu, etiss::uint64 addr,etiss::uint32 len);
	etiss::int32 iwrite(ETISS_CPU * cpu, etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len);
	etiss::int32 dread(ETISS_CPU * cpu, etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len);
	etiss::int32 dwrite(ETISS_CPU * cpu, etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len);
	etiss::int32 dbg_read(etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len);
	etiss::int32 dbg_write(etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len);

	// sync time
	void syncTime(ETISS_CPU * cpu);
	/**
		@brief loads a binary image from a file to the given address
	*/
	bool load(etiss::uint64 addr,const char * file);
	void swapEndian(unsigned align = 4);
private:
	etiss::uint8 mem[DEBUGSYSTEM_MEMBLOCKSIZE*2]; // mounted at 0
};

}

#endif
