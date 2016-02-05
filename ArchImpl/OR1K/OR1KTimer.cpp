
#include "OR1KTimer.h"

OR1KTimer::OR1KTimer(){
	_timer_last_ps = 0;

}
OR1KTimer::~OR1KTimer(){}
etiss::int32 OR1KTimer::execute(){



	etiss::uint32 & TTMR = *(((OR1K*)plugin_cpu_)->TTMR);
	etiss::uint32 mode = TTMR>>30;

	if (mode != 0) { // 0 = disabled

		etiss::uint32 & TTCR = *(((OR1K*)plugin_cpu_)->TTCR);

		etiss::uint64 count = ((plugin_cpu_->cpuTime_ps - ((OR1K*)plugin_cpu_)->_timer_last_ps)>>15)*3;  // ca. 90 MHZ

		switch (mode){
		case 1: // self rearm
			if (((TTMR & 0x0FFFFFFF) <= count)){
				TTCR = 0;
				((OR1K*)plugin_cpu_)->_timer_last_ps = plugin_cpu_->cpuTime_ps;
				if (likely((TTMR & 0x30000000U) == 0x20000000U)){
					TTMR = TTMR | 0x10000000U;
					return OR1K_TICKTIMEREXCEPTION;
				}
			} else {
				TTCR = (etiss::uint32)count;
			}
			break;
		case 2: // stop counting
			if (((TTMR & 0x0FFFFFFF) <= count)){
				if (TTCR < (TTMR & 0x0FFFFFFF)){
					TTCR = (etiss::uint32)count;
                    if (likely((TTMR & 0x30000000U) == 0x20000000U)){
						TTMR = TTMR | 0x10000000U;
						return OR1K_TICKTIMEREXCEPTION;
					}
				}

			} else {
				TTCR = (etiss::uint32)count;
			}
			break;
		case 3: // continue counting
			if (((TTMR & 0x0FFFFFFF) <= count)){
				if (TTCR < (TTMR & 0x0FFFFFFF)){
					TTCR = (etiss::uint32)count;
                    if (likely((TTMR & 0x30000000U) == 0x20000000U)){
						TTMR = TTMR | 0x10000000U;
						return OR1K_TICKTIMEREXCEPTION;
					}
				}

			}
			if (TTCR > ((etiss::uint32)count)){ // wrap around
				TTCR = (etiss::uint32)count;
				((OR1K*)plugin_cpu_)->_timer_last_ps = plugin_cpu_->cpuTime_ps - (TTCR << 15);
			} else {
				TTCR = (etiss::uint32)count;
			}
			break;
		}

	}

	return etiss::RETURNCODE::NOERROR;
}
void OR1KTimer::changedRegister(const char * name){

	//etiss::log(etiss::ERROR,"changeRegister called ",name);

	if (name[0] == 'T'){
		if (name[1] == 'T'){
			if (name[2] == 'C'){
				if (name[3] == 'R'){
					if (name[4] == 0){
						((OR1K*)plugin_cpu_)->_timer_last_ps = plugin_cpu_->cpuTime_ps - (((*((OR1K*)plugin_cpu_)->TTCR) << 15));
					}
				}
			}
		}
	}
}
std::string OR1KTimer::_getPluginName() const{
	return "OR1KTimer";
}

