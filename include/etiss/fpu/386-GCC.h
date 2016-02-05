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

@date July 29, 2014

@version 1.0

*/
/**
	@file
	
	@brief this file was derived from the 386-GCC.h file provided with John Hauser's Softfloat 2b library

	@detail 
*/

#include "etiss/jit/types.h"

/*----------------------------------------------------------------------------
| One of the macros `BIGENDIAN' or `LITTLEENDIAN' must be defined.
*----------------------------------------------------------------------------*/
#define LITTLEENDIAN

/*----------------------------------------------------------------------------
| The macro `BITS64' can be defined to indicate that 64-bit integer types are
| supported by the compiler.
*----------------------------------------------------------------------------*/
#define BITS64

/*----------------------------------------------------------------------------
| Each of the following `typedef's defines the most convenient type that holds
| integers of at least as many bits as specified.  For example, `uint8' should
| be the most convenient type that can hold unsigned integers of as many as
| 8 bits.  The `flag' type must be able to hold either a 0 or 1.  For most
| implementations of C, `flag', `uint8', and `int8' should all be `typedef'ed
| to the same as `int'.
*----------------------------------------------------------------------------*/
typedef char flag;
typedef etiss_uint8 uint8;
typedef etiss_int8 int8;
typedef etiss_uint16 uint16;
typedef etiss_int16 int16;
typedef etiss_uint32 uint32;
typedef etiss_int32 int32;
typedef etiss_uint64 uint64;
typedef etiss_int64 int64;

/*----------------------------------------------------------------------------
| Each of the following `typedef's defines a type that holds integers
| of _exactly_ the number of bits specified.  For instance, for most
| implementation of C, `bits16' and `sbits16' should be `typedef'ed to
| `unsigned short int' and `signed short int' (or `short int'), respectively.
*----------------------------------------------------------------------------*/
typedef etiss_uint8 bits8;
typedef etiss_int8 sbits8;
typedef etiss_uint16 bits16;
typedef etiss_int16 sbits16;
typedef etiss_uint32 bits32;
typedef etiss_int32 sbits32;
typedef etiss_uint64 bits64;
typedef etiss_int64 sbits64;

#define LIT64( a ) a##LL


/*----------------------------------------------------------------------------
| The macro `INLINE' can be used before functions that should be inlined.  If
| a compiler does not support explicit inlining, this macro should be defined
| to be `static'.
*----------------------------------------------------------------------------*/
#define INLINE extern inline

