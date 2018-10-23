#include "timer.h"
#include "isr.h"
#include "io.h"
#include "../libc/function.h"

u32 tick = 0;

static void timer_callback(registers_t regs) {
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

void init_timer(u32 freq) {
	register_interrupt_handler(IRQ0, timer_callback);

	/* Get PIT value: hardware clock at 1193180 Hz */
	u32 divisor = 1193180 / freq;
	u8 low = (u8)(divisor & 0xFF);
	u8 high = (u8)((divisor >> 8) & 0xFF);

	port_byte_out(0x43, 0x36); /* command port */
	port_byte_out(0x40, low);
	port_byte_out(0x40, high);
}
