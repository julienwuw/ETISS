


if (NOT LLVMJIT_TEMPLATE_REINCLUDED)

	set(ETISS_PROJECT_NAME LLVMJIT)
	set(ETISS_PROJECT_PATH ${CMAKE_CURRENT_LIST_DIR})
	
	set(${ETISS_PROJECT_NAME}_MAKEFILE Makefile)

	#set(${ETISS_PROJECT_NAME}_TEMPLATE_REINCLUDE ${CMAKE_CURRENT_LIST_FILE})

	include(../../CMakeLists.txt.project.template)

else (NOT LLVMJIT_TEMPLATE_REINCLUDED)


## TODO search for llvm instad of hardcoding the path
set(LLVMPATH_BIN /nfs/TUEIEDAprojects/SystemDesign/tools/llvm/3.4.2/bin)

# get libraries
execute_process(COMMAND ${LLVMPATH_BIN}/llvm-config --libfiles 
		OUTPUT_VARIABLE LLVM_LIBS)
# get libraries convert spaces to semicolons
string (REPLACE " " ";" LLVM_LIBS "${LLVM_LIBS}")
string (REPLACE "\n" ";" LLVM_LIBS "${LLVM_LIBS}")
#get include directories
execute_process(COMMAND ${LLVMPATH_BIN}/llvm-config --includedir
		OUTPUT_VARIABLE LLVM_INCLUDES)
string (REPLACE " " ";" LLVM_INCLUDES "${LLVM_INCLUDES}")
string (REPLACE "\n" ";" LLVM_INCLUDES "${LLVM_INCLUDES}")

execute_process(COMMAND ${LLVMPATH_BIN}/llvm-config --cxxflags
		OUTPUT_VARIABLE LLVM_CPPFLAGS)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LLVM_CPPFLAGS} ")

set(LLVMJIT_ADDITIONAL_LIBRARIES ${LLVMJIT_ADDITIONAL_LIBRARIES} pthread "-Wl,--whole-archive" ${LLVM_LIBS} "-Wl,--no-whole-archive")

include_directories(${LLVM_INCLUDES})

file(GLOB LLVMJIT_ADDITIONAL_PROJECT_FILES src/*.cpp)

endif(NOT LLVMJIT_TEMPLATE_REINCLUDED)

