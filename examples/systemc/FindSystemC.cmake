#
#	Copyright (c) 2014 Institute for Electronic Design Automation, TU Munich
#	
#	The above copyright notice and this permission notice shall be included in
#	all copies or substantial portions of the Software.
#	
#	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
#	THE SOFTWARE.
#	
#	
#	Author: Marc Greim <marc.greim@mytum.de>
#



# SystemC_VERSION_MAJOR = The major version of the package found.
# SystemC_VERSION_MINOR = The minor version of the package found.
# SystemC_VERSION_REV = The patch version of the package found.
# SystemC_VERSION = Full version string (major.minor.rev)
#
# use e.g. FIND_PACKAGE(SystemC 2.3) to find systemc. tlm should be included starting with systemc 2.3
#
# The following variables will be set:
#
# SystemC_INCLUDE_DIRS: Full path to include directory.
# SystemC_LIBRARIES: Full path to library.
#

INCLUDE (CheckLibraryExists) 
message(STATUS "Searching for SystemC")

#possible paths

SET(_SYSTEMC_HINTS
	"[HKEY_LOCAL_MACHINE\\SOFTWARE\\SystemC\\2.2;SystemcHome]/include"
	${SYSTEMC_PREFIX}/include
	${SYSTEMC_PREFIX}/lib
	${SYSTEMC_PREFIX}/lib-linux
	${SYSTEMC_PREFIX}/lib-linux64
	${SYSTEMC_PREFIX}/lib-macos
	$ENV{SYSTEMC_PREFIX}/include
	$ENV{SYSTEMC_PREFIX}/lib
	$ENV{SYSTEMC_PREFIX}/lib-linux
	$ENV{SYSTEMC_PREFIX}/lib-linux64
	$ENV{SYSTEMC_PREFIX}/lib-macos
	${CMAKE_INSTALL_PREFIX}/include
	${CMAKE_INSTALL_PREFIX}/lib
	${CMAKE_INSTALL_PREFIX}/lib-linux
	${CMAKE_INSTALL_PREFIX}/lib-linux64
	${CMAKE_INSTALL_PREFIX}/lib-macos
	${ETISS_SYSTEMC_PREFIX}/include
	${ETISS_SYSTEMC_PREFIX}/lib
	${ETISS_SYSTEMC_PREFIX}/lib-linux
	${ETISS_SYSTEMC_PREFIX}/lib-linux64
	${ETISS_SYSTEMC_PREFIX}/lib-macos
)
SET(_SYSTEMC_PATHS
	/usr/include/systemc
	/usr/lib
	/usr/lib-linux
	/usr/lib-linux64
	/usr/lib-macos
	/usr/local/lib
	/usr/local/lib-linux
	/usr/local/lib-linux64
	/usr/local/lib-macos
)
FIND_FILE(_SYSTEMC_VERSION_FILE
	NAMES sc_ver.h
	HINTS ${_SYSTEMC_HINTS}
	PATHS ${_SYSTEMC_PATHS}
	PATH_SUFFIXES sysc/kernel
)

EXEC_PROGRAM("cat ${_SYSTEMC_VERSION_FILE} |grep '#define SC_API_VERSION_STRING' | cut -d '_' -f 7 "
				OUTPUT_VARIABLE SystemC_MAJOR)
EXEC_PROGRAM("cat ${_SYSTEMC_VERSION_FILE} |grep '#define SC_API_VERSION_STRING' | cut -d '_' -f 8 "
				OUTPUT_VARIABLE SystemC_MINOR)
EXEC_PROGRAM("cat ${_SYSTEMC_VERSION_FILE} |grep '#define SC_API_VERSION_STRING' | cut -d '_' -f 9 "
				OUTPUT_VARIABLE SystemC_REV)
set(SystemC_VERSION ${SystemC_MAJOR}.${SystemC_MINOR}.${SystemC_REV})

FIND_PATH(SystemC_INCLUDE_DIRS
	NAMES systemc.h
	HINTS ${_SYSTEMC_HINTS}
	PATHS ${_SYSTEMC_PATHS}
)
FIND_PATH(SystemC_LIBRARY_DIRS
	NAMES libsystemc.a
	HINTS ${_SYSTEMC_HINTS}
	PATHS ${_SYSTEMC_PATHS}
)



if(EXISTS "${SystemC_INCLUDE_DIRS}/tlm.h" AND EXISTS "${SystemC_INCLUDE_DIRS}/systemc.h")
	set(SystemC_FOUND TRUE)
endif()

if(${SystemC_FOUND})
	add_definitions(-DSC_INCLUDE_DYNAMIC_PROCESSES)
	message(STATUS "SystemC: added definition SC_INCLUDE_DYNAMIC_PROCESSES")
	message(STATUS "SystemC version = ${SystemC_VERSION}")
	set(SystemC_LIBRARIES ${SystemC_LIBRARY_DIRS}/libsystemc.a)
	message(STATUS "SystemC library = ${SystemC_LIBRARIES}")
	
	find_package(Threads)
	if(${Threads_FOUND})
		list(APPEND SystemC_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})
		message(STATUS "SystemC library added: ${CMAKE_THREAD_LIBS_INIT}")
	endif()
	
	CHECK_LIBRARY_EXISTS(dl dlopen "" ETISS_SYSTEMC_HAVE_DL) 
	if(ETISS_SYSTEMC_HAVE_DL)
		list(APPEND SystemC_LIBRARIES dl)
		message(STATUS "SystemC library added: dl")
	endif()
	
else()
	message(STATUS "SystemC not found")
endif()

