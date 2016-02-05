#include "etiss/JIT.h"
#include <map>

class TCCJIT : public etiss::JIT {
        public :
        	TCCJIT();
                virtual void * translate(std::string code,std::set<std::string> headerpaths,std::set<std::string> librarypaths,std::set<std::string> libraries,std::string & error,bool debug= false);
                virtual void * getFunction(void * handle,std::string name,std::string & error);
                virtual void free(void * handle);
       private:
       		std::string wd;
			std::map<std::string, void*> extsymbols; ///< only use for windows. manual linking to symbols of current executable
};
