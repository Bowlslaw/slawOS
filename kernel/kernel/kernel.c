#include <stdio.h>
#include <string.h>

#include <kernel/tty.h>

void kernel_main(void) {
  terminal_initialize();
  printf("Hello, kernel World!\n");

  char dest[] = "oldstring";
  const char src[] = "newstring";

  printf("Before memove: %s | %s\n", dest, src);
  memmove(dest, src, strlen(dest));
  printf("After memmove: %s | %s\n", dest, src);

  for(int i = 0; i < 30; i++) {
	printf("HERE\n");
  }
}
