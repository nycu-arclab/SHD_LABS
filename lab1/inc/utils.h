#ifndef UTILS_H
#define UTILS_H

#include "types.h"

// Character I/O
void putc(char c);
char getc(void);

// String I/O
void puts(char *str);
void gets(char *str);

// Number I/O
void put_int(int32_t val);
int32_t get_int(void);

// String functions
size_t strlen(char *str);

#endif