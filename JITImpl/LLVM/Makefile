
BUILD_DIR?=build

LLVMINSTALLED?=0

ifeq ($(LLVMINSTALLED),0)
	LLVMTOOLDIR?=/usr/local/research/projects/SystemDesign/tools/llvm
	LLVMVERSION?=3.4.2
	LLVMPATH=$(LLVMTOOLDIR)/$(LLVMVERSION)
	LLVMPATH_BIN=$(LLVMPATH)/bin
	LLVMPATH_LIB=$(LLVMPATH)/lib
	LLVMPATH_INCLUDE=$(LLVMPATH)/include
	CLANG_HEADERS=$(realpath $(LLVMPATH_LIB)/clang/$(LLVMVERSION)/include)
else
	LLVMVERSION?=$(shell llvm-config --version)
	LLVMPATH_BIN=$(shell llvm-config --bindir)
	LLVMPATH_LIB=$(shell llvm-config --libdir)
	LLVMPATH_INCLUDE=$(shell llvm-config --includedir)
	CLANG_HEADERS=$(realpath $(LLVMPATH_LIB)/clang/$(LLVMVERSION)/include)
endif

DEBUG?=1
NATIVE?=0

ifeq ($(DEBUG),0)
	DBGPARAM=
	ifeq ($(NATIVE),0)
		OPTLEVEL?=-O3
	else
		OPTLEVEL?=-O3 -mtune=native -march=native 
	endif
else
	DBGPARAM=-g
	OPTLEVEL?=-O0
endif

FORCED_CFLAGS= $(DBGPARAM) $(OPTLEVEL) 

ETISS_INCLUDE=../../include
ETISS_INCLUDE_C=../../include_c
ETISS_LIBRARY=../../

LLVMFLAGS=$($(LLVMPATH_BIN)/llvm-config --cxxflags)

STATICLIBS__=$(shell $(LLVMPATH_BIN)/llvm-config --libfiles)
STATICLIBS_=$(STATICLIBS__:%.so= )
LLVMLIBFOLDER=$(shell $(LLVMPATH_BIN)/llvm-config --libdir)
STATICLIBS_+=$(wildcard $(LLVMLIBFOLDER)/*.a)
STATICLIBS=$(STATICLIBS_)

all: $(BUILD_DIR)/libLLVMJIT.so

CLANG_INCLUDED_HEADERS_ += $(wildcard $(realpath $(LLVMPATH_LIB)/clang/$(LLVMVERSION)/include)/*.h)
CLANG_INCLUDED_HEADERS_ += $(wildcard $(realpath $(LLVMPATH_LIB)/clang/$(LLVMVERSION)/include)/*/*.h)
CLANG_INCLUDED_HEADERS_ += $(wildcard $(realpath $(LLVMPATH_LIB)/clang/$(LLVMVERSION)/include)/*/*/*.h)
CLANG_INCLUDED_HEADERS_ += $(wildcard $(realpath $(LLVMPATH_LIB)/clang/$(LLVMVERSION)/include)/*/*/*/*.h)
CLANG_INCLUDED_HEADERS_ += $(wildcard $(realpath $(LLVMPATH_LIB)/clang/$(LLVMVERSION)/include)/*/*/*/*/*.h)
CLANG_INCLUDED_HEADERS_ += $(wildcard $(realpath $(LLVMPATH_LIB)/clang/$(LLVMVERSION)/include)/*/*/*/*/*/*.h)
CLANG_INCLUDED_HEADERS_ += $(wildcard $(realpath $(LLVMPATH_LIB)/clang/$(LLVMVERSION)/include)/*/*/*/*/*/*/*.h)

toCMAKEList=$(subst $(eval) ,;,$1)

CLANG_INCLUDED_HEADERS__=$(foreach header,$(CLANG_INCLUDED_HEADERS_),"$(header:$(realpath $(LLVMPATH_LIB))/%=%),$(header)")
CLANG_INCLUDED_HEADERS=$(subst $(eval) ,;,$(CLANG_INCLUDED_HEADERS__))

$(BUILD_DIR)/src/CLangIncludedFiles.cpp:
	mkdir -p $(BUILD_DIR)/include
	mkdir -p $(BUILD_DIR)/src
	$(BUILD_DIR)/../../IncludedFilesGenerator -fl "$(CLANG_INCLUDED_HEADERS)" -ns clang::storedfiles -h $(BUILD_DIR)/include/CLangIncludedFiles.h -cpp $(BUILD_DIR)/src/CLangIncludedFiles.cpp -hi CLangIncludedFiles.h

$(BUILD_DIR)/CLangIncludedFiles.o : $(BUILD_DIR)/src/CLangIncludedFiles.cpp
	gcc -DCLANG_HEADERS=$(CLANG_HEADERS) -DCLANG_FALLBACK_PATH=$(realpath $(LLVMPATH_LIB))/ -DCLANG_HEADER_REALTIVE_PATH=clang/$(LLVMVERSION)/include -std=c++0x -c -Wall -Werror -fPIC -Iinclude -I$(BUILD_DIR)/include -MMD $(INCLUDE_ARGS) -I$(ETISS_INCLUDE) -I$(ETISS_INCLUDE_C) -I$(LLVMPATH_INCLUDE) $(shell $(LLVMPATH_BIN)/llvm-config --cxxflags) -DDEBUG=$(DEBUG) $(FORCED_CFLAGS) -o $@ $< 

#python ../../includeHeaderCodegen.py -s $(realpath $(LLVMPATH_LIB)) $(realpath $(LLVMPATH_LIB)/clang/$(LLVMVERSION)/include) -mkd $(BUILD_DIR)/IncludedFiles.cpp.d src/IncludedFiles.cpp -ns clang -ns storedfiles -l count -n names -d data -ch include/IncludedFiles.h IncludedFiles.h src/IncludedFiles.cpp

.PHONY: llvmdownload
llvmdownload:
	mkdir -p llvm
	svn co http://llvm.org/svn/llvm-project/llvm/tags/RELEASE_34/final/ llvm
	svn co http://llvm.org/svn/llvm-project/cfe/tags/RELEASE_34/final/ llvm/tools/clang
	mkdir -p llvm/projects
	svn co http://llvm.org/svn/llvm-project/compiler-rt/tags/RELEASE_34/final/ llvm/projects/compiler-rt

.PHONY: install
install: llvmdownload
	cd $(BUILD_DIR) && ./configure --enable-languages=c
	cd $(BUILD_DIR) && make
	
TARGETFILES=$(wildcard src/*.cpp)
OBJFILES=$(TARGETFILES:src/%.cpp=$(BUILD_DIR)/%.o)

$(BUILD_DIR)/%.o: src/%.cpp
	gcc -DCLANG_HEADERS=$(CLANG_HEADERS) -DCLANG_FALLBACK_PATH=$(realpath $(LLVMPATH_LIB))/ -DCLANG_HEADER_REALTIVE_PATH=clang/$(LLVMVERSION)/include -std=c++0x -c -Wall -Werror -fPIC -Iinclude -I$(BUILD_DIR)/include -MMD $(INCLUDE_ARGS) -I$(ETISS_INCLUDE) -I$(ETISS_INCLUDE_C) -I$(LLVMPATH_INCLUDE) $(shell $(LLVMPATH_BIN)/llvm-config --cxxflags) -DDEBUG=$(DEBUG) $(FORCED_CFLAGS) -o $@ $< 

#-include $(BUILD_DIR)/*.d

$(BUILD_DIR)/libLLVMJIT.so: LLVMJITLIB.cpp $(BUILD_DIR)/CLangIncludedFiles.o $(OBJFILES)
	gcc -DCLANG_HEADERS=$(CLANG_HEADERS) -std=c++0x -shared -Iinclude -I$(BUILD_DIR)/include $(INCLUDE_ARGS) -I$(ETISS_INCLUDE) -I$(ETISS_INCLUDE_C) -I$(LLVMPATH_INCLUDE) $(BUILD_DIR)/CLangIncludedFiles.o -L$(LLVMPATH_LIB) $(shell $(LLVMPATH_BIN)/llvm-config --cxxflags) -DDEBUG=$(DEBUG) $(FORCED_CFLAGS) -L../.. LLVMJITLIB.cpp -o $(BUILD_DIR)/libLLVMJIT.so $(OBJFILES) $(STATICLIBS) $(STATICLIBS) $(shell $(LLVMPATH_BIN)/llvm-config --ldflags)  -Wl,--version-script=LLVMJITLIBAPI.cfg

main: $(OBJFILES)
	g++ -std=c++0x $(OPTLEVEL) $(DBGPARAM) -Iinclude -I$(BUILD_DIR)/include -I$(ETISS_INCLUDE) $(INCLUDE_ARGS) -I$(ETISS_INCLUDE_C) -I$(LLVMPATH_INCLUDE)  $(shell $(LLVMPATH_BIN)/llvm-config --cxxflags) -Iinclude  $(FORCED_CFLAGS) -L../.. main.cpp  -o $(OBJFILES) $(STATICLIBS) $(STATICLIBS) -lETISS  $(shell $(LLVMPATH_BIN)/llvm-config --ldflags)

clean:
	rm -f ./libLLVMJIT.so
	rm -f ./main
	rm -f $(BUILD_DIR)/src/CLangIncludedFiles.cpp
	rm -f $(BUILD_DIR)/include/CLangIncludedFiles.h
	
