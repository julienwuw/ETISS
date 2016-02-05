#make directories if not present
$(shell mkdir -p ./build)

CC = gcc

#######################################
# adapt these paths if needed

#defines ETISS_LIBRARIES, ETISS_INCLUDES and ETISS_LIBPATH
include /nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/installed/include/ETISS.mk

SystemC_LIBRARIES=  /usr/local/research/projects/SystemDesign/tools/systemc/systemc-2.3.0/lib-linux64/libsystemc.a -lpthread -ldl 
SystemC_INCLUDE_DIRS= -I/usr/local/research/projects/SystemDesign/tools/systemc/systemc-2.3.0/include
######################################

CFLAGS = -O0 -g -std=c++0x -fpermissive ${ETISS_INCLUDES} ${SystemC_INCLUDE_DIRS} -Icpu_systemc_interface_lib -Icpu_systemc_etiss_lib -DSC_INCLUDE_DYNAMIC_PROCESSES -MMD




TARGETFILES=$(wildcard *.cpp)
TARGETFILESCLEAN=$(filter-out main.cpp,$(TARGETFILES))
OBJFILES:=$(TARGETFILESCLEAN:%.cpp=build/%.o)



all: main

build/SimpleMemory.o: SimpleMemory.cpp
	$(CC) -c $(CFLAGS) -o $@ $<
	
build/cpu_systemcinterface_sc.o: cpu_systemc_interface_lib/cpu_systemcinterface_sc.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

build/cpu_etiss_sc.o: cpu_systemc_etiss_lib/cpu_etiss_sc.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

-include build/*.d

main: main.cpp build/cpu_etiss_sc.o build/cpu_systemcinterface_sc.o build/SimpleMemory.o
	g++ $(CFLAGS) main.cpp build/cpu_etiss_sc.o build/cpu_systemcinterface_sc.o build/SimpleMemory.o -o main  $(SystemC_LIBRARIES) $(ETISS_LIBRARIES)

.PHONY: run
run:  	main
	LD_LIBRARY_PATH=$(ETISS_LIBPATH):$LD_LIBRARY_PATH ./main

.PHONY: gdb
gdb:	main
	LD_LIBRARY_PATH=$(ETISS_LIBPATH):$LD_LIBRARY_PATH gdb --args ./main

-PHONY: clean
clean:
	rm -R -f ./build/*
	rm -f main

