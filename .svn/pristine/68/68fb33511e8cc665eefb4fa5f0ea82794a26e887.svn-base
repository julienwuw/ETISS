

project(bare_etiss_processor_example)


configure_file(
  CMakeLists.txt.in
  "${PROJECT_BINARY_DIR}/tobeinstalled/CMakeLists.txt"
  @ONLY
 )
install(FILES "${PROJECT_BINARY_DIR}/tobeinstalled/CMakeLists.txt"
		DESTINATION examples/bare_etiss_processor
    	PERMISSIONS OWNER_READ GROUP_READ WORLD_READ
)

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/
		DESTINATION examples/bare_etiss_processor
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
