#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "kernel.h"
#include "../libc/string.h"

void main() {
  isr_install();
	irq_install();

	kprint("Type stuff: goes through kernel\n"
				 "Type END to halt CPU\n> ");
}

void user_input(char *input) {
	if(str_cmp(input, "END") == 0) {
		kprint("Stopping CPU.\n");
		asm volatile("hlt");
	}

	kprint("You said: ");
	kprint(input);
	kprint("\n> ");
}
