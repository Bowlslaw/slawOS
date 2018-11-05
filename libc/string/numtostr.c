#include <string.h>

int numtostr(unsigned int n, char *str) {
  while(n) {
	*str++ = (n % 10) + '0';
	n /= 10;
  }
  return 0;
}
