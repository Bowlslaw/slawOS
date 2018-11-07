#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>

#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

#define NEWLINE   0x0A
#define BACKSPACE 0x08
#define TAB       0x09

#define PIC1_CMD 0x20
#define PIC1_DATA 0x21
#define PIC2_CMD 0xA0
#define PIC2_DATA 0xA1

void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
void terminal_print_error(void);

unsigned char port_byte_in(unsigned short port);
void port_byte_out(unsigned short port, unsigned char data);

int get_cursor_offset();
void set_cursor_offset(int offset);
void update_cursor(int x, int y);

#endif
