# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install

# Include any dependencies generated for this target.
include CMakeFiles/IncludedFilesGenerator.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/IncludedFilesGenerator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/IncludedFilesGenerator.dir/flags.make

CMakeFiles/IncludedFilesGenerator.dir/IncludedFilesGenerator.cpp.o: CMakeFiles/IncludedFilesGenerator.dir/flags.make
CMakeFiles/IncludedFilesGenerator.dir/IncludedFilesGenerator.cpp.o: ../IncludedFilesGenerator.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/IncludedFilesGenerator.dir/IncludedFilesGenerator.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/IncludedFilesGenerator.dir/IncludedFilesGenerator.cpp.o -c ../IncludedFilesGenerator.cpp

CMakeFiles/IncludedFilesGenerator.dir/IncludedFilesGenerator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IncludedFilesGenerator.dir/IncludedFilesGenerator.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E ../IncludedFilesGenerator.cpp > CMakeFiles/IncludedFilesGenerator.dir/IncludedFilesGenerator.cpp.i

CMakeFiles/IncludedFilesGenerator.dir/IncludedFilesGenerator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IncludedFilesGenerator.dir/IncludedFilesGenerator.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S ../IncludedFilesGenerator.cpp -o CMakeFiles/IncludedFilesGenerator.dir/IncludedFilesGenerator.cpp.s

CMakeFiles/IncludedFilesGenerator.dir/IncludedFilesGenerator.cpp.o.requires:
.PHONY : CMakeFiles/IncludedFilesGenerator.dir/IncludedFilesGenerator.cpp.o.requires

CMakeFiles/IncludedFilesGenerator.dir/IncludedFilesGenerator.cpp.o.provides: CMakeFiles/IncludedFilesGenerator.dir/IncludedFilesGenerator.cpp.o.requires
	$(MAKE) -f CMakeFiles/IncludedFilesGenerator.dir/build.make CMakeFiles/IncludedFilesGenerator.dir/IncludedFilesGenerator.cpp.o.provides.build
.PHONY : CMakeFiles/IncludedFilesGenerator.dir/IncludedFilesGenerator.cpp.o.provides

CMakeFiles/IncludedFilesGenerator.dir/IncludedFilesGenerator.cpp.o.provides.build: CMakeFiles/IncludedFilesGenerator.dir/IncludedFilesGenerator.cpp.o

# Object files for target IncludedFilesGenerator
IncludedFilesGenerator_OBJECTS = \
"CMakeFiles/IncludedFilesGenerator.dir/IncludedFilesGenerator.cpp.o"

# External object files for target IncludedFilesGenerator
IncludedFilesGenerator_EXTERNAL_OBJECTS =

IncludedFilesGenerator: CMakeFiles/IncludedFilesGenerator.dir/IncludedFilesGenerator.cpp.o
IncludedFilesGenerator: CMakeFiles/IncludedFilesGenerator.dir/build.make
IncludedFilesGenerator: CMakeFiles/IncludedFilesGenerator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable IncludedFilesGenerator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/IncludedFilesGenerator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/IncludedFilesGenerator.dir/build: IncludedFilesGenerator
.PHONY : CMakeFiles/IncludedFilesGenerator.dir/build

CMakeFiles/IncludedFilesGenerator.dir/requires: CMakeFiles/IncludedFilesGenerator.dir/IncludedFilesGenerator.cpp.o.requires
.PHONY : CMakeFiles/IncludedFilesGenerator.dir/requires

CMakeFiles/IncludedFilesGenerator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/IncludedFilesGenerator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/IncludedFilesGenerator.dir/clean

CMakeFiles/IncludedFilesGenerator.dir/depend:
	cd /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0 /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0 /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/CMakeFiles/IncludedFilesGenerator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/IncludedFilesGenerator.dir/depend

