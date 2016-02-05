DEBUG?=1

CC=gcc

ifeq ($(DEBUG),0)
	DBGPARAM =
	OPTLEVEL?=-Ofast
else
	DBGPARAM =-g
	OPTLEVEL?=
endif

BaseFolder=../..

CFLAGS=-std=c++0x -c -DETISS_LIB_SHARED=1 -MMD -Wall -Werror -fPIC $(OPTLEVEL) $(DBGPARAM) -DDEBUG=$(DEBUG) -I$(BaseFolder)/include -I$(BaseFolder)/include_c


all : libOR1KArch.so

IncludedFiles.cpp : OR1K.h
	mkdir -p ./include_c/Arch/OR1K
	cp ./OR1K.h ./include_c/Arch/OR1K/OR1K.h
	python ../../includeHeaderCodegen.py -f ./ ./include_c/Arch/OR1K/OR1K.h -ns or1k -ns storedfiles -l count -n names -d data -ch IncludedFiles.h IncludedFiles.h IncludedFiles.cpp
	rm -rf ./include_c
	
IncludedFiles.o: IncludedFiles.cpp
	$(CC) $(CFLAGS) IncludedFiles.cpp

OR1KArch.o : OR1KArch.cpp
	$(CC) $(CFLAGS) OR1KArch.cpp

OR1KArch_fpu.o : OR1KArch_fpu.cpp
	$(CC) $(CFLAGS) OR1KArch_fpu.cpp

OR1KGDBCore.o : OR1KGDBCore.cpp
	$(CC) $(CFLAGS) OR1KGDBCore.cpp

OR1KTimer.o : OR1KTimer.cpp
	$(CC) $(CFLAGS) OR1KTimer.cpp

ORBIS32_I.o: ORBIS32_I.cpp
	$(CC) $(CFLAGS) ORBIS32_I.cpp
	
ORBIS32_II.o: ORBIS32_II.cpp
	$(CC) $(CFLAGS) ORBIS32_II.cpp
	
ORFPX32.o : ORFPX32.cpp
	$(CC) $(CFLAGS) ORFPX32.cpp
	
OR1200Timing.o : OR1200Timing.cpp
	$(CC) $(CFLAGS) OR1200Timing.cpp
	
-include ./*.d

libOR1KArch.so : IncludedFiles.o OR1KArch.o OR1KGDBCore.o OR1KTimer.o OR1KArch_fpu.o ORBIS32_I.o ORBIS32_II.o ORFPX32.o OR1200Timing.o
	$(CC) -std=c++0x -shared -g -L$(BaseFolder) -lETISS -dl -o libOR1KArch.so OR1KArch.o OR1KArch_fpu.o OR1KGDBCore.o OR1KTimer.o IncludedFiles.o ORBIS32_I.o ORBIS32_II.o ORFPX32.o OR1200Timing.o  -Wl,--version-script=OR1KLIBAPI.cfg

clean :
	rm -f *o
	rm -f libOR1KArch.so
	rm -f IncludedFiles.cpp IncludedFiles.h





