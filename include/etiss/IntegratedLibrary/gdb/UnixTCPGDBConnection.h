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

@date September 2, 2014

@version 0.1

*/
/**
	@file

	@brief

	@detail




*/

#ifndef ETISS_INCLUDE_GDB_UNIXTCPGDBCONNECTION_H_
#define ETISS_INCLUDE_GDB_UNIXTCPGDBCONNECTION_H_
#include "etiss/config.h"

#if ETISS_USE_POSIX_SOCKET

#include "etiss/jit/types.h"
#include "etiss/IntegratedLibrary/gdb/GDBConnection.h"

namespace etiss {

	namespace plugin {

		namespace gdb {

			/**
				@brief implementation of TCP socket + server socket for gdb communication
			*/
			class UnixTCPGDBConnection : public Connection {
			public :
				UnixTCPGDBConnection(unsigned port = 2222);
				virtual ~UnixTCPGDBConnection();
				virtual bool available();
				bool _available(bool block);
				virtual std::string rcv();
				virtual bool snd(std::string answer);
			private:
				int socket_;
				bool valid_;
				int active_;
				bool active_valid_;
				etiss::uint8 buffer_[1024];
				unsigned buffer_pos_;
			};

		}

	}

}

#endif //ETISS_USE_POSIX_SOCKET


#endif
