#include "string.h"

/* Return length of string */
int str_len(char s[]) {
	int i = 0;
	while(s[i] != '\0')
		++i;
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
	s[len-1] = '\0';
}

void backspace(char s[]) {
	int len = str_len(s);
	s[len-1] = '\0';
}

int str_cmp(char s1[], char s2[]) {
	int i;
	for(i = 0; s1[i] == s2[i]; i++) {
		if(s1[i] == '\0')
			return 0;
	}
	return s1[i] - s2[i];
}
