
#include "etiss/jit/ReturnCode.h"
#include "etiss/Plugin.h"
#include "etiss/VirtualStruct.h"


namespace etiss {

namespace plugin {

namespace fault {


class SwitchSystem : public etiss::InterruptListenerPlugin{

public:

	virtual bool interruptWrite(unsigned bit,bool value) = 0;

	int32_t iread(uint64_t & time_ps,uint64_t addr,uint8_t * buf,uint32_t len);
	int32_t iwrite(uint64_t & time_ps,uint64_t addr,uint8_t * buf,uint32_t len);
	int32_t dread(uint64_t & time_ps,uint64_t addr,uint8_t * buf,uint32_t len);
	int32_t dwrite(uint64_t & time_ps,uint64_t addr,uint8_t * buf,uint32_t len);

};

}

}

}

