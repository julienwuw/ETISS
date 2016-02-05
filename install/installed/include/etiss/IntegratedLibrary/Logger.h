
#ifndef ETISS_PLUGIN_LOGGER_H_
#define ETISS_PLUGIN_LOGGER_H_

#include "etiss/Plugin.h"

namespace etiss{

namespace plugin {

/**
	simple logger implementation.
	by overriding log it would also be possible to use this as a device mounted to a certain memory address. due to the function call overhead this is only suggested for testing purposes
*/
class Logger : public etiss::SystemWrapperPlugin{
public:

	Logger(uint64_t addr_value,uint64_t addr_mask);

	virtual ETISS_System * wrap(ETISS_CPU * cpu,ETISS_System * system); // wrap read/write redirection

	virtual ETISS_System * unwrap(ETISS_CPU * cpu,ETISS_System * system); // undo wrapping

	/**
		@attention if called by iread then the buf pointer is NULL
	*/
	virtual int32_t log(bool isread,uint64_t local_addr,uint8_t * buf,unsigned len); // called whenever a write(or read) occured to logger address

protected:
	inline virtual std::string _getPluginName() const { return std::string("Logger @") + etiss::toString(addr); }
private:
	uint64_t addr;
	uint64_t mask;
};

}

}

#endif
