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

#ifndef ETISS_INCLUDE_GDB_GDBCONNECTION_H_
#define ETISS_INCLUDE_GDB_GDBCONNECTION_H_


#include <string>

namespace etiss {

	namespace plugin {

		namespace gdb {
	
			class Connection;
			
			/**
				@brief implements gdb's packet protocol	
			*/
			class PacketProtocol {
			friend class Connection;
			private:
				PacketProtocol(Connection & connection);
			public:
				virtual bool available(bool block = false);
				virtual std::string rcv(bool & isnotification);
				virtual bool snd(std::string answer,bool isnotification);
			private:
				virtual bool _available(bool block);
				virtual void tryReadPacket();
				std::string buffer;
				std::string command;
				bool command_isnotification;
				Connection & con;
				bool cfg_noack_;
			};
		
			/**
				@brief interface for gdb connections. implemented by UnixTCPGDBConnection.h . use PacketProtocol (Connection::getPacketProtocol) for communication with gdb
			*/
			class Connection {
			friend class PacketProtocol;
			public:
				Connection();
				virtual ~Connection();
				virtual bool available() = 0;
				virtual std::string rcv() = 0;
				virtual bool snd(std::string answer) = 0;
				virtual PacketProtocol & getPacketProtocol();
				virtual bool isRelyable();
				virtual bool pendingBREAK();
				virtual void clearBREAK();
			protected:
				bool pending_break_;
			private:
				PacketProtocol packproc_;
			};
		
		
	
		}

	}

}

#endif
