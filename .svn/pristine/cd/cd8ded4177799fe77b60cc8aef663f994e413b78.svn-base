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
	
	@brief type declarations for etiss and definition of the likely/unlikely macros.

	@detail current jit implementations (GCC/LLVM) don't require customization of this file.
		

*/
#ifndef ETISS_INCLUDE_TYPES_H_
#define ETISS_INCLUDE_TYPES_H_


//TODO: move to special header provided by compiler
//_________________________________________________________________
//#ifdef _MSC_VER
//#include "etiss/jit/msvc_stdint.h"
//#else
#include <stdint.h>
//#endif
//#include <stdbool.h> // removed since it may not be available


#ifdef __GNUC__
	#define likely(x)       __builtin_expect(!!(x), 1)
	#define unlikely(x)     __builtin_expect(!!(x), 0)
#else
	#define likely(x)       (x)
	#define unlikely(x)     (x)
#endif

//_________________________________________________________________

#define stream_code_info "\t{ File: " << __FILE__ << "\tLine: " << __LINE__ << "}" 

#ifdef __cplusplus
extern "C" {
#endif

	typedef		int8_t		etiss_int8;
	typedef		uint8_t		etiss_uint8;
	
	typedef		int16_t		etiss_int16;
	typedef		uint16_t	etiss_uint16;
	
	typedef		int32_t		etiss_int32;
	typedef		uint32_t	etiss_uint32;
	
	typedef		int64_t		etiss_int64;
	typedef		uint64_t	etiss_uint64;
	
	typedef		etiss_int64	etiss_intMax;
	typedef		etiss_uint64	etiss_uintMax;



#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
namespace etiss {

	typedef		etiss_int8	int8;
	typedef		etiss_uint8	uint8;

	typedef		etiss_int16	int16;
	typedef		etiss_uint16	uint16;

	typedef		etiss_int32	int32;
	typedef		etiss_uint32	uint32;
	
	typedef		etiss_int64	int64;
	typedef		etiss_uint64	uint64;

	typedef		etiss_intMax 	intMax;
	typedef		etiss_uintMax 	uintMax;

}
#endif


#endif
