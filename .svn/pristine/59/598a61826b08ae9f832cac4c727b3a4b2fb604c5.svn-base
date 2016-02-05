

#include "GCCJIT.h"

#define ETISS_LIBNAME GCCJIT

#include "etiss/helper/JITLibrary.h"
#include "etiss/Misc.h"

extern "C" {

const char * GCCJIT_versionInfo(){
	return "0.4";
}

// implement version function
ETISS_LIBRARYIF_VERSION_FUNC_IMPL

unsigned GCCJIT_countJIT(){
	return 1;
}

const char * GCCJIT_nameJIT(unsigned i){
	return "GCCJIT";
}

etiss::JIT * GCCJIT_createJIT(unsigned i,std::map<std::string,std::string> options){
	etiss::Configuration cfg;
	cfg.config() = options;
	return new GCCJIT(cfg.get<bool>("cleanup",true));
}

void GCCJIT_deleteJIT(etiss::JIT * jit){
	delete (GCCJIT*)jit;
}


}
