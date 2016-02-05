DEBUG?=0

CC=gcc

ifeq ($(DEBUG),0)
	DBGPARAM= -g1
	OPTLEVEL= -O2 
else
	DBGPARAM= -g1 
	OPTLEVEL= -O0 
endif

ETISS_FOLDER=../..

CFLAGS=-std=c++0x -c -MMD -Wall -Werror -fPIC $(OPTLEVEL) $(DBGPARAM) -DDEBUG=$(DEBUG) -I$(ETISS_FOLDER)/include -I$(ETISS_FOLDER)/include_c


all : libTCCJIT.so


tcc-0.9.26:
	wget -O tcc-0.9.26.tar.bz2 http://download.savannah.gnu.org/releases/tinycc/tcc-0.9.26.tar.bz2
	tar -jxvf tcc-0.9.26.tar.bz2
	rm tcc-0.9.26.tar.bz2

tcc: tcc-0.9.26
	ln -s tcc-0.9.26 tcc

tcc/build/libtcc.a: tcc
	cd tcc && mkdir -p build
	cd tcc/build && ../configure --extra-cflags=-fPIC && make
	
./tcc/build/libtcc1.a : tcc/build/libtcc.a

IncludedFiles.cpp : tcc tcc/build/libtcc1.a
	python ../../includeHeaderCodegen.py -s ./ ./tcc/include -f ./ ./tcc/build/libtcc1.a -mkd ./IncludedFiles.cpp.d IncludedFiles.cpp -ns tcc -ns storedfiles -l count -n names -d data -ch IncludedFiles.h IncludedFiles.h IncludedFiles.cpp

IncludedFiles.o: tcc IncludedFiles.cpp 
	$(CC) $(CFLAGS) IncludedFiles.cpp

TCCJIT.o : tcc TCCJIT.cpp
	$(CC) $(CFLAGS) TCCJIT.cpp

TCCJITLib.o: TCCJITLib.cpp
	$(CC) $(CFLAGS) TCCJITLib.cpp

-include ./*.d

libTCCJIT.so : IncludedFiles.o TCCJIT.o TCCJITLib.o tcc/build/libtcc.a
	$(CC) -std=c++0x -shared -g -o libTCCJIT.so TCCJIT.o TCCJITLib.o IncludedFiles.o tcc/build/libtcc.a

clean :
	rm -f *.o
	rm -f *.d
	rm -f libTCCJIT.so
	rm -f IncludedFiles.cpp IncludedFiles.h

