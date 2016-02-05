// define a name for this library. this will be used to avoid name clashes with other libraries. in this example the library is named "X".
// IMPORTANT this name MUST match the library name: e.g. X -> libX.so
#define ETISS_LIBNAME TCCJIT


#include "etiss/helper/JITLibrary.h" // defines the following functions


#include "TCCJIT.h"

#include "TCCIncludedFiles.h"
                
extern "C"{

		ETISS_PLUGIN_EXPORT const char * TCCJIT_versionInfo(){
			return "0.9.26for0.4";
		}

        ETISS_LIBRARYIF_VERSION_FUNC_IMPL

		ETISS_PLUGIN_EXPORT unsigned TCCJIT_countJIT(){
                //TODO
                return 1; // number of cpu architectures provided
        }
		ETISS_PLUGIN_EXPORT const char * TCCJIT_nameJIT(unsigned index){
                //TODO
                switch (index){
                case 0:
                        return "TCCJIT";
                default:
                        return "";
                }
        }
		ETISS_PLUGIN_EXPORT etiss::JIT * TCCJIT_createJIT(unsigned index, std::map<std::string, std::string> options){
                //TODO
                switch (index){
                case 0:
                        // parse arguments?
                        return new TCCJIT();
                default:
                        return 0;
                }
        }
		ETISS_PLUGIN_EXPORT void TCCJIT_deleteJIT(etiss::JIT* arch){
                delete arch;
        }
        
		ETISS_PLUGIN_EXPORT int TCCJIT_getFileCount(){
        	return tcc::storedfiles::count;
        }
		ETISS_PLUGIN_EXPORT const char * TCCJIT_getFileName(int index){
			return tcc::storedfiles::names[index];
		}
		ETISS_PLUGIN_EXPORT const char * TCCJIT_getFileData(int index){
			return tcc::storedfiles::data[index];
		}
		ETISS_PLUGIN_EXPORT int TCCJIT_getFileSize(int index){
			return tcc::storedfiles::datalen[index];
		}
}
