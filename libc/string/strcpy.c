#include <string.h>

void strcpy(char *dest, const char *src) {
  while((*dest++ = *src++) != '\0')
	;
}
