
#include "OR1KArch.h"


class OR1KTimer : public etiss::CoroutinePlugin, public etiss::RegisterDevicePlugin {
public:
	OR1KTimer();
	virtual ~OR1KTimer();
	virtual etiss::int32 execute();
	virtual void changedRegister(const char * name);
protected:
	virtual std::string _getPluginName() const ;
private:
	etiss_uint64 _timer_last_ps;
};
