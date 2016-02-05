
unset(LOCAL_SUBDIRS)

# add all example folders that are included
list(APPEND LOCAL_SUBDIRS systemc)
list(APPEND LOCAL_SUBDIRS SW)
list(APPEND LOCAL_SUBDIRS bare_etiss_processor)

foreach(subdir ${LOCAL_SUBDIRS})
	if(IS_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/${subdir})
		if (EXISTS ${CMAKE_CURRENT_LIST_DIR}/${subdir}/CMakeLists.txt)
			add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/${subdir})
			message(STATUS "Including sub project ${subdir}.")
		else(EXISTS ${CMAKE_CURRENT_LIST_DIR}/${subdir}/CMakeLists.txt)
			message(WARNING "Directory ${subdir} is not added to the current build because it lacks a CMakeLists.txt")
		endif(EXISTS ${CMAKE_CURRENT_LIST_DIR}/${subdir}/CMakeLists.txt)
	endif(IS_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/${subdir})
endforeach(subdir ${LOCAL_SUBDIRS})


ETISS_UPDATE_GLOBAL_VARIABLES()
