# Install script for directory: /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/installed")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Debug")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/IncludedFilesGenerator" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/IncludedFilesGenerator")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/IncludedFilesGenerator"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/IncludedFilesGenerator")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/IncludedFilesGenerator" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/IncludedFilesGenerator")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/IncludedFilesGenerator")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/etiss" TYPE FILE FILES "/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/include/etiss/config.h")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/include/" FILES_MATCHING REGEX "/[^/]*\\.h$" REGEX "/[^/]*\\.hpp$" REGEX "/\\.svn$" EXCLUDE REGEX "/dox$" EXCLUDE PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/include_c/" FILES_MATCHING REGEX "/[^/]*\\.h$" REGEX "/[^/]*\\.hpp$" REGEX "/\\.svn$" EXCLUDE PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/doc" TYPE DIRECTORY OPTIONAL FILES "/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/doc/" FILES_MATCHING REGEX "/[^/]*$" PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/etiss" TYPE FILE FILES "/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/include/etiss/IncludedFiles.h")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/etiss" TYPE FILE FILES
    "/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/include_c/etiss/pluginexport.h"
    "/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/include/etiss/export.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libETISS.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libETISS.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libETISS.so"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/libETISS.so")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libETISS.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libETISS.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libETISS.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  
	file(GLOB_RECURSE TMP_PLUGINS /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/installed/lib/plugins/lib*.so)
	file(WRITE "/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/installed/lib/plugins/list.txt" "")
	foreach(plugin ${TMP_PLUGINS})
		get_filename_component(plugin ${plugin} REALPATH)
		get_filename_component(dir ${plugin} PATH)
		get_filename_component(name ${plugin} NAME)
		string(REGEX REPLACE "lib(.*)\\.so" "\\1" name ${name})
	    if (ETISS_BUILD_PORTABLE)
	        file(APPEND "/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/installed/lib/plugins/list.txt" "${name}\n")
	    else(ETISS_BUILD_PORTABLE)
		    file(APPEND "/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/installed/lib/plugins/list.txt" "${name},${dir},${name}\n")
		endif(ETISS_BUILD_PORTABLE)
	endforeach()
	
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/CMake/ETISS" TYPE FILE FILES
    "/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/ETISSConfig.cmake"
    "/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/ETISSConfigVersion.cmake"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/ETISS.mk")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/src/cmake_install.cmake")
  INCLUDE("/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/include/cmake_install.cmake")
  INCLUDE("/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/include_c/cmake_install.cmake")
  INCLUDE("/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/projects/cmake_install.cmake")
  INCLUDE("/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/ArchImpl/cmake_install.cmake")
  INCLUDE("/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/JITImpl/cmake_install.cmake")
  INCLUDE("/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/PluginImpl/cmake_install.cmake")
  INCLUDE("/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/examples/cmake_install.cmake")
  INCLUDE("/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/systemc/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
