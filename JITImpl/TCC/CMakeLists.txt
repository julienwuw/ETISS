


if (NOT TCCJIT_TEMPLATE_REINCLUDED)

	set(ETISS_PROJECT_NAME TCCJIT)
	set(ETISS_PROJECT_PATH ${CMAKE_CURRENT_LIST_DIR})

	set(${ETISS_PROJECT_NAME}_TEMPLATE_REINCLUDE ${CMAKE_CURRENT_LIST_FILE})

	include(../../CMakeLists.txt.project.template)

else (NOT TCCJIT_TEMPLATE_REINCLUDED)


### configure tcc architecture
unset(TCCJIT_ARCH)
if(UNIX)
	set(TCCJIT_ARCH unix)
elseif(WIN32)
	if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
		set(TCCJIT_ARCH win64)
	else()
		set(TCCJIT_ARCH win32)
	endif()
else()
	message(ERROR "cannot build TCCJIT on this unknown system")
endif()

#download and extract tcc (if neccessary)
if (NOT EXISTS ${PROJECT_BINARY_DIR}/tcc_${TCCJIT_ARCH})
	if(${TCCJIT_ARCH} STREQUAL unix)
		if (EXISTS ${PROJECT_SOURCE_DIR}/tcc-0.9.26.tar.bz2)
			execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${PROJECT_SOURCE_DIR}/tcc-0.9.26.tar.bz2
					WORKING_DIRECTORY ${PROJECT_BINARY_DIR})
		else()
			file(DOWNLOAD http://download.savannah.gnu.org/releases/tinycc/tcc-0.9.26.tar.bz2 ${PROJECT_BINARY_DIR}/tcc-0.9.26.tar.bz2 SHOW_PROGRESS)
			execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${PROJECT_BINARY_DIR}/tcc-0.9.26.tar.bz2
					WORKING_DIRECTORY ${PROJECT_BINARY_DIR})
		endif()
		file(RENAME ${PROJECT_BINARY_DIR}/tcc-0.9.26 ${PROJECT_BINARY_DIR}/tcc_unix)
		file(REMOVE ${PROJECT_BINARY_DIR}/tcc-0.9.26.tar.bz2)
		file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/tcc_unix/build)
		execute_process(COMMAND ${PROJECT_BINARY_DIR}/tcc_unix/configure --extra-cflags=-fPIC
				WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/tcc_unix/build)
		execute_process(COMMAND make
				WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/tcc_unix/build)
	elseif(${TCCJIT_ARCH} STREQUAL win64)
		if (EXISTS ${PROJECT_SOURCE_DIR}/tcc-0.9.26.tar.bz2)
			execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${PROJECT_SOURCE_DIR}/tcc-0.9.26-win64-bin.zip
					WORKING_DIRECTORY ${PROJECT_BINARY_DIR})
		else()
			file(DOWNLOAD http://download.savannah.gnu.org/releases/tinycc/tcc-0.9.26-win64-bin.zip ${PROJECT_BINARY_DIR}/tcc-0.9.26-win64-bin.zip SHOW_PROGRESS)
			execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${PROJECT_BINARY_DIR}/tcc-0.9.26-win64-bin.zip
					WORKING_DIRECTORY ${PROJECT_BINARY_DIR})
		endif()
		file(RENAME ${PROJECT_BINARY_DIR}/tcc ${PROJECT_BINARY_DIR}/tcc_win64)
		file(REMOVE ${PROJECT_BINARY_DIR}/tcc-0.9.26-win64-bin.zip)
	elseif(${TCCJIT_ARCH} STREQUAL win32)
		if (EXISTS ${PROJECT_SOURCE_DIR}/tcc-0.9.26.tar.bz2)
			execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${PROJECT_SOURCE_DIR}/tcc-0.9.26-win32-bin.zip
					WORKING_DIRECTORY ${PROJECT_BINARY_DIR})
		else()
			file(DOWNLOAD http://download.savannah.gnu.org/releases/tinycc/tcc-0.9.26-win32-bin.zip ${PROJECT_BINARY_DIR}/tcc-0.9.26-win32-bin.zip SHOW_PROGRESS)
			execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${PROJECT_BINARY_DIR}/tcc-0.9.26-win32-bin.zip
					WORKING_DIRECTORY ${PROJECT_BINARY_DIR})
		endif()
		file(RENAME ${PROJECT_BINARY_DIR}/tcc ${PROJECT_BINARY_DIR}/tcc_win32)
		file(REMOVE ${PROJECT_BINARY_DIR}/tcc-0.9.26-win32-bin.zip)
	else()
		message(ERROR "Unknown TCCJIT_ARCH value")
	endif()

endif()

### add libraries
if(${TCCJIT_ARCH} STREQUAL unix)
	message("setting TCCJIT_ADDITIONAL_LIBRARIES...")
	set(TCCJIT_ADDITIONAL_LIBRARIES ${TCCJIT_ADDITIONAL_LIBRARIES} "${PROJECT_BINARY_DIR}/tcc_unix/build/libtcc.a")
	message("setting TCCJIT_ADDITIONAL_LIBRARIES to ${TCCJIT_ADDITIONAL_LIBRARIES}")
	include_directories("${PROJECT_BINARY_DIR}/tcc_unix")
	install(FILES "${PROJECT_BINARY_DIR}/tcc_unix/libtcc.h"
			DESTINATION include)
	set(TCC_H_PATH ${PROJECT_BINARY_DIR}/tcc_unix)
	list(APPEND TCC_H_FILES "tcc/lib/libtcc1.a,${TCC_H_PATH}/build/libtcc1.a")
	list(APPEND TCC_H_FILES "tcc/libtcc1.a,${TCC_H_PATH}/build/libtcc1.a")
elseif(${TCCJIT_ARCH} STREQUAL win64)
	include_directories("${PROJECT_BINARY_DIR}/tcc_win64/libtcc")
	set(TCC_H_PATH "${PROJECT_BINARY_DIR}/tcc_win64")
	add_custom_command(OUTPUT "${PROJECT_BINARY_DIR}/tcc_win64/libtcc.lib"
			COMMAND lib "/DEF:\"${PROJECT_BINARY_DIR}/tcc_win64/libtcc/libtcc.def\"" /MACHINE:X64 /OUT:\"${PROJECT_BINARY_DIR}/tcc_win64/libtcc.lib\"
			WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
			)
	install(FILES "${PROJECT_BINARY_DIR}/tcc_win64/libtcc/libtcc.h"
			DESTINATION include)
	install(FILES "${PROJECT_BINARY_DIR}/tcc_win64/libtcc.lib"
			DESTINATION lib)
	install(FILES "${PROJECT_BINARY_DIR}/tcc_win64/libtcc.dll"
			DESTINATION lib)
	list(APPEND ETISS_FILES_LNK "${CMAKE_INSTALL_PREFIX}/lib/libtcc.lib")
	set(${ETISS_PROJECT_NAME}_ADDITIONAL_LIBRARIES ${${ETISS_PROJECT_NAME}_ADDITIONAL_LIBRARIES} ${PROJECT_BINARY_DIR}/tcc_win64/libtcc.lib)
	set(${ETISS_PROJECT_NAME}_ADDITIONAL_PROJECT_FILES ${${ETISS_PROJECT_NAME}_ADDITIONAL_PROJECT_FILES} ${PROJECT_BINARY_DIR}/tcc_win64/libtcc/libtcc.def ${PROJECT_BINARY_DIR}/tcc_win64/libtcc.dll ${PROJECT_BINARY_DIR}/tcc_win64/libtcc.lib)
	list(APPEND TCC_H_FILES "tcc/lib/libtcc1.a,${TCC_H_PATH}/lib/libtcc1.a")
	list(APPEND TCC_H_FILES "tcc/libtcc1.a,${TCC_H_PATH}/lib/libtcc1.a")
	list(APPEND ETISS_FILES_LNK "Dbghelp.lib")
elseif(${TCCJIT_ARCH} STREQUAL win32)
	include_directories("${PROJECT_BINARY_DIR}/tcc_win32/libtcc")
	set(TCC_H_PATH ${PROJECT_BINARY_DIR}/tcc_win32)
	add_custom_command(OUTPUT "${PROJECT_BINARY_DIR}/tcc_win32/libtcc.lib"
			COMMAND lib "/DEF:\"${PROJECT_BINARY_DIR}/tcc_win32/libtcc/libtcc.def\"" /MACHINE:X86 /OUT:\"${PROJECT_BINARY_DIR}/tcc_win32/libtcc.lib\"
			WORKING_DIRECTORY "${PROJECT_BINARY_DIR}"
			)
	install(FILES "${PROJECT_BINARY_DIR}/tcc_win32/libtcc/libtcc.h"
			DESTINATION include)
	install(FILES "${PROJECT_BINARY_DIR}/tcc_win32/libtcc.lib"
			DESTINATION lib)
	install(FILES "${PROJECT_BINARY_DIR}/tcc_win32/libtcc.dll"
			DESTINATION lib)
	list(APPEND ETISS_FILES_LNK "${CMAKE_INSTALL_PREFIX}/lib/libtcc.lib")
	set(${ETISS_PROJECT_NAME}_ADDITIONAL_LIBRARIES ${${ETISS_PROJECT_NAME}_ADDITIONAL_LIBRARIES} "${PROJECT_BINARY_DIR}/tcc_win32/libtcc.lib")
	set(${ETISS_PROJECT_NAME}_ADDITIONAL_PROJECT_FILES ${${ETISS_PROJECT_NAME}_ADDITIONAL_PROJECT_FILES} "${PROJECT_BINARY_DIR}/tcc_win32/libtcc/libtcc.def" "${PROJECT_BINARY_DIR}/tcc_win32/libtcc.dll" "${PROJECT_BINARY_DIR}/tcc_win32/libtcc.lib")
	list(APPEND TCC_H_FILES "tcc/lib/libtcc1.a,${TCC_H_PATH}/lib/libtcc1.a")
	list(APPEND TCC_H_FILES "tcc/libtcc1.a,${TCC_H_PATH}/lib/libtcc1.a")
	list(APPEND ETISS_FILES_LNK "Dbghelp.lib")
else()
	message(ERROR "Unknown TCCJIT_ARCH value")
endif()

###include headers

file(GLOB_RECURSE TCC_H_FILES_TMP RELATIVE "${TCC_H_PATH}" "${TCC_H_PATH}/include/*")
foreach(tccfile ${TCC_H_FILES_TMP})
	#file(TO_NATIVE_PATH "tcc/${tccfile}" pp1)
	set(pp1 "tcc/${tccfile}")
	file(TO_NATIVE_PATH "${tccfile}" pp2)
	#file(TO_NATIVE_PATH "${TCC_H_PATH}/${tccfile}" pp2)
	list(APPEND TCC_H_FILES "${pp1},${pp2}")
	message("${pp1},${pp2}")
endforeach()
#string(REPLACE "winapi/winre.h" "winapi/winreg.h" TCC_H_FILES "${TCC_H_FILES}")
add_custom_command(	OUTPUT ${PROJECT_BINARY_DIR}/TCCIncludedFiles.h ${PROJECT_BINARY_DIR}/TCCIncludedFiles.cpp 
			COMMAND IncludedFilesGenerator -fl "${TCC_H_FILES}" -ns tcc::storedfiles -h "${PROJECT_BINARY_DIR}/TCCIncludedFiles.h" -cpp "${PROJECT_BINARY_DIR}/TCCIncludedFiles.cpp" -hi "TCCIncludedFiles.h"
			WORKING_DIRECTORY ${TCC_H_PATH}
			DEPENDS IncludedFilesGenerator 
			COMMENT "Generating code to include some header files for TCCJIT: ${TCC_H_FILES}"
			VERBATIM
			)
set(${ETISS_PROJECT_NAME}_ADDITIONAL_PROJECT_FILES ${${ETISS_PROJECT_NAME}_ADDITIONAL_PROJECT_FILES} ${PROJECT_BINARY_DIR}/TCCIncludedFiles.cpp ${PROJECT_BINARY_DIR}/TCCIncludedFiles.h)
			
endif(NOT TCCJIT_TEMPLATE_REINCLUDED)




