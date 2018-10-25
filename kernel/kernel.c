#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "kernel.h"
#include "../libc/string.h"
#include "../libc/mem.h"

void kmain() {
  isr_install();
	irq_install();

	kprint("Type stuff: goes through kernel\n"
				 "Type END to halt CPU\n> ");
}

void user_input(char *input) {
	if(str_cmp(input, "END") == 0) {
		kprint("Stopping CPU.\n");
		asm volatile("hlt");
	} else if(str_cmp(input, "PAGE") == 0) {
		  uint32_t paddr;
			uint32_t page = kmalloc(1000, 1, &paddr);
			char pagestr[16] = "";
			hex2ascii(page, pagestr);
			char pstr[16] = "";
			hex2ascii(paddr, pstr);
			kprint("Page: ");
			kprint(pagestr);
			kprint(", physical address: ");
			kprint(pstr);
			kprint("\n");
	}
	kprint("You said: ");
	kprint(input);
	kprint("\n> ");
}
