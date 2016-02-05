# Install script for directory: /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/JITImpl/LLVM

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
  
							if(NOT EXISTS /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/JITImpl/LLVM/libLLVMJIT.so)
								if(EXISTS /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/JITImpl/LLVM/build/libLLVMJIT.so)
									message(WARNING "/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/JITImpl/LLVM/build/libLLVMJIT.so should be moved to /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/JITImpl/LLVM/libLLVMJIT.so")
									execute_process(COMMAND /usr/bin/cmake -E copy "/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/JITImpl/LLVM/build/libLLVMJIT.so" "/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/JITImpl/LLVM/libLLVMJIT.so")
								elseif(EXISTS /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/JITImpl/LLVM/libLLVMJIT.so)
									message(WARNING "/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/JITImpl/LLVM/libLLVMJIT.so should be moved to /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/JITImpl/LLVM/libLLVMJIT.so")
									execute_process(COMMAND /usr/bin/cmake -E copy "/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/JITImpl/LLVM/libLLVMJIT.so" "/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/JITImpl/LLVM/libLLVMJIT.so")
								else()
									message(WARNING "Installation of makefile project LLVMJIT failed. /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/JITImpl/LLVM/libLLVMJIT.so was not available to install")
								endif()
							endif()
						
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/plugins" TYPE FILE OPTIONAL FILES "/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/JITImpl/LLVM/libLLVMJIT.so")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

