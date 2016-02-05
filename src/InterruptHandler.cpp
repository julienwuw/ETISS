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

@date July 29, 2014

@version 0.1

*/
/**
	@file

	@brief implements etiss/InterruptHandler.h

	@detail

*/
#include "etiss/InterruptHandler.h"

using namespace etiss;

InterruptHandler::InterruptHandler(etiss::InterruptVector* interruptVector,std::shared_ptr<CPUArch> arch,InterruptType itype,bool sync) : itype_(itype),sync_(sync),vector_(interruptVector),cpuarch_(arch){
	empty_ = true;
}

InterruptHandler::~InterruptHandler(){

}

bool interrupt_handler_cmp(const std::pair<etiss::uint64,std::pair<unsigned,bool> > & o1, const std::pair<etiss::uint64,std::pair<unsigned,bool> > & o2){
	return o1.first < o2.first;
}

void InterruptHandler::setLine(unsigned line,bool state,etiss::uint64 time_ps){
	if (vector_ == 0)
		return;

	if (sync_)
		mu_.lock();
	pending_.push_back(std::make_pair(time_ps,std::make_pair(line,state))); // add interrupt to list
	pending_.sort(interrupt_handler_cmp);
	empty_ = false;
	if (sync_)
		mu_.unlock();
}

etiss::int32 InterruptHandler::execute(){

	etiss::uint64 time_ps = plugin_cpu_->cpuTime_ps;

	if (vector_ == 0)
		return etiss::RETURNCODE::NOERROR;

	if (sync_)
		mu_.lock();

	bool mayinterrupt = (itype_ != EDGE_TRIGGERED); // edge triggered may only interrupt once after a rising edge

	// fast check for empty pending list
	if (!empty_){

		while (!pending_.empty() && pending_.front().first <= time_ps){ // apply events from past
			std::pair<etiss::uint64,std::pair<unsigned,bool> > & cur = pending_.front();
			switch (itype_){
				case EDGE_TRIGGERED:
					if (cur.second.second) { // if line high
						if (ed_raised_.find(cur.second.first) == ed_raised_.end()){ // if line was low
							vector_->clear();
							vector_->setBit(cur.second.first,cur.second.second);
							ed_raised_.insert(cur.second.first);
							mayinterrupt = true;
						}
					} else { // line low
						ed_raised_.erase(cur.second.first);
					}
					break;
				case LEVEL_TRIGGERED:
					vector_->setBit(cur.second.first,cur.second.second);
					break;
				default:
					std::cout << "ERROR: interrupt type is invalid" << stream_code_info << std::endl;
			}
			pending_.pop_front();
		}

		empty_ = pending_.empty();

	}

	if (sync_)
		mu_.unlock();

	return (mayinterrupt &&vector_->isActive())?etiss::RETURNCODE::INTERRUPT:etiss::RETURNCODE::NOERROR;
}

std::string InterruptHandler::_getPluginName() const{
	return "InterruptHandler";
}



