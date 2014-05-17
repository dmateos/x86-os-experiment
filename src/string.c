#include "string.h"

size_t strlen(char s[]) {
  int i = 0;
  while(*s++ != '\0')
    i++;
  return i;
}

void reverse(char s[]) {
  int i, j;
  char tmp;

  for(i = 0, j = strlen(s)-1; i < j; i++, j--) {
    tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;
  }
}

void itoa(int n, char s[]) {
  int i, sign;
  if((sign = n) < 0) {
    n = -n;
  }
  i = 0;
  do {
    s[i++] = n % 10 + '0';
  } while((n /= 10) > 0);

  if(sign < 0) {
    s[i++] = '-';
  }
  s[i] = '\0';
  reverse(s);
}
