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

void itoa(int value, char* result, int base) {
  // check that the base if valid
  if (base < 2 || base > 36) { *result = '\0'; return; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

  do {
    tmp_value = value;
    value /= base;
    *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
  } while ( value );

  // Apply negative sign
  if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
  while(ptr1 < ptr) {
    tmp_char = *ptr;
    *ptr--= *ptr1;
    *ptr1++ = tmp_char;
  }
}

void *memset(void *b, int c, size_t len) {
  return NULL;
}
