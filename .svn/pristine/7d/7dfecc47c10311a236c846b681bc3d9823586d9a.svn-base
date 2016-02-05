

if (NOT DEFINED ETISS_SYSTEMC_INCLUDE_DIRS AND NOT DEFINED ETISS_SYSTEMC_LIBS)
	set(ETISS_SYSTEMC_PREFIX "/usr/local/research/projects/SystemDesign/tools/systemc/systemc-2.3.0/") ### TODO: change as needed. adds a search path to systems
	list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")
	FIND_PACKAGE(SystemC 2.3) #TLM should be included
	if (SystemC_FOUND)
		set(ETISS_SYSTEMC_INCLUDE_DIRS ${SystemC_INCLUDE_DIRS})
		set(ETISS_SYSTEMC_LIBS ${SystemC_LIBRARIES})
	endif()
endif()


if(DEFINED ETISS_SYSTEMC_INCLUDE_DIRS AND DEFINED ETISS_SYSTEMC_LIBS)
	foreach(lib ${ETISS_SYSTEMC_LIBS})
		get_filename_component(TMP "${lib}" PATH)
		LINK_DIRECTORIES("${TMP}")
		get_filename_component(TMP "${lib}" NAME)
		list(APPEND ETISS_SYSTEMC_LINK "${TMP}")
		message("systemc lib: ${TMP}")
	endforeach()
	INCLUDE_DIRECTORIES(${ETISS_SYSTEMC_INCLUDE_DIRS})
	
	INCLUDE_DIRECTORIES(${CMAKE_CURRENT_LIST_DIR}/cpu_systemc_etiss_lib)
	INCLUDE_DIRECTORIES(${CMAKE_CURRENT_LIST_DIR}/cpu_systemc_interface_lib)
	INCLUDE_DIRECTORIES(${CMAKE_CURRENT_LIST_DIR})
	
	file(GLOB_RECURSE TMP *.cpp)
	add_executable(main_sc ${TMP})
	target_link_libraries(main_sc ETISS ${ETISS_SYSTEMC_LIBS} ${ETISS_FILES_LNK})
	
endif()
