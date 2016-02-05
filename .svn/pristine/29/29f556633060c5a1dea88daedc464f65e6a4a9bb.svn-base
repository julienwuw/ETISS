
project(systemc_example)

#find systemc
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")
FIND_PACKAGE(SystemC 2.3) #TLM should be included

#configure libraries
if (SystemC_FOUND)
ETISS_TO_MAKEFILE_LIBRARIES(MK_SystemC_LIBRARIES ${SystemC_LIBRARIES})
else()
set(SystemC_INCLUDE_DIRS "/path/to/systemC-2.3.0/includes")
set(SystemC_LIBRARIES " -L/path/to/systemC-2.3.0/libs -lsystemc -lpthread -ldl")
endif()


#configure makefile
configure_file(
  Makefile.in
  "${PROJECT_BINARY_DIR}/tobeinstalled/Makefile"
  @ONLY
 )
install(FILES "${PROJECT_BINARY_DIR}/tobeinstalled/Makefile"
		DESTINATION examples/systemc
    	PERMISSIONS OWNER_READ GROUP_READ WORLD_READ
)

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/
		DESTINATION examples/systemc
		FILES_MATCHING
    	PATTERN "*.h"
    	PATTERN "*.cpp"
		PATTERN "*.c"
		PATTERN "*.S"
		PATTERN "*.s"
		PATTERN "README"
    	PATTERN "code.bin"
    	PATTERN ".svn" EXCLUDE
		PATTERN "*.in" EXCLUDE
		PATTERN "CMakeLists.txt" EXCLUDE
    	PERMISSIONS OWNER_READ GROUP_READ WORLD_READ
)


list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")


