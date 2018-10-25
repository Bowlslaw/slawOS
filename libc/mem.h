#ifndef MEM_H
#define MEM_H

#include <stdint.h>

/* Copy bytes from src to dest */
void mem_cpy(char *src, char *dest, int bytes);

/* TODO: Provide short explanation */
void mem_set(uint8_t *dest, uint8_t val, uint32_t len);

uint32_t kmalloc(uint32_t size, int align, uint32_t *paddr);

#endif
