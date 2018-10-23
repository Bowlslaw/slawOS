#include "timer.h"
#include "isr.h"
#include "io.h"
#include "../libc/function.h"
#include <stdint.h>

#define HERTZ 1193180

uint32_t tick = 0;

static void timer_callback(registers_t *regs) {
	tick++;
	UNUSED(regs);
	/* testing code
	kprint("Tick: ");

	char tick_ascii[256];
	int2ascii(tick, tick_ascii);
	kprint(tick_ascii);
	kprint("\n");
	*/
}

void init_timer(uint32_t freq) {
	register_interrupt_handler(IRQ0, timer_callback);

	/* Get PIT value: hardware clock at 1193180 Hz */
	uint32_t divisor = HERTZ / freq;
	uint8_t low = (uint8_t)(divisor & 0xFF);
	uint8_t high = (uint8_t)((divisor >> 8) & 0xFF);

	port_byte_out(0x43, 0x36); /* command port */
	port_byte_out(0x40, low);
	port_byte_out(0x40, high);
}
