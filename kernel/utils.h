#ifndef UTIL_H
#define UTIL_H

#include "../cpu/types.h"

void mem_cpy(char *src, char *dest, int bytes);
void mem_set(u8 *dest, u8 val, u32 len);
void int2ascii(int n, char *str);
void reverse(char s[]);
int str_len(char s[]);

#endif
