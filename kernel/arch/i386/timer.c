#include <stdint.h>

#include "idt.h"

#define HERTZ 1193180

uint32_t tick = 0;

static void timer_callback(void) {
  tick++;
}
