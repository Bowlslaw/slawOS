#include "string.h"

/* Return length of string */
int str_len(char *s) {
	int i;

	for(i = 0; *s != '\0'; s++)
		i++;
	return i;
}

/* Reverse a string */
void reverse(char s[]) {
	int c, i, j;
	for(i = 0, j = str_len(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

/* Convert an integer to its ASCII representation */
void int2ascii(int n, char *str) {
  int i, sign;
  if((sign = n) < 0)
    n = -n;

  i = 0;
  do {
    str[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);

  if(sign < 0)
    str[i++] = '-';
  str[i] = '\0';


	reverse(str);
}

void append(char s[], char n) {
	int len = str_len(s);
	s[len] = n;
	s[len+1] = '\0';
}

/* append s to n */
void str_cat(char *dest, char *src) {
	while(*dest != '\0')
		dest++;
	while((*dest++ = *src++) != '\0')
		;
}


void backspace(char *s) {
	int len = str_len(s);
	s[len-1] = '\0';
}

int str_cmp(char *s, char *t) {
	for( ; *s == *t; s++, t++)
		if(*s == '\0')
			return 0;
	return *s - *t;
}
