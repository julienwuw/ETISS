#make directories if not present
$(shell mkdir -p ./build)

CC = gcc
CFLAGS = -std=c++0x -fpermissive -I

ifeq ($(DEBUG),0)
	DBGPARAM =
	OPTLEVEL?=-O2
else
	DBGPARAM =-g
	OPTLEVEL?=
endif

CFLAGS+= $(OPTLEVEL) $(DBGPARAM) 


#######################################
# adapt these paths if needed
SYSTEMC_HOME=/usr/local/research/projects/SystemDesign/tools/systemc/systemc-2.3.0
TLM_HOME=/usr/local/research/projects/SystemDesign/tools/systemc/TLM-2009-07-15
SYSTEMC_LIBS= -lstdc++ -lm  -lpthread 
TARGET_ARCH=linux64
######################################

SYSTEMC_FLAGS=${CFLAGS} -DSC_INCLUDE_DYNAMIC_PROCESSES -I${SYSTEMC_HOME}/include -L${SYSTEMC_HOME}/lib-${TARGET_ARCH} -I${TLM_HOME}/include/tlm -I../include -I../include_c


TARGETFILES=$(wildcard *.cpp)
TARGETFILESCLEAN=$(filter-out main.cpp,$(TARGETFILES))
OBJFILES:=$(TARGETFILESCLEAN:%.cpp=build/%.o)



all: main

build/%.o: %.cpp
	$(CC) -c $(SYSTEMC_FLAGS)  -MMD -o $@ $<

-include build/*.d

../libETISS.so:
	cd ../ && make

main: $(OBJFILES) main.cpp ../libETISS.so
	g++ $(SYSTEMC_FLAGS) main.cpp -L../ -o main  $(OBJFILES) ${SYSTEMC_HOME}/lib-${TARGET_ARCH}/libsystemc.a -ldl -lETISS ${SYSTEMC_LIBS} $(filter -L%,$(shell python2-config --ldflags)) $(filter -l%,$(shell python2-config --ldflags))

.PHONY: run
run:  	main
	LD_LIBRARY_PATH=../:${SYSTEMC_HOME}/lib-${TARGET_ARCH}:$LD_LIBRARY_PATH ./main

.PHONY: gdb
gdb:	main
	LD_LIBRARY_PATH=../:${SYSTEMC_HOME}/lib-${TARGET_ARCH}:$LD_LIBRARY_PATH gdb --args ./main

-PHONY: clean
clean:
	rm -R -f ./build/*
	rm -f main
