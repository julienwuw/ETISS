
CC=gcc
CFLAGS=-std=c++0x -O3 -c -Wall -fPIC -g -MMD 

BaseFolder=../..


all : libGCCJIT.so

-include *.d

GCCJIT.o : GCCJIT.cpp
	$(CC) $(CFLAGS) -I$(BaseFolder)/include -I$(BaseFolder)/include_c GCCJIT.cpp
	
libGCCJIT.so : GCCJIT.o GCCJITLIB.cpp
	$(CC) -std=c++0x -shared -g -fPIC -MMD -L$(BaseFolder) -I$(BaseFolder)/include -I$(BaseFolder)/include_c GCCJITLIB.cpp -o libGCCJIT.so GCCJIT.o -Wl,--version-script=GCCJITLIBAPI.cfg
	
clean :
	rm -f *o
	rm -f libGCCJIT.so
