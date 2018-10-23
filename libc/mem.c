#include "mem.h"

/* Copy bytes from src to dest */
void mem_cpy(char *src, char *dest, int bytes) {
  int i;
  for(i = 0; i < bytes; i++) {
    *(dest + i) = *(src + i);
  }
}

void mem_set(u8 *dest, u8 val, u32 len) {
  u8 *temp = (u8 *)dest;
  for( ;len != 0; len--) {
    *temp++ = val;
  }
}
