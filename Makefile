C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c libc/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h libc/*.h)

# Convert *.c filename to *.o
OBJ = ${C_SOURCES:.c=.o cpu/interrupt.o}

CC = ~/opt/cross/bin/i686-elf-gcc
LD = ~/opt/cross/bin/i686-elf-ld
GDB = ~/opt/cross/bin/i686-elf-gdb

CFLAGS = -g -Wall -Wextra

# Disk image the computer loads: compiled bootsector + kernel
os-image.bin: boot/boot_sect.bin kernel.bin
	cat $^ > os-image.bin

# Build binary of kernel from kernel_entry.o and kernel.o object files
kernel.bin: boot/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.elf: boot/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^

debug: os-image.bin kernel.elf
	qemu-system-i386 -s -fda os-image.bin -d guest_errors,in &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

# Disassemble kernel for debugging
kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@

# Default build target
all: os-image.bin

# Run QEMU test
run: all
	qemu-system-i386 -fda os-image.bin

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

# Clear generated files
clean:
	rm -rf *.bin *.dis *.o *.elf
	rm -rf kernel/*.o boot/*.bin boot/*.o drivers/*.o cpu/*.o libc/*.o

