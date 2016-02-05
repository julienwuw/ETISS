
TOOLBIN=/usr/local/research/projects/SystemDesign/tools/openrisc/gcc-or1k-elf-4.8.1-x86_64/bin

SOFTFLOAT?=0

ifeq ($(SOFTFLOAT),1)
	FLOATTYPE= -mhard-float
else 
	FLOATTYPE= -msoft-float 
endif


OR32CC=PATH=$(TOOLBIN):$(PATH) LD_LIBRARY_PATH=$(TOOLBIN)/../x86_64-unknown-linux-gnu/or1k-elf/lib:$(LD_LIBRARY_PATH) $(TOOLBIN)/or1k-elf-gcc -std=c99 $(FLOATTYPE) 
OR32OBJCPY=PATH=$(TOOLBIN):$(PATH) LD_LIBRARY_PATH=$(TOOLBIN)/../x86_64-unknown-linux-gnu/or1k-elf/lib:$(LD_LIBRARY_PATH) $(TOOLBIN)/or1k-elf-objcopy
OR32OBJDMP=PATH=$(TOOLBIN):$(PATH) LD_LIBRARY_PATH=$(TOOLBIN)/../x86_64-unknown-linux-gnu/or1k-elf/lib:$(LD_LIBRARY_PATH) $(TOOLBIN)/or1k-elf-objdump
OR32RDELF=PATH=$(TOOLBIN):$(PATH) LD_LIBRARY_PATH=$(TOOLBIN)/../x86_64-unknown-linux-gnu/or1k-elf/lib:$(LD_LIBRARY_PATH) $(TOOLBIN)/or1k-elf-readelf
OR32GDB=PATH=$(TOOLBIN):$(PATH) LD_LIBRARY_PATH=$(TOOLBIN)/../x86_64-unknown-linux-gnu/or1k-elf/lib:$(LD_LIBRARY_PATH) $(TOOLBIN)/or1k-elf-gdb


DEBUG?=1

ifeq ($(DEBUG),0)
	DBGPARAM =
	OPTLEVEL?=-O3
else
	DBGPARAM =-g
	OPTLEVEL?=-O3
endif

CFLAGS = $(DBGPARAM) $(OPTLEVEL)

all: code.bin code.hex code.elf code.txt code.disasm

bogomips.o : bogomips.c
	$(OR32CC) -g -O0 -c bogomips.c
	
testbench.o : testbench.c
	$(OR32CC) -g -O0 -c testbench.c

print.o : print.S
	$(OR32CC) $(CFLAGS) -c print.S

print_.o : print.c
	$(OR32CC) $(CFLAGS) -o print_.o -c print.c 

board.o: board.S
	$(OR32CC) $(CFLAGS) -c board.S

code.elf: board.o print.o print_.o bogomips.o testbench.o main.c
	$(OR32CC) $(CFLAGS) -T ./link.ld main.c -o code.elf board.o print.o print_.o bogomips.o testbench.o
	
htest: htest.c
	gcc -std=c99 -g -O0 htest.c -o htest

code.bin: code.elf
	$(OR32OBJCPY) ./code.elf --output-target=binary ./code.bin

code.hex: code.bin
	hexdump ./code.bin > code.hex

code.disasm : code.elf
	$(OR32OBJDMP) -D ./code.elf > code.disasm

code.txt: code.bin
	$(OR32RDELF) -a code.elf > code.txt

readelf: code.txt

clean:
	rm -f *.o
	rm -f code.*

gdb:
	$(OR32GDB) --args ./code.elf
