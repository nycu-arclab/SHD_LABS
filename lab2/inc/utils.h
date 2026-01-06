#ifndef UTILS_H
#define UTILS_H

#include "types.h"

void putc(char c);
void puts(const char *s);
char getc(void);
void gets(char *buf);
void put_hex(uint32_t val);
void put_int(uint32_t val);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, uint32_t n);

#endif