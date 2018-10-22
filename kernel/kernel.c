#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "utils.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "../cpu/timer.h"

void main() {
  isr_install();
	asm volatile("sti");
	//init_timer(50);

	init_keyboard();
}
