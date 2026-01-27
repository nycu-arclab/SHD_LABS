#ifndef SERIAL_H
#define SERIAL_H

void serial_putc(char c);
void serial_puts(char *str);
char serial_getc(void);
int  serial_read(char *buf, int maxlen);

#endif