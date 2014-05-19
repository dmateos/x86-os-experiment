#ifndef _STRING_H_
#define _STRING_H_

#include <stdint.h>
#include <stddef.h>

size_t strlen(char s[]);
void reverse(char s[]);
void itoa(int n, char*, int base);
void *memset(void *b, int c, size_t len);

#endif
