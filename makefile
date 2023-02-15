TOOLCHAIN = arm-none-eabi-
CC = $(TOOLCHAIN)gcc
LD = $(CC)
OBJCOPY = $(TOOLCHAIN)objcopy
OBJDUMP = $(TOOLCHAIN)objdump

CC_FLAGS = -std=c18 -c -mthumb -mcpu=cortex-m3 -Wall -Wpedantic -Wextra -fdiagnostics-color=never -Og -ggdb
LINKER_SCRIPT = arm_gcc.ld
LD_FLAGS = -T$(LINKER_SCRIPT) -nostartfiles --specs=nosys.specs -fdiagnostics-color=never 

all: prog.elf prog.bin debug

prog.bin: prog.elf
	$(OBJCOPY) -O binary "output/$<" "output/$@"

prog.elf: main.o startup.o
	$(LD) $^ $(LD_FLAGS) -o "output/$@"
	
main.o:
startup.o:

%.o: %.c
	$(CC) $< $(CC_FLAGS) -o $@ 
	
debug: main.o startup.o prog.elf
	$(OBJDUMP) "output/prog.elf" --section-headers > "debug/prog_headers.txt"
	$(OBJDUMP) "output/prog.elf" --disassemble-all > "debug/prog_disassembly.txt"
	$(OBJDUMP) main.o --section-headers > "debug/main_headers.txt"
	$(OBJDUMP) startup.o --section-headers > "debug/startup_headers.txt"
	
clean: 
	# if on using CMD uncomment:
	# -del -fR *.o	
	rm -rf *.o
	rm -rf debug/*
	rm -rf output/*
	



