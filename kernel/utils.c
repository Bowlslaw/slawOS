/* Copy bytes from src to dest */
void mem_cpy(char *src, char *dest, int bytes) {
  int i;
  for(i = 0; i < bytes; i++) {
    *(dest + i) = *(src + i);
  }
}


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
}
