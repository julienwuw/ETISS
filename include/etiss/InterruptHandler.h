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

	@brief interrupt checking and signaling

	@detail

*/

#ifndef ETISS_INCLUDE_INTERRUPTHANDLER_H_
#define ETISS_INCLUDE_INTERRUPTHANDLER_H_

#include <mutex>
#include <vector>
#include <list>
#include <set>
#include "etiss/LibraryInterface.h"
#include "etiss/jit/types.h"
#include "etiss/CPUArch.h"
#include "etiss/InterruptVector.h"
#include "etiss/Plugin.h"

namespace etiss {

	/**
		interrupt types supported by the default implementation
	*/
	enum InterruptType {

		EDGE_TRIGGERED = 1,
		LEVEL_TRIGGERED

	};

	/**
		@brief class that handles interrupt signaling and checking. functions are declared virtual to allow customization
	*/
	class InterruptHandler : public etiss::CoroutinePlugin{
	public:
		InterruptHandler(etiss::InterruptVector* interruptVector,std::shared_ptr<etiss::CPUArch> arch,InterruptType itype = EDGE_TRIGGERED,bool sync = true);
		virtual ~InterruptHandler();
		/**
			@brief set the state of a line at a given time. changes will not be applied until flush(2) with a time_ps value equal or greater than this time_ps value is called
		*/
		virtual void setLine(unsigned line,bool state,etiss::uint64 time_ps);
		/**
			@brief apply interrupt changes to the InterruptVector
			@return etiss::RETURNCODE::INTERRUPT if an interrupt should occur
		*/
		virtual etiss::int32 execute();
		virtual std::string _getPluginName() const;
	protected:
		const InterruptType itype_;
		std::mutex mu_;
		const bool sync_;
		InterruptVector * const vector_;
		/** list: (time , (line ,state) ) */
		std::list<std::pair<etiss::uint64,std::pair<unsigned,bool> > > pending_;
		const std::shared_ptr<etiss::CPUArch> cpuarch_;
		std::set<unsigned> ed_raised_;
		bool empty_;
	};
}

#endif
