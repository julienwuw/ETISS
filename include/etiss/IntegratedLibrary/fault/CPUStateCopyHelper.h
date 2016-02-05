

#include <vector>


#include "etiss/Misc.h"


namespace etiss{
namespace fault{



class CPUStateCopyHelper {
public:
	etiss_del_como(CPUStateCopyHelper)
private:
	std::list<std::pair<uint8_t*,size_t> > instructions_;
	std::map<std::string,std::function<std::pair<uint8_t*,size_t>(std::string,ETISS_CPU *)> > allocatorMap_; ///< type -> std::pair<uint8_t*,size_t>(*func)(std::string registername,ETISS_CPU * cpu)
public:
	void registerAllocator(std::string type, std::function<std::pair<uint8_t*,size_t>(std::string,ETISS_CPU *)> allocator);
	void	

};


}
}
