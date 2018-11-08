#include "init.h"
#include "interrupts.h"
#include "segment.h"

void arch_initialize(void) {
	gdt_init();
	interrupts_init();
}
