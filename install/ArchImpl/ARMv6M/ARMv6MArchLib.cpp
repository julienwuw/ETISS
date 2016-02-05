// define a name for this library. this will be used to avoid name clashes with other libraries. in this example the library is named "X".
// IMPORTANT this name MUST match the library name: e.g. X -> libX.so
#define ETISS_LIBNAME ARMv6M
#include "etiss/helper/CPUArchLibrary.h" // defines the following functions
#include "ARMv6MArch.h"
#include "ARMv6MIncludedFiles.h"
extern "C" {

    ETISS_LIBRARYIF_VERSION_FUNC_IMPL

    unsigned ARMv6M_countCPUArch()
    {
//TODO
        return 1; // number of cpu architectures provided
    }
    const char * ARMv6M_nameCPUArch(unsigned index)
    {
//TODO
        switch (index)
        {
        case 0:
            return "ARMv6M";
        default:
            return "";
        }
    }
    etiss::CPUArch* ARMv6M_createCPUArch(unsigned index,std::map<std::string,std::string> options)
    {
//TODO
        switch (index)
        {
        case 0:
// parse arguments?
            return new ARMv6MArch();
        default:
            return 0;
        }
    }
    void ARMv6M_deleteCPUArch(etiss::CPUArch* arch)
    {
        delete arch;
    }

    int ARMv6M_getFileCount()
    {
        return armv6m::storedfiles::count; // change variable name / function body as needed
    }
    const char * ARMv6M_getFileName(int index)
    {
        return armv6m::storedfiles::names[index]; // change variable name / function body as needed
    }
    const char * ARMv6M_getFileData(int index)
    {
        return armv6m::storedfiles::data[index]; // change variable name / function body as needed
    }



}
