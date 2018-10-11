#include "../drivers/screen.h"
#include "utils.h"

void main() {
  clear_screen();
  int i = 0;
  for(i = 0; i < 24; i++) {
    char str[255];
    int2ascii(i, str);
    kprint_at(str, 0, i);
  }
  kprint("\nHi!\n\n\n");
  kprint("Hello!\n");
}
