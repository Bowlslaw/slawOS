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

  char src2[] = "poopstring";
  char dest2[] = "peestring";
  printf("Before strcpy: %s | %s\n", dest2, src2);
  strcpy(dest, src);
  printf("After strcpy: %s | %s\n", dest2, src2);

  for(int i = 0; i < 10; i++)
	printf("i = %d\n", i);
}
