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

@date December 16, 2014

@version 0.4

*/
/**
	@file config.h

	@brief contains defines to configure ETISS. this file is generated from config.h.in and may not be modified manually. if changes are needed apply them to config.h.in

	@detail 

*/
/**
	@file config.h.in

	@brief template of config.h for autoconf. run ./configure in the ETISS root folder to regenerate config.h if changes have been made

	@detail 

*/
#ifndef ETISS_CONFIG_H_
#define ETISS_CONFIG_H_

#define ETISS_VERSION_MAJOR 0
#define ETISS_VERSION_MINOR 4
#define ETISS_VERSION_PATCH 3

#define ETISS_VERSION_FULL "0.4.3"

#define ETISS_VERSION_INTERFACE "0.4"


#define ETISS_USE_PYTHON 0

#define ETISS_USE_DLSYM 1

#define ETISS_USE_DLADDR 1

#define ETISS_USE_GETPROC 0

#define ETISS_USE_LINUX_MKDIR 1 //TODO propper mkdir checks

#define ETISS_USE_DLSYM_DEEPBIND 1

#define ETISS_USE_POSIX_SOCKET 1

#define ETISS_INSTALL_DIR "/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/installed"

#define ETISS_USE_CONSTEXPR 1

#if ETISS_USE_CONSTEXPR
#define CONSTEXPR constexpr
#else
#define CONSTEXPR inline
#endif

#define ETISS_LITTLE_ENDIAN 0x00000001
#define ETISS_BIG_ENDIAN 0x01000000
#define ETISS_UNKNOWN_ENDIAN 0xFFFFFFFF

#define ETISS_ENDIANNESS ETISS_LITTLE_ENDIAN

#define ETISS_USE_BYTESWAP_H 0

#endif //ETISS_CONFIG_H_
