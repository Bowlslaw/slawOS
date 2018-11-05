#include "init.h"
#include "interrupts.h"

void arch_initialize(void) {
  gdt_init();
  interrupts_init();
}
