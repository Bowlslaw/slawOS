#ifndef STRING_H
#define STRING_H

/* Return length of string */
int str_len(char *s);

/* Reverse a string */
void reverse(char s[]);

/* Convert an integer to its ASCII representation */
void int2ascii(int n, char *str);

void backspace(char s[]);

void append(char s[], char n);

void str_cat(char *s, char *n);

int str_cmp(char *s1, char *s2);

#endif
