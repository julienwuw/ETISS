#use to create timesoftfloat test program

OBJ = .o
EXE = .exe
INCLUDES = -I../../include -I../../include_c
COMPILE_C = gcc -c -o $@ $(INCLUDES) -iquote -O2
LINK = gcc -o $@

ALL: timesoftfloat$(EXE)

softfloat$(OBJ): softfloat.cpp
	$(COMPILE_C) softfloat.cpp

timesoftfloat$(OBJ): timesoftfloat.c
	$(COMPILE_C) timesoftfloat.c

timesoftfloat$(EXE): softfloat$(OBJ) timesoftfloat$(OBJ)
	$(LINK) softfloat$(OBJ) timesoftfloat$(OBJ)
	rm -f *.o

