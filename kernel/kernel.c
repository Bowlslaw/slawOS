#include "../drivers/io.h"

void main() {
  /* Screen cursor position: ask VGA control register (0x3d4) for bytes
   * 14 = high byte of cursor, 15 = low byte of cursor */
  port_byte_out(0x3d4, 14); /* request byte 14: high byte */

  /* Data return in VGA data register(0x3d5) */
  int position = port_byte_in(0x3d5);
  position = position << 8; /* high byte */

  port_byte_out(0x3d4, 15); /* low byte */
  position += port_byte_in(0x3d5);

  /* VGA cells consist of character and its control ata
   * 'white on black background' */
  int offset_from_vga = position * 2;

  char *vga = 0xb8000;
  vga[offset_from_vga] = 'X';
  vga[offset_from_vga + 1] = 0x0f; /* white text on black background */
}
