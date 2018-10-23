#include "mem.h"
#include <stdint.h>

/* Copy bytes from src to dest */
void mem_cpy(char *src, char *dest, int bytes) {
  int i;
  for(i = 0; i < bytes; i++) {
    *(dest + i) = *(src + i);
  }
}

void mem_set(uint8_t *dest, uint8_t val, uint32_t len) {
  uint8_t *temp = (uint8_t *)dest;
  for( ;len != 0; len--) {
    *temp++ = val;
  }
}
