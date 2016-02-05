
#include "etiss/JIT.h"


/**
	@brief provides compilation via gcc and load the compilation result with dlopen/dlsym functions
	@detail use the option "cleanup" -> "false" to keep code after destruction of a GCCJIT instance
*/
class GCCJIT : public etiss::JIT {
	public :
		GCCJIT(bool cleanup = true);
		virtual ~GCCJIT();
		virtual void * translate(std::string code,std::set<std::string> headerpaths,std::set<std::string> librarypaths,std::set<std::string> libraries,std::string & error,bool debug= false);
		virtual void * getFunction(void * handle,std::string name,std::string & error);
		virtual void free(void * handle);
		
	private :
		
	private :
		unsigned id;
		std::string path_;
		bool cleanup_;
	
};


