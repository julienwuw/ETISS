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
	
	@brief contains an interface for time synchronization and memory access

	@detail 
		
		
		

*/

#ifndef ETISS_INCLUDE_JIT_SYSTEM_H_
#define ETISS_INCLUDE_JIT_SYSTEM_H_

#include "etiss/jit/types.h"
#include "etiss/jit/CPU.h"

#ifdef __cplusplus
extern "C" {
#endif

	#pragma pack(push, 1) // NEVER ALLOW ALIGNMENT OF STRUCTURE MEMBERS
	/**
		@brief memory access and time synchronization functions. the "handle" parameter passed on a function call is always the "handle" variable of the structure.
		@detail to increase performance it is recommended to implement this structure directly. For convinience a etiss::System class is available (include/System.h) that can be extended and which will be automatically wrapped in an ETISS_System structure. 
			NOTE: this structure must be packed {#pragma pack(push, 1)}
		@see include/SystemWrapper.h
		@see src/SystemWrapper.cpp
	*/
	struct ETISS_System {
	
		/**
			@brief used to simulate an instruction fetch. instructions are fetched for translation with dbg_iread(4). this function is not used by default
		*/
		etiss_int32 (*iread) (void * handle, ETISS_CPU * cpu, etiss_uint64 addr,etiss_uint32 length);
		/**
			@brief write instruction data over instruction bus
		*/
		etiss_int32 (*iwrite) (void * handle, ETISS_CPU * cpu, etiss_uint64 addr,etiss_uint8 * buffer,etiss_uint32 length);
		/**
			@brief read data
		*/
		etiss_int32 (*dread) (void * handle, ETISS_CPU * cpu, etiss_uint64 addr,etiss_uint8 * buffer,etiss_uint32 length);
		/**
			@brief write data
		*/
		etiss_int32 (*dwrite) (void * handle, ETISS_CPU * cpu, etiss_uint64 addr,etiss_uint8 * buffer,etiss_uint32 length);
		
		// debug access functions
		/**
			@brief direct debug read
		*/
		etiss_int32 (*dbg_read) (void * handle, etiss_uint64 addr,etiss_uint8 * buffer,etiss_uint32 length);
		/**
			@brief direct debug write
		*/
		etiss_int32 (*dbg_write) (void * handle, etiss_uint64 addr,etiss_uint8 * buffer,etiss_uint32 length);

		/**
			@brief called after a block to synchronize the time
		*/
		void (*syncTime) (void * handle, ETISS_CPU * cpu);
	
		void * handle; /**< @brief custom handle that will be passed to the functions of this structure */
	
	};
	#pragma pack(pop)
	
	
	typedef struct ETISS_System ETISS_System;
	
	extern int ETISS_System_isvalid(ETISS_System * sys);
	

#ifdef __cplusplus
}
#endif

#endif
