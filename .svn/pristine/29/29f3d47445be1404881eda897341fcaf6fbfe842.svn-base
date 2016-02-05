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

################	Conventions			##############

# any variable that is intended for use as a substitution variable
# for generated files must be prefixed with "C_" (e.g. C_VARIABLE)

# variables that are set with values from variables 
# (e.g. set( var1 ${var2]) ) should not be modified by any user,
# unless it is neccessary and all effects of that change are known.

# etiss configuration options shall have the form ETISS_USE_XXXXXX. 
# They are intended for the CMake context and a C_ETISS_USE_XXXXXX
# variable should be provided for generated files (e.g. header files).
# Difference of the C_ prefixed version is that CMake value need to be
# translated to C/C++ common counterparts. The following list shows
# some conversions:
#	Value			C_ prefixed Value
#	ON/TRUE			1
#	OFF/FALSE		0
#	0.3.2			"0.3.2"

# variables that are likely changed over time and configuration options
# should be listed in the section after the Conventions section. The 
# assumption that the listed variables provide a "C_" prefixed version
# for generated files shall hold. Therefore it is not recommended to also
# list the prefixed variable version in that list. If a variable stems
# from an option it should be annoted with "option", otherwise with 
# "variable" or "derived" in case of a derived variable wich holds a 
# usefull value. If an option is located in a sub CMakeLists.txt, then
# the path to that file MUST be appended to that variable in brackets.
# examples:
#	VAR_OPTION1				option		configures option1 to enable/disable ...
#	OPTION2(src/CMakeLists_location/)	option		if option2 is enabled then ... 

# configuration options should perform a check if it is possible to 
# enable/disable that option to prevent errors. if an option cannot be
# set, then the set value may be ignored silently. printing out an info
# message is recommended in that case.

# ALL options MUST be printed out at the end. Variables may be printed
# out if deemed neccessary/useful (e.g. message("VARIABLE_1: ${VARIABLE_1}")

# Don't use #ifndef/#ifdef to check if certain functionality should be present 
# (see ETISS_USE_XXX). always use "#if OPTION" since an undefined option will 
# always evaluate to false and it may be defined as "#define OPTION 0"



######################################################################


################	List of Variables and Options	##############

# ETISS_VERSION_MAJOR		variable	
# ETISS_VERSION_MINOR		variable
# ETISS_VERSION_PATCH		variable
# ETISS_VERSION_FULL		derived		full version of etiss
# ETISS_VERSION_INTERFACE	derived		interface version of etiss. usually only mayor.minor version number

# ETISS_USE_PYTHON		option 		enables or disables python support in ETISS. deactivated by default

# ETISS_USE_DLSYM		option		enables or disables the use of dlopen/dlsym/dlclose functions to load plugin libraries. enabled by default if possible
# ETISS_USE_DLADDR		variable	dladdr(2) may be used. e.g. etiss::preloadLibraries makes use of that

# ETISS_SOURCE			variable	variable to store all source files of etiss (.cpp files located in src)
# ETISS_HEADER			variable	variable to store all header files of etiss (.h/.hpp files located in src)

# ETISS_USE_CXX11		derived		true if the c++ compiler supports the c++11 standard
# ETISS_USE_CXX0X		derived		true if the c++ compiler supports some c++11 features as c++0x

# ETISS_BUILD_DEFAULTSUB		variable	also build projects located in ArchImpl/JITImpl/PluginImpl and projects

# ETISS_BUILD_STATIC	option		builds a static library alongside a shared library if possible

# ETISS_FILES_SRC	variable	all source (.cpp) files of etiss and projects in the source tree
# ETISS_FILES_LIB	variable	all .lib files for etiss
# ETISS_FILES_DLL	variable	all .dll files for etiss
# ETISS_FILES_LNK	variable	all libraries to link against (e.g. pthread)| deprecated: use ETISS_LIBRARY instead | do not change manually: use ETISS(ADD_LIBRARY "yourlib")/ETISS(ADD_LIBRARY "yourlib" OPTIONAL) instead

# ETISS_LIBRARIES 	variable 	all libraries to link against (e.g. pthread)| do not change manually: use ETISS(ADD_LIBRARY "yourlib")/ETISS(ADD_LIBRARY "yourlib" OPTIONAL) instead

# ETISS_SOURCE_INSTALL option	it on then instead of building shread libraries and install those the source code will be installed and ETISS_SOURCES needs to be added to a project. enabled on windows

######################################################################

### configure cmake
set(CMAKE_USE_RELATIVE_PATHS ON)

cmake_minimum_required (VERSION 2.8.3)

################	Declare Project ETISS
project(ETISS)

################	Declare ETISS version
set (ETISS_VERSION_MAJOR 0)
set (ETISS_VERSION_MINOR 4)
set (ETISS_VERSION_PATCH 3)

### derived version variables
set (ETISS_VERSION_FULL ${ETISS_VERSION_MAJOR}.${ETISS_VERSION_MINOR}.${ETISS_VERSION_PATCH})
set (ETISS_VERSION ${ETISS_VERSION_FULL}) ## ETISS_VERSION seems to be the more common variable name
set (ETISS_VERSION_INTERFACE ${ETISS_VERSION_MAJOR}.${ETISS_VERSION_MINOR})

### set variables for defines
set (C_ETISS_VERSION_MAJOR ${ETISS_VERSION_MAJOR})
set (C_ETISS_VERSION_MINOR ${ETISS_VERSION_MINOR})
set (C_ETISS_VERSION_PATCH ${ETISS_VERSION_PATCH})
set (C_ETISS_VERSION_FULL \"${ETISS_VERSION_FULL}\")
set (C_ETISS_VERSION \"${ETISS_VERSION}\")
set (C_ETISS_VERSION_INTERFACE \"${ETISS_VERSION_INTERFACE}\")


###############		include cmake commands
INCLUDE(CheckIncludeFile)
INCLUDE(CheckIncludeFiles)
INCLUDE(CheckCXXSourceCompiles)
INCLUDE(FindPythonLibs)
INCLUDE(TestBigEndian)
INCLUDE(GenerateExportHeader)
INCLUDE(CheckSymbolExists)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})
INCLUDE(ETISSCMakeFunctions)


##################################################################
########	Configuration + Options

if(WIN32 AND NOT MINGW AND NOT CYGWIN)
set(ETISS_SOURCE_INSTALL_DEF ON)
else()
set(ETISS_SOURCE_INSTALL_DEF OFF)
endif()
option(ETISS_SOURCE_INSTALL "disable shared libraries and install the source code directly. enabled for windows builds by default" ${ETISS_SOURCE_INSTALL_DEF})

set (ETISS_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

### configure debug mode
if(CMAKE_BUILD_TYPE MATCHES DEBUG)
	set(P_ETISS_DEBUG ON)
else()
	set(P_ETISS_DEBUG OFF)
endif()
option(ETISS_DEBUG "enable or disable debug mode. usually this is detected but can be overridden (e.g. to enable debug code parts of etiss for release build)." ${P_ETISS_DEBUG})
if (ETISS_DEBUG)
	set(C_ETISS_DEBUG 1)
else()
	set(C_ETISS_DEBUG 0)
endif()
add_definitions(-DETISS_DEBUG=${C_ETISS_DEBUG})

### python
find_package(PythonLibs 2.7)
option(ETISS_USE_PYTHON "Support python within ETISS" OFF)
IF(PYTHONLIBS_FOUND)
	IF(ETISS_USE_PYTHON)
		set(C_ETISS_USE_PYTHON 1)
		ETISS(ADD_LIBRARY ${PYTHON_LIBRARIES})
		#list(APPEND ETISS_FILES_LNK "${PYTHON_LIBRARIES}")
	ELSE()
		set(C_ETISS_USE_PYTHON 0)
	ENDIF()
ELSE()
	set(ETISS_USE_PYTHON OFF)
	set(C_ETISS_USE_PYTHON 0) 
ENDIF()
IF(ETISS_USE_PYTHON)
	include_directories(${PYTHON_INCLUDE_PATH})
ENDIF()

### pthreads #if its there link it since it is commonly needed
find_package (Threads)
if(DEFINED CMAKE_THREAD_LIBS_INIT)
ETISS(ADD_LIBRARY ${CMAKE_THREAD_LIBS_INIT})
#list(APPEND ETISS_FILES_LNK "${CMAKE_THREAD_LIBS_INIT}")
endif()
### dl #if its there link it since it is commonly needed
ETISS(ADD_LIBRARY dl OPTIONAL)


### dlsym
CHECK_INCLUDE_FILES(dlfcn.h ETISS_USE_DLSYM_CHECK)
IF(ETISS_USE_DLSYM_CHECK)
	option(ETISS_USE_DLSYM "Use dlope/dlsym/dlclose to load libraries for ETISS" ON)
	IF(ETISS_USE_DLSYM)
		set(C_ETISS_USE_DLSYM 1)
		ETISS(ADD_LIBRARY dl) #requires dl library
	ELSE()
		set(C_ETISS_USE_DLSYM 0)
	ENDIF()
ELSE()
	set(C_ETISS_USE_DLSYM OFF)
	set(C_ETISS_USE_DLSYM 0)
ENDIF()

### check for RTLD_DEEPBIND
CHECK_CXX_SOURCE_COMPILES(
"#include <dlfcn.h>\nint main(int,char**){ return (int) RTLD_DEEPBIND;}"
ETISS_CAN_USE_DLSYM_DEEPBIND
)
option(ETISS_USE_DLSYM_DEEPBIND "DEPRECATED [Loads libraries in a way that prefers to link against symbol within the same library]" ON)
if (ETISS_CAN_USE_DLSYM_DEEPBIND AND ETISS_USE_DLSYM_DEEPBIND)
	set(C_ETISS_USE_DLSYM_DEEPBIND 1)
	set(ETISS_USE_DLSYM_DEEPBIND ON)
else()
	set(C_ETISS_USE_DLSYM_DEEPBIND 0)
	set(ETISS_USE_DLSYM_DEEPBIND OFF)
endif()

set(CMAKE_REQUIRED_LIBRARIES_OLD ${CMAKE_REQUIRED_LIBRARIES})
list(APPEND CMAKE_REQUIRED_LIBRARIES dl)
### check fo dladdr
CHECK_CXX_SOURCE_COMPILES(
"#include <dlfcn.h>\nint main(int,char**){ Dl_info i; return !dladdr((void*)main,&i);}"
ETISS_USE_DLADDR
)
set(CMAKE_REQUIRED_LIBRARIES ${CMAKE_REQUIRED_LIBRARIES_OLD})
if (ETISS_USE_DLADDR)
	set(C_ETISS_USE_DLADDR 1)
	set(ETISS_USE_DLADDR ON)
else()
	set(C_ETISS_USE_DLADDR 0)
	set(ETISS_USE_DLADDR OFF)
endif()


### check for windows' dlsym equivalent
CHECK_SYMBOL_EXISTS( GetProcAddress windows.h ETISS_CAN_USE_GETPROC)
option(ETISS_USE_GETPROC "Loads libraries in a way that prefers to link against symbol within the same library" ON)
if (ETISS_CAN_USE_GETPROC AND ETISS_USE_GETPROC)
	if (NOT ETISS_CAN_USE_SymEnumSymbols)
	message(WARNING "ETISS is configured to use GetProcAddress for symbol loading. However the related function SymEnumSymbols is not available. This may lead to problems e.g. with the TCC plugin.")
	endif()
	set(C_ETISS_USE_GETPROC 1)
	set(ETISS_USE_GETPROC ON)
else()
	set(C_ETISS_USE_GETPROC 0)
	set(ETISS_USE_GETPROC OFF)
endif()

### check for byteswap header
CHECK_INCLUDE_FILES(byteswap.h ETISS_USE_BYTESWAP_H)
IF($EISS_USE_BYTESWAP_H})
	set(C_ETISS_USE_BYTESWAP_H 1) 
ELSE()
	set(C_ETISS_USE_BYTESWAP_H 0)
ENDIF()

### check linux network sockets
CHECK_INCLUDE_FILES("string.h;errno.h;sys/types.h;sys/socket.h;netinet/in.h;netinet/tcp.h;unistd.h" ETISS_USE_POSIX_SOCKET)
if(${ETISS_USE_POSIX_SOCKET})
	set(C_ETISS_USE_POSIX_SOCKET 1)
else()
	set(C_ETISS_USE_POSIX_SOCKET 0)
endif()

### manual doc build (usefull for testing/debugging since the documentation should not be build on each make)
option(ETISS_BUILD_MANUAL_DOC "If enabled then the documentation will not be build by target all. run $make doc to create the documentation. default is ON for debug build OFF otherwise" ${ETISS_DEBUG})
IF(${ETISS_BUILD_MANUAL_DOC})
	set(C_ETISS_BUILD_MANUAL_DOC 1)
ELSE()
	set(C_ETISS_BUILD_MANUAL_DOC 0)
ENDIF()

option(ETISS_BUILD_DEFAULTSUB "If enabled then the ArchImpl,JITImpl,PluginImpl and projects folder will be added as subfolders. Please have a look at the CMakeLists.txt files of those folders for further information" ON)


### check for c++0x support
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" ETISS_USE_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" ETISS_USE_CXX0X)
if(ETISS_USE_CXX11)
	set(C_ETISS_USE_CXX11 1)
	set(C_ETISS_USE_CXX0X 1)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(ETISS_USE_CXX0X)
	set(C_ETISS_USE_CXX11 0)
	set(C_ETISS_USE_CXX0X 1)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
	set(C_ETISS_USE_CXX11 0)
	set(C_ETISS_USE_CXX0X 0)
        message(WARNING "The compiler ${CMAKE_CXX_COMPILER} doesn't support the --std==c++11 / --std=c++0x otions. ETISS requires at least C++0x as implemented by gcc 4.6. Please ensure that the compiler is up to the task.")
endif()

## check for constexpr
set(TMP_CMAKE_REQUIRED_FLAGS ${CMAKE_REQUIRED_FLAGS})
if (ETISS_USE_CXX11)
	set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} --std=c++11 ")
elseif (ETISS_USE_CXX0X)
	set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} --std=c++0x ")
endif()
CHECK_CXX_SOURCE_COMPILES( 
"constexpr int x() {return 1;} main(int,char**){ return x();}"
ETISS_USE_CONSTEXPR
)
set(CMAKE_REQUIRED_FLAGS ${TMP_CMAKE_REQUIRED_FLAGS})
if (ETISS_USE_CONSTEXPR)
	set(C_ETISS_USE_CONSTEXPR 1)
	set(ETISS_USE_CONSTEXPR ON)
else()
	set(C_ETISS_USE_CONSTEXPR 0)
	set(ETISS_USE_CONSTEXPR OFF)
endif()

## configure endianess
TEST_BIG_ENDIAN(ETISS_ENDIANNESS)
if (NOT DEFINED ETISS_ENDIANNESS)
	message(WARNING "Failed to detect endianness")
	set(C_ETISS_ENDIANNESS ETISS_UNKNOWN_ENDIAN)
elseif(ETISS_ENDIANNESS)
	set(C_ETISS_ENDIANNESS ETISS_BIG_ENDIAN)
else()
	set(C_ETISS_ENDIANNESS ETISS_LITTLE_ENDIAN)
endif()


##################################################################

### NO CONFIGURATION OPTIONS MAY BE SET PAST THIS LINE ###########

##################################################################
########	create code generator target 

### create code generator executable
add_executable(IncludedFilesGenerator IncludedFilesGenerator.cpp)
install(TARGETS IncludedFilesGenerator
		DESTINATION bin)

##################################################################

##################################################################
########	Generate files based on the current configuration

### config.h
configure_file(
  "${PROJECT_SOURCE_DIR}/include/etiss/config.h.in"
  "${PROJECT_BINARY_DIR}/include/etiss/config.h"
 )
install(	FILES ${PROJECT_BINARY_DIR}/include/etiss/config.h
		DESTINATION include/etiss)
set (ETISS_DOX_LOCATIONS ${ETISS_DOX_LOCATIONS} ${PROJECT_BINARY_DIR}/include)
set (ETISS_DOX_LOCATIONS ${ETISS_DOX_LOCATIONS} ${PROJECT_BINARY_DIR}/include_c)
unset(TMP_CONFIG_HEADER_REL)
file(GLOB TMP_CONFIG_HEADER_REL RELATIVE ${ETISS_ROOT_DIR} ${PROJECT_BINARY_DIR}/include/etiss/config.h)
set (ETISS_HEADER ${ETISS_HEADER} ${TMP_CONFIG_HEADER_REL})

### Doxyfile	
configure_file(
  "${PROJECT_SOURCE_DIR}/Doxyfile.in"
  "${PROJECT_BINARY_DIR}/Doxyfile"
 )



##################################################################

##################################################################
########	Copy project files to install dir

#copy headers + doc files from include and include_c
install(	DIRECTORY ${PROJECT_SOURCE_DIR}/include/
		DESTINATION include
		FILES_MATCHING
    		PATTERN "*.h"
    		PATTERN "*.hpp"
    		PATTERN ".svn" EXCLUDE
    		PATTERN "dox" EXCLUDE
    		PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
    		
install(	DIRECTORY ${PROJECT_SOURCE_DIR}/include_c/
		DESTINATION include
		FILES_MATCHING
    		PATTERN "*.h"
    		PATTERN "*.hpp"
    		PATTERN ".svn" EXCLUDE
    		PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
    		
#copy generated documentation
install(	DIRECTORY ${PROJECT_BINARY_DIR}/doc/
		DESTINATION "doc"
		OPTIONAL
		FILES_MATCHING
    		PATTERN "*"
    		PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)

#copy cmake files
if(WIN32)
  set(DEF_INSTALL_CMAKE_DIR CMake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/CMake/ETISS)
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")


##################################################################
########	setup building of libETISS
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_BINARY_DIR}/include")
set (ETISS_DOX_LOCATIONS ${ETISS_DOX_LOCATIONS} ${PROJECT_SOURCE_DIR}/include)
include_directories("${PROJECT_SOURCE_DIR}/include_c")
include_directories("${PROJECT_BINARY_DIR}/include_c")
set (ETISS_DOX_LOCATIONS ${ETISS_DOX_LOCATIONS} ${PROJECT_SOURCE_DIR}/include_c)
set (ETISS_DOX_LOCATIONS ${ETISS_DOX_LOCATIONS} ${PROJECT_SOURCE_DIR}/src)

### check if doxygen is available
find_package(Doxygen)




### find source files
add_subdirectory(src)

### find header files
add_subdirectory(include)
add_subdirectory(include_c)

### include sub projects
if(ETISS_BUILD_DEFAULTSUB)
	add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/projects)
	add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/ArchImpl)
	add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/JITImpl)
	add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/PluginImpl)
endif()

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/examples)

###try to compile systemc example. the systemc example MUST check for availability of systemc and abort without an error if not present
# see systemc/CMakeLists.txt for more information
if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/systemc/CMakeLists.txt)
	add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/systemc/)
endif()




#if doxygen is available generate documentation
if(DOXYGEN_FOUND)
	string(REPLACE ";" " " P_ETISS_DOX_LOCATIONS "${ETISS_DOX_LOCATIONS}")
	string(REPLACE ";" "\n" C_ETISS_DOX_LOCATIONS "\"${ETISS_DOX_LOCATIONS}\"")
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
	if(ETISS_BUILD_MANUAL_DOC)
		add_custom_target(doc 
		${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating API documentation with Doxygen" VERBATIM
		)
	else(ETISS_BUILD_MANUAL_DOC)
		add_custom_target(doc ALL
		${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating API documentation with Doxygen" VERBATIM
		)
	endif(ETISS_BUILD_MANUAL_DOC)
else(DOXYGEN_FOUND)
	message(WARNING "Doxygen could not be found. target doc (e.g. make doc) will not be available")
endif(DOXYGEN_FOUND)

### generate included files #deprecated
find_package(PythonInterp)

##generate included files
# note: if a problem with a random missing character in the passed strings of the executable arises then the command may be to long. in that case use relative paths to shorten the list of files
file(GLOB_RECURSE ETISS_INCLUDEDFILES RELATIVE "${CMAKE_CURRENT_LIST_DIR}" "${CMAKE_CURRENT_LIST_DIR}/include_c/*.h")
file(GLOB_RECURSE ETISS_INCLUDEDFILES_ADD RELATIVE "${PROJECT_BINARY_DIR}" "${PROJECT_BINARY_DIR}/include_c/*.h")
foreach(tmpp ${ETISS_INCLUDEDFILES_ADD})
	list(APPEND ETISS_INCLUDEDFILES "${tmpp},${PROJECT_BINARY_DIR}/${tmpp}")
	list(APPEND ETISS_INCLUDEDFILES_DEPENDS "${PROJECT_BINARY_DIR}/${tmpp}")
endforeach()
add_custom_command(	OUTPUT "${PROJECT_BINARY_DIR}/include/etiss/IncludedFiles.h" "${PROJECT_BINARY_DIR}/src/IncludedFiles.cpp"
			COMMAND IncludedFilesGenerator -fl "\"${ETISS_INCLUDEDFILES}\"" -ns etiss::storedfiles -h "${PROJECT_BINARY_DIR}/include/etiss/IncludedFiles.h" -cpp "${PROJECT_BINARY_DIR}/src/IncludedFiles.cpp" -hi "etiss/IncludedFiles.h"
			WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
			DEPENDS IncludedFilesGenerator ${ETISS_INCLUDEDFILES_DEPENDS}
			COMMENT "Generating code to include some header files into the ETISS libraries"
			)

install(	FILES ${PROJECT_BINARY_DIR}/include/etiss/IncludedFiles.h	DESTINATION  include/etiss)
list( APPEND ETISS_HEADER "${PROJECT_BINARY_DIR}/include/etiss/IncludedFiles.h") 
list( APPEND ETISS_SOURCE "${PROJECT_BINARY_DIR}/src/IncludedFiles.cpp") 

### generate plugin export header with a dummy target
add_library(ETISS_PLUGIN SHARED "${PROJECT_BINARY_DIR}/include/etiss/IncludedFiles.h" "${PROJECT_BINARY_DIR}/src/IncludedFiles.cpp")
SET_TARGET_PROPERTIES(ETISS_PLUGIN PROPERTIES LINKER_LANGUAGE CXX)
GENERATE_EXPORT_HEADER( ETISS_PLUGIN
          BASE_NAME ETISS_PLUGIN
          EXPORT_MACRO_NAME ETISS_PLUGIN_EXPORT
          EXPORT_FILE_NAME include_c/etiss/pluginexport.h
          DEPRECATED_MACRO_NAME ETISS_PLUGIN_DEPRECATED
          NO_EXPORT_MACRO_NAME ETISS_PLUGIN_NOEXPORT
          STATIC_DEFINE ETISS_PLUGIN_STATIC_DEFINE
          NO_DEPRECATED_MACRO_NAME ETISS_PLUGIN_NODEPRECATED
          DEFINE_NO_DEPRECATED
)

### generate ETISS libraries
if (ETISS_SOURCE_INSTALL)
	#dll not supported; we need to create a dll anyway to generate the export headers
	add_library(ETISS SHARED "${PROJECT_BINARY_DIR}/include/etiss/IncludedFiles.h" "${PROJECT_BINARY_DIR}/src/IncludedFiles.cpp")
	SET_TARGET_PROPERTIES(ETISS PROPERTIES LINKER_LANGUAGE CXX)
	#helper target to show source files in ide projects
	add_custom_target(ETISS_src
						SOURCES ${ETISS_SOURCE} ${ETISS_HEADER})
else()
	add_library(ETISS SHARED ${ETISS_SOURCE} ${ETISS_HEADER})
	set_target_properties(ETISS PROPERTIES COMPILE_DEFINITIONS "ETISS_LIB_SHARED=1;ETISS_EXPORTS;ETISS_PLUGIN_EXPORTS")
endif()



GENERATE_EXPORT_HEADER( ETISS
          BASE_NAME ETISS
          EXPORT_MACRO_NAME ETISS_EXPORT
          EXPORT_FILE_NAME include/etiss/export.h
          DEPRECATED_MACRO_NAME ETISS_DEPRECATED
          NO_EXPORT_MACRO_NAME ETISS_NOEXPORT
          STATIC_DEFINE ETISS_STATIC_DEFINE
          NO_DEPRECATED_MACRO_NAME ETISS_NODEPRECATED
          DEFINE_NO_DEPRECATED
)


#file(READ "${PROJECT_BINARY_DIR}/include_c/etiss/pluginexport.h" TMP)
#set(TMP "#define ETISS_PLUGIN_EXPORTS 1\n${TMP}")
#file(WRITE "${PROJECT_BINARY_DIR}/include_c/etiss/pluginexport.h" "${TMP}")
install(FILES ${PROJECT_BINARY_DIR}/include_c/etiss/pluginexport.h ${PROJECT_BINARY_DIR}/include/etiss/export.h
		DESTINATION  include/etiss)

if(NOT ETISS_SOURCE_INSTALL)
install(TARGETS ETISS DESTINATION lib)
endif()



### main executable
if (NOT ETISS_SOURCE_INSTALL)
	add_executable(main main.cpp)
	TARGET_LINK_LIBRARIES(main ETISS ${CMAKE_THREAD_LIBS_INIT})
	if (ETISS_LIBRARIES)
		TARGET_LINK_LIBRARIES(main ${ETISS_LIBRARIES})
	endif()
	if(ETISS_USE_PYTHON)
		TARGET_LINK_LIBRARIES(main ${PYTHON_LIBRARIES})
	endif()
endif()



#currently should be kept on. if at a later time there is a difference between a portable and an installed build this should be used (and moved to the start of this file)
set(ETISS_BUILD_PORTABLE ON)
### as a last install action create a list of plugin libraries in the install directory
string(REPLACE "." "\\\\." REGEX_CMAKE_SHARED_LIBRARY_SUFFIX ${CMAKE_SHARED_LIBRARY_SUFFIX})
install(CODE "
	file(GLOB_RECURSE TMP_PLUGINS ${CMAKE_INSTALL_PREFIX}/lib/plugins/${CMAKE_SHARED_LIBRARY_PREFIX}*${CMAKE_SHARED_LIBRARY_SUFFIX})
	file(WRITE \"${CMAKE_INSTALL_PREFIX}/lib/plugins/list.txt\" \"\")
	foreach(plugin \${TMP_PLUGINS})
		get_filename_component(plugin \${plugin} REALPATH)
		get_filename_component(dir \${plugin} PATH)
		get_filename_component(name \${plugin} NAME)
		string(REGEX REPLACE \"${CMAKE_SHARED_LIBRARY_PREFIX}(.*)${REGEX_CMAKE_SHARED_LIBRARY_SUFFIX}\" \"\\\\1\" name \${name})
	    if (ETISS_BUILD_PORTABLE)
	        file(APPEND \"${CMAKE_INSTALL_PREFIX}/lib/plugins/list.txt\" \"\${name}\\n\")
	    else(ETISS_BUILD_PORTABLE)
		    file(APPEND \"${CMAKE_INSTALL_PREFIX}/lib/plugins/list.txt\" \"\${name},\${dir},\${name}\\n\")
		endif(ETISS_BUILD_PORTABLE)
	endforeach()
	")


if(ETISS_SOURCE_INSTALL)	
list(APPEND ETISS_FILES_SRC ${ETISS_SOURCE})

foreach(sf ${ETISS_FILES_SRC})
	file(TO_CMAKE_PATH "${sf}" sf) # ensure '/' path seperator
	set(NAMECLASH OFF)
	if ("${sf}" MATCHES ".*/src/.*\\.c(pp)?")
		STRING(REGEX REPLACE ".*/src/(.*)" "src/\\1" rel_sf "${sf}")
		list (FIND NAMECLASH_LIST "${relsf}" _index)
		if (${_index} GREATER -1)
			set(NAMECLASH ON)
		else()
			list (APPEND NAMECLASH_LIST "${relsf}")
			get_filename_component(rel_sf_dir "${rel_sf}" DIRECTORY)
			install(FILES ${sf} DESTINATION "${rel_sf_dir}")
			list(APPEND ETISS_SOURCES_RN "${CMAKE_INSTALL_PREFIX}/${rel_sf}")
			message("${sf} will be installed as ${rel_sf}")
		endif()
	endif()
	if(((NOT "${sf}" MATCHES ".*/src/.*\\.c(pp)?") OR NAMECLASH) AND ("${sf}" MATCHES ".*\\.c(pp)?"))
		string(SHA1 IFILE "${sf}")
		get_filename_component(ext "${sf}" EXT)
		install(FILES ${sf} DESTINATION src RENAME ${IFILE}${ext})
		list(APPEND ETISS_SOURCES_RN "${CMAKE_INSTALL_PREFIX}/src/${IFILE}${ext}")
		message("${sf} will be installed as ${IFILE}${ext}")
	endif()
endforeach()

install(FILES src/fpu/softfloat-macros DESTINATION src/fpu)
install(FILES src/fpu/softfloat-specialize DESTINATION src/fpu)
install(FILES src/fpu/softfloat-macros DESTINATION src)
install(FILES src/fpu/softfloat-specialize DESTINATION src)

endif()



################ final cmake file generation #####################
### cmake package files
configure_file(
  "${PROJECT_SOURCE_DIR}/ETISSConfig.cmake.in"
  "${PROJECT_BINARY_DIR}/ETISSConfig.cmake"
  @ONLY
 )
configure_file(
  "${PROJECT_SOURCE_DIR}/ETISSConfigVersion.cmake.in"
  "${PROJECT_BINARY_DIR}/ETISSConfigVersion.cmake"
  @ONLY
 )
install(FILES
  "${PROJECT_BINARY_DIR}/ETISSConfig.cmake"
  "${PROJECT_BINARY_DIR}/ETISSConfigVersion.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)
ETISS_TO_MAKEFILE_LIBRARIES(MK_ETISS_LIBRARIES ${ETISS_LIBRARIES})
configure_file(
  ETISS.mk.in
  ETISS.mk
  @ONLY
 )
 install(FILES
  "${PROJECT_BINARY_DIR}/ETISS.mk"
  DESTINATION include)
  

################ Print out options (and variables)	##############

message(STATUS "ETISS_VERSION_FULL: ${ETISS_VERSION_FULL}")

message(STATUS "ETISS_USE_PYTHON: ${ETISS_USE_PYTHON}")

message(STATUS "ETISS_USE_DLSYM: ${ETISS_USE_DLSYM}")

message(STATUS "ETISS_BUILD_MANUAL_DOC: ${ETISS_BUILD_MANUAL_DOC}")

message(STATUS "ETISS_BUILD_STATIC: ${ETISS_BUILD_STATIC}")

message(STATUS "ETISS_SOURCE_INSTALL: ${ETISS_SOURCE_INSTALL}")

message(STATUS "ETISS_LIBRARIES: ${ETISS_LIBRARIES}")
######################################################################











