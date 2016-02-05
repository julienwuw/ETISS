#define ETISS_LIBNAME LLVMJIT

#include "etiss/helper/JITLibrary.h"

#include "LLVMJIT.h"
#include "CLangIncludedFiles.h"

#include <iostream>

// implement etiss library interface
extern "C" {

	const char * LLVMJIT_versionInfo(){
		return "3.4.2for0.4";
	}

	// implement version function
	ETISS_LIBRARYIF_VERSION_FUNC_IMPL

	unsigned LLVMJIT_countJIT(){
		return 1;
	}
	const char *  LLVMJIT_nameJIT(unsigned index){
		switch (index){
		case 0: return "LLVMJIT";
		default: return 0;
		}
	}
	etiss::JIT * LLVMJIT_createJIT(unsigned index,std::map<std::string,std::string> options){
		switch (index){
		case 0:
			return new etiss::LLVMJIT();
		default:
			return 0;
		}
	}

	void LLVMJIT_deleteJIT(etiss::JIT *o){
		delete o;
	}
	
	int LLVMJIT_getFileCount(){
        	return clang::storedfiles::count;
        }
	const char * LLVMJIT_getFileName(int index){
		return clang::storedfiles::names[index];
	}
	const char * LLVMJIT_getFileData(int index){
		return clang::storedfiles::data[index];
	}

}
