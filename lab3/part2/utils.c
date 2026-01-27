#include "utils.h"
#include "serial.h"
#include <stdarg.h>

void printf(char *format, ...) {
    va_list ap;
    va_start(ap, format);

    char *idx;
    for (idx = format; *idx != '\0'; idx++) {
        if (*idx == '%') { // skip "%"
            idx++;
            switch (*idx) {
                case 'c': {
                    char c = (char)va_arg(ap, int);
                    serial_putc(c);
                    break;
                }
                case 's': {
                    char *s = va_arg(ap, char*);
                    serial_puts(s);
                    break;
                }
                case 'x': {
                    unsigned int val = va_arg(ap, unsigned int);
                    // print hex
                    char hex[9];
                    hex[8] = '\0';
                    for (int i = 7; i >= 0; i--) {
                        int digit = val & 0xF;
                        hex[i] = (digit < 10) ? ('0' + digit) : ('A' + digit - 10);
                        val >>= 4;
                    }
                    char *p = hex;
                    while (*p == '0' && *(p+1) != '\0') p++;
                    serial_puts(p);
                    break;
                }
                case 'd': {
                    int val = va_arg(ap, int);
                    if (val < 0) {
                        serial_putc('-');
                        val = -val;
                    }
                    // print decimal
                    char buf[12];
                    int i = 10;
                    buf[11] = '\0';
                    do {
                        buf[i--] = '0' + (val % 10);
                        val /= 10;
                    } while (val > 0);
                    serial_puts(&buf[i+1]);
                    break;
                }
                case '%': {
                    serial_putc('%');
                    break;
                }
                default:
                    serial_putc('%');
                    serial_putc(*idx);
                    break;
            }
        } else { // only one argument
            serial_putc(*idx);
        }
    }

    va_end(ap);
}

int atoi(const char *str) {
    int result = 0;
    int sign = 1;
    
    // Skip whitespace
    while (*str == ' ' || *str == '\t') str++;
    
    // Handle sign
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }
    
    // Convert digits
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }
    
    return sign * result;
}