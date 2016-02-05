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
#ifndef ETISS_INCLUDE_GDB_GDBSERVER_H_
#define ETISS_INCLUDE_GDB_GDBSERVER_H_

#include "etiss/jit/CPU.h"
#include "etiss/jit/System.h"
#include "etiss/CPUArch.h"
#include "etiss/IntegratedLibrary/gdb/GDBConnection.h"

#include "etiss/Plugin.h"

#include <memory>

namespace etiss {

	namespace plugin {

		namespace gdb {

			/**
				@brief structure to store breakpoints
			*/
			class BreakpointDB {
			public:
				BreakpointDB();
				inline bool isEmpty(){
					return instrbrkpt_ == 0;
				}
				inline etiss::uint32 get(etiss::uint64 addr){
					if (unlikely(instrbrkpt_ == 0))
						return 0;
					unsigned a1 = (addr)&0xFFFF;
					if (unlikely(instrbrkpt_[a1] != 0)){
						unsigned a2 = (addr>>16)&0xFFFF;
						if (unlikely(instrbrkpt_[a1][a2] != 0)){
							unsigned a3 = (addr>>32)&0xFFFF;
							if (unlikely(instrbrkpt_[a1][a2][a3] != 0)){
								unsigned a4 = (addr>>48)&0xFFFF;
								std::cout << "Breakpoint hit: " << std::hex << (addr<<2) << std::dec << std::endl;
								return instrbrkpt_[a1][a2][a3][a4];
							}
						}
					}
					return 0;
				}
				void set(etiss::uint64 addr,etiss::uint32 val);

			private:
				etiss::uint32 **** instrbrkpt_; ///< important: index maps are reversed to instruction pointer e.g pointer(0x0102030405060708) [POINTER != ADDRESS] -> instrbrkpt_[0x0708][0x0506][0x0304][0x0201]
			};


			/**
				@brief gdb server implementation that is used as a plugin in etiss
			*/
			class Server :public etiss::CoroutinePlugin,public etiss::TranslationPlugin,public etiss::SystemWrapperPlugin{
			public:

				Server(etiss::plugin::gdb::PacketProtocol & pp);

				virtual ~Server();

				virtual etiss::int32 preInstructionCallback();

				virtual etiss::int32 preMemoryAccessCallback(etiss::uint64 addr,etiss::uint32 len,bool data,bool read);

				virtual etiss::int32 execute(); // called before block execution, check for BREAK command

				virtual void process(etiss::CodeBlock & block,unsigned index); // add instruction breakpoint check

				virtual void finalizeInstrSet(etiss::instr::ModedInstructionSet & ) const;

				virtual void finalizeCodeBlock(etiss::CodeBlock & ) const;

				/**

					@see GDBSystemWrapper.cpp
				*/
				virtual ETISS_System * wrap(ETISS_CPU * cpu,ETISS_System * system); // wrap for memory breakpoints
				/**

					@see GDBSystemWrapper.cpp
				*/
				virtual ETISS_System * unwrap(ETISS_CPU * cpu,ETISS_System * system); // undo wrapping

				virtual void * getPluginHandle(); //handle is pointer to this object

				virtual void init(ETISS_CPU * cpu,ETISS_System * system,CPUArch * arch);

				virtual void cleanup();

			protected:
				virtual void handlePacket(bool block);
				virtual std::string _getPluginName() const;
			protected:
				etiss::plugin::gdb::PacketProtocol & con_;
				CPUArch * arch_;
				ETISS_CPU * cpu_;
				ETISS_System * system_;
				bool status_paused_;
				bool gdb_status_paused_;
				unsigned status_step_;
				bool status_pending_jump_;
				bool status_pending_kill_;
				etiss::uint64 status_jumpaddr_;
				BreakpointDB breakpoints_;
				unsigned execute_skip_count;
				unsigned execute_skip_index;
			private:
				std::shared_ptr<Connection> cinst_;
			public:
                static Server * createTCPServer(std::map<std::string,std::string> options);
				static Server * createTCPServer(int port);
			};
		}

	}

}

#endif

