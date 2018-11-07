/*
 * This is the screen driver. It contains functions which print
 * characters and colors to the screen
 * using the VGA controller.
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>

#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t *const VGA_MEMORY = (uint16_t *)0xC03FF000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t *terminal_buffer;

int get_offset(int col, int row) {
  return 2 * (row * VGA_WIDTH + col);
}

int get_offset_row(int offset) {
  return offset / (2 * VGA_WIDTH);
}

int get_offset_col(int offset) {
  return (offset - (get_offset_row(offset) * 2 * VGA_WIDTH)) / 2;
}

/* print white/red E to bottom right corner of screen */
void terminal_print_error(void) {
  if(terminal_row >= VGA_HEIGHT) {
	terminal_row = 0;
	terminal_putentryat('E', vga_entry_color(VGA_COLOR_RED, VGA_COLOR_WHITE),
						VGA_WIDTH - 1, VGA_HEIGHT - 1);
  }
}

void terminal_initialize(void) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_CYAN);
	terminal_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) {
	unsigned char uc = c;

	switch(c) {
	  case NEWLINE:
		terminal_row++;
		terminal_column = 0;
		break;

	  case TAB:
		terminal_putentryat('    ', terminal_color, terminal_column, terminal_row);
		terminal_column += 4;
		break;

	  case BACKSPACE:
		terminal_column--;
		terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
		break;

	  default:
		terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
		terminal_column++;
	}

	if(terminal_column >= VGA_WIDTH) {
	  terminal_column = 0;
	  terminal_row++;
	}

	if(terminal_row >= VGA_HEIGHT) {
	  size_t i, j;
	  for(i = 0; i < VGA_WIDTH-1; i++) {
		for(j = VGA_HEIGHT-2; j > 0; j--)
		  terminal_buffer[(j * VGA_WIDTH) + i] = terminal_buffer[((j+1) * VGA_WIDTH) + i];
	  }
	  for(i = 0; i < VGA_WIDTH; i++) {
		terminal_putentryat(' ', terminal_color, i, VGA_HEIGHT - 1);
	  }

	  terminal_row = VGA_HEIGHT - 1;
	}

	update_cursor(terminal_column, terminal_row);
}

void terminal_write(const char *data, size_t size) {
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char *data) {
	terminal_write(data, strlen(data));
}

/* inb */
unsigned char port_byte_in(unsigned short port) {
  unsigned char result;
  asm ("in %%dx, %%al" : "=a" (result) : "d" (port));
  return result;
}

/* outb */
void port_byte_out(unsigned short port, unsigned char data) {
  asm ("out %%al, %%dx" : : "a" (data), "d" (port));
}

int get_cursor_offset() {
  /*
   * Use the VGA ports to get the current cursor position
   * 1. Ask for high byte of the cursor offset (data 14)
   * 2. Ask for low byte (data 15)
   */
  port_byte_out(REG_SCREEN_CTRL, 14);
  int offset = port_byte_in(REG_SCREEN_DATA) << 8; /* High byte: << 8 */
  port_byte_out(REG_SCREEN_CTRL, 15);
  offset += port_byte_in(REG_SCREEN_DATA);
  return offset * 2; /* Position * size of character cell */
}

void set_cursor_offset(int offset) {
  /* Similar to get_cursor_offset, but instead of reading we write data */
  offset /= 2;
  port_byte_out(REG_SCREEN_CTRL, 14);
  port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
  port_byte_out(REG_SCREEN_CTRL, 15);
  port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

void update_cursor(int x, int y) {
  uint16_t pos = y * VGA_WIDTH + x;

  port_byte_out(REG_SCREEN_CTRL, 15);
  port_byte_out(REG_SCREEN_DATA, (uint8_t)(pos & 0xFF));
  port_byte_out(REG_SCREEN_CTRL, 14);
  port_byte_out(REG_SCREEN_DATA, (uint8_t)(pos >> 8) & 0xFF);
}

/*
void enable_cursor(uint8_t cursor_start, uint8_t cursor_end) {
  outb(0x3D4, 0x0A);
  outb(0x3D, (inb(0x3D5) & 0xC0) | cursor_start);

  outb(0x3D4, 0x0B);
  outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}
*/
