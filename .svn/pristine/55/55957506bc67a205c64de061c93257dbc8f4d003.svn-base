#################################################################################################
#
#	Copyright (c) 2014 Institute for Electronic Design Automation, TU Munich
#
#	The above copyright notice and this permission notice shall be included in
#	all copies or substantial portions of the Software.
#
#	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
#	THE SOFTWARE.
#
#	author Marc Greim <marc.greim@mytum.de>
#
#	date June 24, 2014
#
#	version 0.4

###############################################################################################

#make command
MAKE=make

#flags that are passed to the main executable (targets: run,profile)
RUNFLAGS?=

# 0 if release build (may require clean/cleanall to take efect)
DEBUG?=1

# 0 if the build is intended to run on different pcs. 1 for full use of the cpu functions this has been compiled on (enables -mtune=native and -march=native)
NATIVE?=0

# if not 0 the the first error will terminate compilation (Abort After Error)
AAE?=0

# compiler collection
CC?=gcc

#enable use of python
ETISS_USE_PYTHON?=0

AGGRESSIVEOPT?=0

ifneq ($(AGGRESSIVEOPT),0)
	AGGRESSIVEOPTLEVEL= -flto -funroll-loops -mfpmath=sse
else
	AGGRESSIVEOPTLEVEL=
endif



#select flags based on debug/release configuration
ifeq ($(DEBUG),0)
	DBGPARAM= -g1
	ifeq ($(NATIVE),0)
		OPTLEVEL?=-O3 $(AGGRESSIVEOPTLEVEL)
	else
		OPTLEVEL?=-O3 -mtune=native -march=native $(AGGRESSIVEOPTLEVEL)
	endif
else
	DBGPARAM= -g3
	OPTLEVEL?= -O0 $(AGGRESSIVEOPTLEVEL)
endif



# search library projects in the respective folders to build after etiss (targets: all,libs)
OTHERLIBSDIR=$(foreach location,$(wildcard ArchImpl/*/Makefile),$(realpath $(dir $(location))))
OTHERLIBSDIR+=$(foreach location,$(wildcard JITImpl/*/Makefile),$(realpath $(dir $(location))))
OTHERLIBSDIR+=$(foreach location,$(wildcard PluginImpl/*/Makefile),$(realpath $(dir $(location))))

USERFLAGS?=
# compiler flags. change -std=c++0x to -std=c++11 as soon as possible
CFLAGS= -std=c++0x -c -Wall -Werror -fPIC $(OPTLEVEL) $(DBGPARAM) -DDEBUG=$(DEBUG) -Iinclude -Iinclude_c $(USERFLAGS)


# abort compilation after error?
ifneq ($(AAE),0)
	CFLAGS+= -Wfatal-errors
endif

# add python?
CFLAGS+= -DETISS_USE_PYTHON=$(ETISS_USE_PYTHON)
ifneq ($(ETISS_USE_PYTHON),0)
	CFLAGS+= $(shell python2-config --includes)
	PYLIBS= $(filter -L%,$(shell python2-config --ldflags)) $(filter -l%,$(shell python2-config --ldflags))
else
	PYLIBS=
endif


# contains targets to perform checks and defined some variables
include Prerequisites.mk

#default
all: $(TARGET_CHECK_BUILD) libs



# dependency to run all build checks
.PHONY: build_init
build_init: $(TARGET_CHECK_BUILD)

# dependency to run all execution checks
.PHONY: run_init
run_init: $(TARGET_CHECK_BULD)


#find source files of etiss. note: max searched folder depth in src: 4
TARGETFILES= src/IncludedFiles.cpp $(filter-out src/IncludedFiles.cpp, $(wildcard src/*.cpp) $(wildcard src/*/*.cpp) $(wildcard src/*/*/*.cpp) $(wildcard src/*/*/*/*.cpp) src/IncludedFiles.cpp )
OBJFILES=$(TARGETFILES:src/%.cpp=build/%.o)

src/IncludedFiles.cpp: build/se_check_python
	python ./includeHeaderCodegen.py -f ./ ./Printlibs.mk -s ./ ./include_c/etiss/jit -mkd ./build/IncludedFiles.cpp.d src/IncludedFiles.cpp -ns etiss -ns storedfiles -l count -n names -d data -ch include/etiss/IncludedFiles.h etiss/IncludedFiles.h src/IncludedFiles.cpp

#build source files of etiss
build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -DETISS=1 -MMD -o $@ $<

#include header dependencies of source files of etiss (for propper change detection by $make)
-include build/*.d
-include build/*/*.d
-include build/*/*/*.d
-include build/*/*/*/*.d
-include build/*/*/*/*/*.d
-include build/*/*/*/*/*/*.d

# build ETISS dynamic library
libETISS.so: $(OBJFILES)
	$(CC) -std=c++0x -fPIC $(OPTLEVEL) -g -shared -o libETISS.so $(OBJFILES) -ldl

#build ETISS static library
libETISS.a: $(OBJFILES)
	ar rcs libETISS.a $(OBJFILES)

# build main example/test file
main: libETISS.so main.cpp
	g++ -std=c++0x $(OPTLEVEL) $(DBGPARAM) -DDEBUG=$(DEBUG) -Iinclude -Iinclude_c main.cpp -L./  -o main -lETISS -ldl -lpthread $(PYLIBS)

# build the test.cpp file for simple test with etiss
test: libETISS.so test.cpp
	g++ -std=c++0x $(OPTLEVEL) $(DBGPARAM) -DDEBUG=$(DEBUG) -Iinclude -Iinclude_c test.cpp -L./  -o test -lETISS -ldl -lpthread $(PYLIBS)

# build ETISS dynamic library and sub projects
libs: libETISS.so libETISS.a
	-$(foreach location,$(OTHERLIBSDIR), $(MAKE) -C $(location) && ) true
	-cd SW && make DEBUG=$(DEBUG)
	-cd systemc && make DEBUG=$(DEBUG)

# execute the main example/test file
.PHONY: run
run: main
	LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH ./main $(RUNFLAGS)

# execute test file
.PHONY: run
trun: test
	LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH ./test $(RUNFLAGS)

# execute the main example/test file with callgrind
.PHONY: profile
profile: main
	LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH valgrind --tool=callgrind -v ./main $(RUNFLAGS)

# execute the main example/test file with cachegrind
.PHONY: cprofile
cprofile: main
	LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH valgrind --tool=cachegrind -v ./main $(RUNFLAGS)

# execute the main example/test file with memcheck
.PHONY: memcheck
memcheck: main
	LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH valgrind --tool=memcheck --track-origins=yes --leak-check=full --num-callers=50 --suppressions=./cfg/valgrind-python.supp --log-file="main.memcheck"   ./main $(RUNFLAGS)

# execute test file with memcheck
.PHONY: tmemcheck
tmemcheck: test
	LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH valgrind --tool=memcheck --track-origins=yes --leak-check=full --num-callers=50 --suppressions=./cfg/valgrind-python.supp valgrind --log-file="test.memcheck"   ./test $(RUNFLAGS)


# execute the main example/test file with memcheck (fast)
.PHONY: memcheckf
memcheckf: main
	LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH valgrind --tool=memcheck --suppressions=./cfg/valgrind-python.supp   ./main $(RUNFLAGS)



#execute the main example/test file with gdb
.PHONY: gdb
gdb: main
	LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH gdb --args ./main

#generate documenation
.PHONY: doc
doc:
	doxygen ./cfg/Doxyfile

#generate pdf documenation
.PHONY: pdfdoc
pdfdoc: doc
	cd doc/latex/ && make pdf && cp refman.pdf ../documentation.pdf

# view documentation in firefox
.PHONY: vdoc
vdoc:
	firefox ./doc/html/index.html

# clean etiss files
.PHONY: clean
clean :
	rm -f callgrind.out*
	rm -rf -- build
	rm -f main
	rm -f libETISS.so
	rm -f etiss/IncludedFiles.h src/IncludedFiles.cpp

# clean etiss files and subprojects
.PHONY: cleanall
cleanall: clean
	-$(foreach location,$(OTHERLIBSDIR), $(MAKE) -C $(location) clean && ) true


INSTALL_TARGET?=./install/

.PHONY: install
install: libETISS.so
	make -f Install.mk INSTALL_TARGET=$(INSTALL_TARGET) DEBUG=$(DEBUG) OPTLEVEL=$(OPTLEVEL)


.PHONY: project
project:
	cd SW/ && make code.bin
	python createProject.py

cpplint: script/etiss/cpplint.py
	python script/etiss/cpplint.py ./src/ETISS.cpp

#uses clangFormat to format all etiss header files and sourcefiles excluding files locates in the ArchImpl,JITImpl,PluginImpl,systemc folder
format:
	PATH=~/.llvm/bin/:$(PATH) clang-format -i -style=llvm ./src/ETISS.cpp

build/fault_xml_module_defs.h:
	touch build/fault_xml_module_defs.h
	@echo -e "#ifndef NO_ETISS\n#define NO_ETISS\n#endif\n\n" >> build/fault_xml_module_defs.h

build/fault_xml_module/fault/%.h: include/etiss/fault/%.h build/fault_xml_module_defs.h
	@mkdir -p $(dir $@)
	rm -f $@
	cat build/fault_xml_module_defs.h $< > $@
build/fault_xml_module/fault/%.hpp: include/etiss/fault/%.hpp build/fault_xml_module_defs.h
	@mkdir -p $(dir $@)
	rm -f $@
	cat build/fault_xml_module_defs.h $< > $@
build/fault_xml_module/fault/%.cpp: src/fault/%.cpp
	@mkdir -p $(dir $@)
	rm -f $@
	cat build/fault_xml_module_defs.h $< > $@

FAULT_XML_MODULE_HEADERS=$(wildcard include/etiss/fault/*.h) $(wildcard include/etiss/fault/*.hpp) $(wildcard include/etiss/fault/*/*.h) $(wildcard include/etiss/fault/*/*.hpp)
FAULT_XML_MODULE_SOURCES=$(wildcard src/fault/*.cpp) $(wildcard src/fault/*/*.cpp)
FAULT_XML_MODULE_MHEADERS=$(FAULT_XML_MODULE_HEADERS:include/etiss/fault/%=build/fault_xml_module/fault/%)
FAULT_XML_MODULE_MSOURCES=$(FAULT_XML_MODULE_SOURCES:src/fault/%=build/fault_xml_module/fault/%)
#creates a zip file that contains all neccessary files for xml fault definition and parsing. that packet can be used standalone
fault_xml_module.zip: $(FAULT_XML_MODULE_MHEADERS) $(FAULT_XML_MODULE_MSOURCES) src/fault_xml_module.mk
	@mkdir -p build/fault_xml_module/fault
	rm -f build/fault_xml_module/fault/TODO.cpp
	@echo -e "#include \"fault/Injector.h\"\n\nnamespace etiss {\nnamespace fault {\n Injector::ptr Injector::get(const std::string & path){\n\n#error TODO: Implement static get method\n\n} \n}\n}\n" > build/fault_xml_module/fault/TODO.cpp
	cp src/fault_xml_module.mk build/fault_xml_module/
	rm -f build/fault_xml_module/fault_xml_module.zip
	cd build/fault_xml_module/ && zip -r fault_xml_module.zip ./* -x "fault_/*"
	cp build/fault_xml_module/fault_xml_module.zip ./
















