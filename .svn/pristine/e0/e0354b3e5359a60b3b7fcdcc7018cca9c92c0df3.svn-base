/**

@copyright
<pre>


	Copyright (c) 2014 Institute for Electronic Design Automation, TU Munich

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.


</pre>
@author Marc Greim <marc.greim@mytum.de>

@date July 24, 2014

@version 0.1

*/
/**
	@file

	@brief contains exception/return codes used to control execution of an etiss::CPUCore

	@detail any return code defined with the defineReturnCode(NAME,VALUE,MSG) macro is available in C++ under the name etiss::RETURNCODE::NAME and ETISS_RETURNCODE_NAME and in C under the name ETISS_RETURNCODE_NAME. In C++ the return code names and messages are accessible via the maps returned by etiss::RETURNCODE::getErrorMessages and etiss::RETURNCODE::getErrorNames

*/
#ifndef ETISS_INCLUDE_RETURNCODE_H_
#define ETISS_INCLUDE_RETURNCODE_H_

#include "etiss/jit/types.h"


#ifdef __cplusplus

#include "etiss/Misc.h" // etiss::log(2)
#include <map>

namespace etiss {

	namespace RETURNCODE {
		/**
			@brief function to access error message map. implemented in ETISS.cpp
			@see ETISS.cpp
		*/
		extern std::map<etiss::int32,const char*> & getErrorMessages();
		/**
			@brief function to access error name map. implemented in ETISS.cpp
			@see ETISS.cpp
		*/
		extern std::map<etiss::int32,const char*> & getErrorNames();

        extern int32_t setTemporary(const std::string & msg);

	}

}

#endif

/// sets the message of a temporary return code and returns the returncode. use for custom messages. message may be overwritten if all other temporary return codes are used
extern int32_t etiss_returncode_setTemporary(const char * msg);




#ifndef etiss_toString
#define etiss__toString_(X) #X
#define etiss_toString(X) etiss__toString_(X)
#endif
#ifndef etiss_merge2
#define etiss__merge2_(X,Y) X##Y
#define etiss_merge2(X,Y) etiss__merge2_(X,Y)
#endif

/**
	define RETURNCODE definition template for easy use with c and c++
*/
#ifdef __cplusplus
#ifdef ETISS_RETURNCODE_REGISTRATION_BODY

	#define defineReturnCodeClass_(UNIQUENUMBER,NAME,VALUE,MSG)	static class ReturnCodeRegistration_##UNIQUENUMBER {\
																public:\
																ReturnCodeRegistration_##UNIQUENUMBER(){\
																	auto entry = etiss::RETURNCODE::getErrorNames().find(VALUE); \
																	if (entry != etiss::RETURNCODE::getErrorNames().end()) { \
																		if (std::string(entry->second) != etiss_toString(NAME)){ \
																			std::stringstream ss; \
																			ss << "Duplicated RETURNCODE "<< VALUE << ": "; \
																			ss << etiss::RETURNCODE::getErrorNames().find(VALUE)->second << "," << etiss_toString(NAME); \
																			etiss::log(etiss::ERROR,ss.str()); \
																		} \
																	} \
																	etiss::RETURNCODE::getErrorMessages()[VALUE] = MSG; \
																	etiss::RETURNCODE::getErrorNames()[VALUE] = etiss_toString(NAME); \
																}\
																} returnCodeRegistration_##UNIQUENUMBER;

    #define defineReturnCodeClass(UNIQUENUMBER,NAME,VALUE,MSG) defineReturnCodeClass_(UNIQUENUMBER,NAME,VALUE,MSG)

	#define defineReturnCode(NAME,VALUE,MSG) namespace etiss { namespace RETURNCODE { static const etiss::int32 NAME = VALUE; } } \
						static const etiss_int32 etiss_merge2(ETISS_RETURNCODE_,NAME) = VALUE; \
						defineReturnCodeClass(__COUNTER__,NAME,VALUE,MSG)
#else
	#define defineReturnCode(NAME,VALUE,MSG) 	static const etiss_int32 ETISS_RETURNCODE_##NAME = VALUE;\
												namespace etiss { namespace RETURNCODE { static const etiss::int32 NAME = VALUE; } }
#endif
#else
	#define defineReturnCode(NAME,VALUE,MSG) 	static const etiss_int32 ETISS_RETURNCODE_##NAME = VALUE;
#endif


//////////////////// definition of global (cpu architecture independent) return codes

defineReturnCode(NOERROR,0,"No error.")
defineReturnCode(GENERALERROR,-1,"General error.")

defineReturnCode(RELOADBLOCKS,-2,"clear cached translated blocks")
defineReturnCode(RELOADCURRENTBLOCK,-3,"clear the cached block that returned this code")
//defineReturnCode(RELOADRANGE,-4,"clear cached translated blocks in a range")

defineReturnCode(DBUS_READ_ERROR,-5,"")
defineReturnCode(DBUS_WRITE_ERROR,-6,"")
defineReturnCode(IBUS_READ_ERROR,-7,"")
defineReturnCode(IBUS_WRITE_ERROR,-8,"")

defineReturnCode(INTERRUPT,-9,"signal an interrupt")
defineReturnCode(RESET,-10,"reset signal")

defineReturnCode(ILLEGALINSTRUCTION,-11,"illegal instruction")
defineReturnCode(ILLEGALJUMP,-12,"illegal jump address")

defineReturnCode(GDBNOERROR,-16,"has the same effect as NOERROR but allows exiting a block where NOERROR would have continued block execution");

defineReturnCode(CPUFINISHED,1<<31,"finished cpu execution. this is the propper way to exit from etiss::CPUCore::execute");
defineReturnCode(CPUTERMINATED,0x80000001,"terminates cpu execution. this is the propper way to force an exit from etiss::CPUCore::execute (e.g. by a debugger)");


defineReturnCode(JITERROR,-32,"")
defineReturnCode(JITCOMPILATIONERROR,-33,"")
defineReturnCode(ARCHERROR,-34,"")
defineReturnCode(EMULATIONNOTSUPPORTED,-35,"")

defineReturnCode(INVALIDSYSTEM,-36,"An ETISS_System structure doesn't contain the neccessary function pointers.")

defineReturnCode(TEMPORARY0,-128,"")
defineReturnCode(TEMPORARY1,-129,"")
defineReturnCode(TEMPORARY2,-130,"")
defineReturnCode(TEMPORARY3,-131,"")
defineReturnCode(TEMPORARY4,-132,"")
defineReturnCode(TEMPORARY5,-133,"")
defineReturnCode(TEMPORARY6,-134,"")
defineReturnCode(TEMPORARY7,-135,"")
#define ETISS_RETURNCODE_TEMPORARY_COUNT 8


#endif
