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
include ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/depend.make

# Include the progress variables for this target.
include ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/progress.make

# Include the compile flags for this target's objects.
include ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/flags.make

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KGDBCore.cpp.o: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/flags.make
ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KGDBCore.cpp.o: ../ArchImpl/OR1K/OR1KGDBCore.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KGDBCore.cpp.o"
	cd ArchImpl/OR1K && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OR1KArch.dir/OR1KGDBCore.cpp.o -c ../../../ArchImpl/OR1K/OR1KGDBCore.cpp

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KGDBCore.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OR1KArch.dir/OR1KGDBCore.cpp.i"
	cd ArchImpl/OR1K && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E ../../../ArchImpl/OR1K/OR1KGDBCore.cpp > CMakeFiles/OR1KArch.dir/OR1KGDBCore.cpp.i

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KGDBCore.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OR1KArch.dir/OR1KGDBCore.cpp.s"
	cd ArchImpl/OR1K && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S ../../../ArchImpl/OR1K/OR1KGDBCore.cpp -o CMakeFiles/OR1KArch.dir/OR1KGDBCore.cpp.s

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KGDBCore.cpp.o.requires:
.PHONY : ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KGDBCore.cpp.o.requires

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KGDBCore.cpp.o.provides: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KGDBCore.cpp.o.requires
	$(MAKE) -f ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/build.make ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KGDBCore.cpp.o.provides.build
.PHONY : ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KGDBCore.cpp.o.provides

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KGDBCore.cpp.o.provides.build: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KGDBCore.cpp.o

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORFPX32.cpp.o: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/flags.make
ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORFPX32.cpp.o: ../ArchImpl/OR1K/ORFPX32.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORFPX32.cpp.o"
	cd ArchImpl/OR1K && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OR1KArch.dir/ORFPX32.cpp.o -c ../../../ArchImpl/OR1K/ORFPX32.cpp

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORFPX32.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OR1KArch.dir/ORFPX32.cpp.i"
	cd ArchImpl/OR1K && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E ../../../ArchImpl/OR1K/ORFPX32.cpp > CMakeFiles/OR1KArch.dir/ORFPX32.cpp.i

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORFPX32.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OR1KArch.dir/ORFPX32.cpp.s"
	cd ArchImpl/OR1K && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S ../../../ArchImpl/OR1K/ORFPX32.cpp -o CMakeFiles/OR1KArch.dir/ORFPX32.cpp.s

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORFPX32.cpp.o.requires:
.PHONY : ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORFPX32.cpp.o.requires

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORFPX32.cpp.o.provides: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORFPX32.cpp.o.requires
	$(MAKE) -f ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/build.make ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORFPX32.cpp.o.provides.build
.PHONY : ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORFPX32.cpp.o.provides

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORFPX32.cpp.o.provides.build: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORFPX32.cpp.o

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORBIS32_II.cpp.o: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/flags.make
ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORBIS32_II.cpp.o: ../ArchImpl/OR1K/ORBIS32_II.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORBIS32_II.cpp.o"
	cd ArchImpl/OR1K && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OR1KArch.dir/ORBIS32_II.cpp.o -c ../../../ArchImpl/OR1K/ORBIS32_II.cpp

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORBIS32_II.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OR1KArch.dir/ORBIS32_II.cpp.i"
	cd ArchImpl/OR1K && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E ../../../ArchImpl/OR1K/ORBIS32_II.cpp > CMakeFiles/OR1KArch.dir/ORBIS32_II.cpp.i

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORBIS32_II.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OR1KArch.dir/ORBIS32_II.cpp.s"
	cd ArchImpl/OR1K && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S ../../../ArchImpl/OR1K/ORBIS32_II.cpp -o CMakeFiles/OR1KArch.dir/ORBIS32_II.cpp.s

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORBIS32_II.cpp.o.requires:
.PHONY : ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORBIS32_II.cpp.o.requires

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORBIS32_II.cpp.o.provides: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORBIS32_II.cpp.o.requires
	$(MAKE) -f ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/build.make ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORBIS32_II.cpp.o.provides.build
.PHONY : ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORBIS32_II.cpp.o.provides

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORBIS32_II.cpp.o.provides.build: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORBIS32_II.cpp.o

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KArch.cpp.o: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/flags.make
ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KArch.cpp.o: ../ArchImpl/OR1K/OR1KArch.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KArch.cpp.o"
	cd ArchImpl/OR1K && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OR1KArch.dir/OR1KArch.cpp.o -c ../../../ArchImpl/OR1K/OR1KArch.cpp

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KArch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OR1KArch.dir/OR1KArch.cpp.i"
	cd ArchImpl/OR1K && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E ../../../ArchImpl/OR1K/OR1KArch.cpp > CMakeFiles/OR1KArch.dir/OR1KArch.cpp.i

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KArch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OR1KArch.dir/OR1KArch.cpp.s"
	cd ArchImpl/OR1K && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S ../../../ArchImpl/OR1K/OR1KArch.cpp -o CMakeFiles/OR1KArch.dir/OR1KArch.cpp.s

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KArch.cpp.o.requires:
.PHONY : ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KArch.cpp.o.requires

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KArch.cpp.o.provides: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KArch.cpp.o.requires
	$(MAKE) -f ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/build.make ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KArch.cpp.o.provides.build
.PHONY : ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KArch.cpp.o.provides

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KArch.cpp.o.provides.build: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KArch.cpp.o

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1K_Helper.cpp.o: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/flags.make
ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1K_Helper.cpp.o: ../ArchImpl/OR1K/OR1K_Helper.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1K_Helper.cpp.o"
	cd ArchImpl/OR1K && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OR1KArch.dir/OR1K_Helper.cpp.o -c ../../../ArchImpl/OR1K/OR1K_Helper.cpp

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1K_Helper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OR1KArch.dir/OR1K_Helper.cpp.i"
	cd ArchImpl/OR1K && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E ../../../ArchImpl/OR1K/OR1K_Helper.cpp > CMakeFiles/OR1KArch.dir/OR1K_Helper.cpp.i

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1K_Helper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OR1KArch.dir/OR1K_Helper.cpp.s"
	cd ArchImpl/OR1K && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S ../../../ArchImpl/OR1K/OR1K_Helper.cpp -o CMakeFiles/OR1KArch.dir/OR1K_Helper.cpp.s

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1K_Helper.cpp.o.requires:
.PHONY : ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1K_Helper.cpp.o.requires

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1K_Helper.cpp.o.provides: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1K_Helper.cpp.o.requires
	$(MAKE) -f ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/build.make ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1K_Helper.cpp.o.provides.build
.PHONY : ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1K_Helper.cpp.o.provides

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1K_Helper.cpp.o.provides.build: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1K_Helper.cpp.o

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KTimer.cpp.o: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/flags.make
ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KTimer.cpp.o: ../ArchImpl/OR1K/OR1KTimer.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KTimer.cpp.o"
	cd ArchImpl/OR1K && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OR1KArch.dir/OR1KTimer.cpp.o -c ../../../ArchImpl/OR1K/OR1KTimer.cpp

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KTimer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OR1KArch.dir/OR1KTimer.cpp.i"
	cd ArchImpl/OR1K && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E ../../../ArchImpl/OR1K/OR1KTimer.cpp > CMakeFiles/OR1KArch.dir/OR1KTimer.cpp.i

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KTimer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OR1KArch.dir/OR1KTimer.cpp.s"
	cd ArchImpl/OR1K && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S ../../../ArchImpl/OR1K/OR1KTimer.cpp -o CMakeFiles/OR1KArch.dir/OR1KTimer.cpp.s

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KTimer.cpp.o.requires:
.PHONY : ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KTimer.cpp.o.requires

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KTimer.cpp.o.provides: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KTimer.cpp.o.requires
	$(MAKE) -f ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/build.make ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KTimer.cpp.o.provides.build
.PHONY : ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KTimer.cpp.o.provides

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KTimer.cpp.o.provides.build: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KTimer.cpp.o

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KArch_fpu.cpp.o: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/flags.make
ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KArch_fpu.cpp.o: ../ArchImpl/OR1K/OR1KArch_fpu.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KArch_fpu.cpp.o"
	cd ArchImpl/OR1K && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OR1KArch.dir/OR1KArch_fpu.cpp.o -c ../../../ArchImpl/OR1K/OR1KArch_fpu.cpp

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KArch_fpu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OR1KArch.dir/OR1KArch_fpu.cpp.i"
	cd ArchImpl/OR1K && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E ../../../ArchImpl/OR1K/OR1KArch_fpu.cpp > CMakeFiles/OR1KArch.dir/OR1KArch_fpu.cpp.i

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KArch_fpu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OR1KArch.dir/OR1KArch_fpu.cpp.s"
	cd ArchImpl/OR1K && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S ../../../ArchImpl/OR1K/OR1KArch_fpu.cpp -o CMakeFiles/OR1KArch.dir/OR1KArch_fpu.cpp.s

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KArch_fpu.cpp.o.requires:
.PHONY : ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KArch_fpu.cpp.o.requires

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KArch_fpu.cpp.o.provides: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KArch_fpu.cpp.o.requires
	$(MAKE) -f ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/build.make ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KArch_fpu.cpp.o.provides.build
.PHONY : ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KArch_fpu.cpp.o.provides

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KArch_fpu.cpp.o.provides.build: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KArch_fpu.cpp.o

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1200Timing.cpp.o: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/flags.make
ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1200Timing.cpp.o: ../ArchImpl/OR1K/OR1200Timing.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1200Timing.cpp.o"
	cd ArchImpl/OR1K && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OR1KArch.dir/OR1200Timing.cpp.o -c ../../../ArchImpl/OR1K/OR1200Timing.cpp

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1200Timing.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OR1KArch.dir/OR1200Timing.cpp.i"
	cd ArchImpl/OR1K && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E ../../../ArchImpl/OR1K/OR1200Timing.cpp > CMakeFiles/OR1KArch.dir/OR1200Timing.cpp.i

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1200Timing.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OR1KArch.dir/OR1200Timing.cpp.s"
	cd ArchImpl/OR1K && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S ../../../ArchImpl/OR1K/OR1200Timing.cpp -o CMakeFiles/OR1KArch.dir/OR1200Timing.cpp.s

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1200Timing.cpp.o.requires:
.PHONY : ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1200Timing.cpp.o.requires

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1200Timing.cpp.o.provides: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1200Timing.cpp.o.requires
	$(MAKE) -f ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/build.make ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1200Timing.cpp.o.provides.build
.PHONY : ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1200Timing.cpp.o.provides

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1200Timing.cpp.o.provides.build: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1200Timing.cpp.o

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORBIS32_I.cpp.o: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/flags.make
ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORBIS32_I.cpp.o: ../ArchImpl/OR1K/ORBIS32_I.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORBIS32_I.cpp.o"
	cd ArchImpl/OR1K && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OR1KArch.dir/ORBIS32_I.cpp.o -c ../../../ArchImpl/OR1K/ORBIS32_I.cpp

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORBIS32_I.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OR1KArch.dir/ORBIS32_I.cpp.i"
	cd ArchImpl/OR1K && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E ../../../ArchImpl/OR1K/ORBIS32_I.cpp > CMakeFiles/OR1KArch.dir/ORBIS32_I.cpp.i

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORBIS32_I.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OR1KArch.dir/ORBIS32_I.cpp.s"
	cd ArchImpl/OR1K && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S ../../../ArchImpl/OR1K/ORBIS32_I.cpp -o CMakeFiles/OR1KArch.dir/ORBIS32_I.cpp.s

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORBIS32_I.cpp.o.requires:
.PHONY : ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORBIS32_I.cpp.o.requires

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORBIS32_I.cpp.o.provides: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORBIS32_I.cpp.o.requires
	$(MAKE) -f ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/build.make ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORBIS32_I.cpp.o.provides.build
.PHONY : ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORBIS32_I.cpp.o.provides

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORBIS32_I.cpp.o.provides.build: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORBIS32_I.cpp.o

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KIncludedFiles.cpp.o: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/flags.make
ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KIncludedFiles.cpp.o: ArchImpl/OR1K/OR1KIncludedFiles.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KIncludedFiles.cpp.o"
	cd ArchImpl/OR1K && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OR1KArch.dir/OR1KIncludedFiles.cpp.o -c OR1KIncludedFiles.cpp

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KIncludedFiles.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OR1KArch.dir/OR1KIncludedFiles.cpp.i"
	cd ArchImpl/OR1K && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E OR1KIncludedFiles.cpp > CMakeFiles/OR1KArch.dir/OR1KIncludedFiles.cpp.i

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KIncludedFiles.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OR1KArch.dir/OR1KIncludedFiles.cpp.s"
	cd ArchImpl/OR1K && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S OR1KIncludedFiles.cpp -o CMakeFiles/OR1KArch.dir/OR1KIncludedFiles.cpp.s

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KIncludedFiles.cpp.o.requires:
.PHONY : ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KIncludedFiles.cpp.o.requires

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KIncludedFiles.cpp.o.provides: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KIncludedFiles.cpp.o.requires
	$(MAKE) -f ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/build.make ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KIncludedFiles.cpp.o.provides.build
.PHONY : ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KIncludedFiles.cpp.o.provides

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KIncludedFiles.cpp.o.provides.build: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KIncludedFiles.cpp.o

ArchImpl/OR1K/OR1KIncludedFiles.h: IncludedFilesGenerator
ArchImpl/OR1K/OR1KIncludedFiles.h: ../ArchImpl/OR1K/OR1K.h
	$(CMAKE_COMMAND) -E cmake_progress_report /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/CMakeFiles $(CMAKE_PROGRESS_11)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating code to include some header files for OR1KArch"
	cd ../ArchImpl/OR1K && /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/IncludedFilesGenerator -fl include_c/Arch/OR1K/OR1K.h,/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/ArchImpl/OR1K/OR1K.h -ns or1k::storedfiles -h /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/ArchImpl/OR1K/OR1KIncludedFiles.h -cpp /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/ArchImpl/OR1K/OR1KIncludedFiles.cpp -hi OR1KIncludedFiles.h

ArchImpl/OR1K/OR1KIncludedFiles.cpp: ArchImpl/OR1K/OR1KIncludedFiles.h

# Object files for target OR1KArch
OR1KArch_OBJECTS = \
"CMakeFiles/OR1KArch.dir/OR1KGDBCore.cpp.o" \
"CMakeFiles/OR1KArch.dir/ORFPX32.cpp.o" \
"CMakeFiles/OR1KArch.dir/ORBIS32_II.cpp.o" \
"CMakeFiles/OR1KArch.dir/OR1KArch.cpp.o" \
"CMakeFiles/OR1KArch.dir/OR1K_Helper.cpp.o" \
"CMakeFiles/OR1KArch.dir/OR1KTimer.cpp.o" \
"CMakeFiles/OR1KArch.dir/OR1KArch_fpu.cpp.o" \
"CMakeFiles/OR1KArch.dir/OR1200Timing.cpp.o" \
"CMakeFiles/OR1KArch.dir/ORBIS32_I.cpp.o" \
"CMakeFiles/OR1KArch.dir/OR1KIncludedFiles.cpp.o"

# External object files for target OR1KArch
OR1KArch_EXTERNAL_OBJECTS =

ArchImpl/OR1K/libOR1KArch.so: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KGDBCore.cpp.o
ArchImpl/OR1K/libOR1KArch.so: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORFPX32.cpp.o
ArchImpl/OR1K/libOR1KArch.so: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORBIS32_II.cpp.o
ArchImpl/OR1K/libOR1KArch.so: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KArch.cpp.o
ArchImpl/OR1K/libOR1KArch.so: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1K_Helper.cpp.o
ArchImpl/OR1K/libOR1KArch.so: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KTimer.cpp.o
ArchImpl/OR1K/libOR1KArch.so: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KArch_fpu.cpp.o
ArchImpl/OR1K/libOR1KArch.so: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1200Timing.cpp.o
ArchImpl/OR1K/libOR1KArch.so: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORBIS32_I.cpp.o
ArchImpl/OR1K/libOR1KArch.so: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KIncludedFiles.cpp.o
ArchImpl/OR1K/libOR1KArch.so: libETISS.so
ArchImpl/OR1K/libOR1KArch.so: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/build.make
ArchImpl/OR1K/libOR1KArch.so: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library libOR1KArch.so"
	cd ArchImpl/OR1K && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OR1KArch.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/build: ArchImpl/OR1K/libOR1KArch.so
.PHONY : ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/build

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/requires: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KGDBCore.cpp.o.requires
ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/requires: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORFPX32.cpp.o.requires
ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/requires: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORBIS32_II.cpp.o.requires
ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/requires: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KArch.cpp.o.requires
ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/requires: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1K_Helper.cpp.o.requires
ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/requires: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KTimer.cpp.o.requires
ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/requires: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KArch_fpu.cpp.o.requires
ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/requires: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1200Timing.cpp.o.requires
ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/requires: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/ORBIS32_I.cpp.o.requires
ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/requires: ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/OR1KIncludedFiles.cpp.o.requires
.PHONY : ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/requires

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/clean:
	cd ArchImpl/OR1K && $(CMAKE_COMMAND) -P CMakeFiles/OR1KArch.dir/cmake_clean.cmake
.PHONY : ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/clean

ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/depend: ArchImpl/OR1K/OR1KIncludedFiles.h
ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/depend: ArchImpl/OR1K/OR1KIncludedFiles.cpp
	cd /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0 /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/ArchImpl/OR1K /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/ArchImpl/OR1K /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ArchImpl/OR1K/CMakeFiles/OR1KArch.dir/depend
