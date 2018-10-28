#include <stdio.h>
#include <string.h>

#include <kernel/tty.h>

void kernel_main(void) {
	terminal_initialize();
	printf("Hello, kernel World!\n");

	const char src[50] = "this is a test string";
	char dest[50];
	strcpy(dest, "Helloooo!");
	printf("Before memmove: %s\n", dest);
	memmove(dest, src, strlen(src) + 1);
	printf("After memmove: %s\n", dest);

	for(int i = 0; i < 23; i++)
	  printf("%d\n", i);
}
