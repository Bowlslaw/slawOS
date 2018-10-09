# Generate lists of sources using wildcards
C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)

# TODO: Make sources dep on all header files

# Convert *.c filename to *.o
OBJ = ${C_SOURCES:.c=.o}

CC = ~/opt/cross/bin/i686-elf-gcc
LD = ~/opt/cross/bin/i686-elf-ld
GDB = ~/opt/cross/bin/i686-elf-gdb

CFLAGS = -g

# Default build target
all: os-image.bin

# Run QEMU test
run: all
	qemu-system-i386 -fda os-image.bin

# Disk image the computer loads: compiled bootsector + kernel
os-image.bin: boot/boot_sect.bin kernel.bin
	cat $^ > os-image.bin

# Build binary of kernel from kernel_entry.o and kernel.o object files
kernel.bin: boot/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^ --oformat binary

# Generic rule for compiling C code to object file
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

# Assemble kernel_entry
%.o: %.asm
	nasm $< -f elf64 -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

# Clear generated files
clean:
	rm -rf *.bin *.dis *.o
	rm -rf kernel/*.o boot/*.bin

# Disassemble kernel for debugging
kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@
