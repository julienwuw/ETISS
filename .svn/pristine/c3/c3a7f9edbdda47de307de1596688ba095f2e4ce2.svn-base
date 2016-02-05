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

#ifndef ETISS_PLUGIN_ERRORINJECTION_PLUGIN_H_
#define ETISS_PLUGIN_ERRORINJECTION_PLUGIN_H_

#include "etiss/Plugin.h"

#include <string>
#include <list>

namespace etiss {

	namespace plugin {

		namespace errorInjection {

			/**
				@brief Register error injection class. errors may be injected after blocks.
				@detail if needed BlockAccurateHandler::execute may be called from within the cpu thread at any time to apply errors
			*/
			class BlockAccurateHandler : public etiss::CoroutinePlugin {
			public:

				class Error {
				public:
					Error(std::string reg,unsigned errorid,etiss::uint64 time_ps,etiss::uintMax xor_,etiss::uintMax and_ = (etiss::uintMax)(etiss::intMax)-1,etiss::uintMax or_ = 0);
					std::string reg;
					unsigned errorid;
					etiss::uint64 time_ps;
					etiss::uintMax xor_;
					etiss::uintMax and_;
					etiss::uintMax or_;
				};

				BlockAccurateHandler();
				~BlockAccurateHandler();

				/**
					@brief schedule an error
					@param time_ps time of activation in picoseconds
					@param errorid some usedefined id
					@param register a register name that is defined by the used etiss::CPUArch
				*/
				void add(etiss::uint64 time_ps,unsigned errorid,std::string register_,etiss::uintMax xor_,etiss::uintMax and_ = (etiss::uintMax)(etiss::intMax)-1,etiss::uintMax or_ = 0);

				/**
					@brief call to apply errors
				*/
				virtual etiss::int32 execute();

				/**
					@brief reads a file and adds the errors.
					@detail <pre>
						Syntax:
							TIME_IN_NANOSECONDS;AFFECTED_BIT[;ERROR_ID]

						NOTE: 	the ";ERROR_ID" part is optional. No spaces may exist inbetween the values

						Example:
							1000;3
							2000;0;1234

						above example schedules an error at time:
							1000 ns: bit number 3 will be flipped e.g. @999ns: 0x00000000 @1001ns: 0x00000008
							2000 ns: bit number 0 will be flipped e.g. @1999ns: 0x00000008 @2100ns: 0x00000009

						NOTE: 	due to the infrequent execution of this plugin (usually only after a block)
							there may be a large delay between scheduled time and application of the error

						</pre>
				*/
				void parseFile(std::string filename,std::string reg);

				virtual std::string _getPluginName() const;

				virtual void init(ETISS_CPU * cpu,ETISS_System * system,CPUArch * arch);
				virtual void cleanup() ;

			private:
				ETISS_CPU * cpu;
				ETISS_System * system;
				CPUArch * arch;
				std::list<Error> errors_;
				etiss::uint64 last_time_ps;
				etiss::uint64 next_time_ps;
			};

		}

	}

}

#endif
