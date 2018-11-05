//#include <arch/init.h>
//#include <arch/i386/interrupts.h>

void arch_initialize(void) {
  // gdt_init()
  interrupts_init();
}
