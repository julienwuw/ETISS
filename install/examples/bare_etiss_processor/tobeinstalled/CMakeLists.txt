
cmake_minimum_required(VERSION 2.8)
project(bare_etiss_processor)

# may not be needed if ETISS was installed into the default directory (e.g. /usr/... for linux or "C:\Program Files\..." for windows)
# if ETISS cannot be found search for the file ETISSConfig.cmake
set(ETISS_DIR "/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/installed/lib/CMake/ETISS")


#NOTE: etiss NEEDS at least the c++0x standard as implemented by gcc. C++11 recommended. the compiler used here must be the same as the compiler used for etiss. 
# by default the -std=c++0x / -std= c++11 options are set in the package file unless ETISS_DISABLE_COMPILERFLAGS is set to on

#find ETISS package
find_package(ETISS 0.4)

#add include directories
include_directories(${ETISS_INCLUDE_DIRS})

#main executable
add_executable(main main.cpp)

#link required libraries
#not python libraries may not be found and this could lead to problems if ETISS was configure to use python.
target_link_libraries(main ${ETISS_LIBRARIES})
