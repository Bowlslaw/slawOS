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

uint32_t free_mem_addr = 0x10000;

uint32_t kmalloc(uint32_t size, int align, uint32_t *paddr) {
	if(align == 1 && (free_mem_addr & 0xFFFFF000)) {
		free_mem_addr &= 0xFFFFF000;
		free_mem_addr += 0x1000;
	}

	if(paddr)
		*paddr = free_mem_addr;

	uint32_t ret = free_mem_addr;
	free_mem_addr += size;
	return ret;
}
