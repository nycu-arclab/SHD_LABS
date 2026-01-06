#include "utils.h"
#include "qemu_virt.h"

#define UART_LSR_TX_IDLE 0x20

void putc(char c) {
    volatile char *uart = (volatile char *)QEMU_VIRT_UART;
    volatile char *lsr = (volatile char *)QEMU_VIRT_UART_LSR;
    while ((*lsr & UART_LSR_TX_IDLE) == 0);
    *uart = c;
}

void puts(const char *s) {
    while (*s) {
        putc(*s++);
    }
}

char getc(void) {
    volatile char *uart = (volatile char *)QEMU_VIRT_UART;
    volatile char *lsr = (volatile char *)QEMU_VIRT_UART_LSR;
    while ((*lsr & UART_LSR_DATA_READY_MASK) == 0);
    return *uart;
}

void gets(char *buf) {
    char c;
    while (1) {
        c = getc();
        if (c == '\r' || c == '\n') {
            *buf = '\0';
            return;
        }
        putc(c);  // echo
        *buf++ = c;
    }
}

void put_hex(uint32_t val) {
    char hex[] = "0123456789ABCDEF";
    for (int i = 28; i >= 0; i -= 4) {
        putc(hex[(val >> i) & 0xF]);
    }
}

void put_int(uint32_t val) {
    if (val == 0) {
        putc('0');
        return;
    }
    char buf[12];
    int i = 0;
    while (val > 0) {
        buf[i++] = '0' + (val % 10);
        val /= 10;
    }
    while (--i >= 0) {
        putc(buf[i]);
    }
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}