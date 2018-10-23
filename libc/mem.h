#ifndef MEM_H
#define MEM_H

#include "../cpu/types.h"

/* Copy bytes from src to dest */
void mem_cpy(char *src, char *dest, int bytes);

/* TODO: Provide short explanation */
void mem_set(u8 *dest, u8 val, u32 len);

#endif
