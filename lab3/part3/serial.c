#include "serial.h"

#define CSR_SERIAL_OUT        0x004
#define CSR_SERIAL_IN_STATUS  0x005
#define CSR_SERIAL_IN_DATA    0x006

// Output
static inline void csr_write_serial(char c) {
    asm volatile (
        "csrw %0, %1"
        :
        : "i"(CSR_SERIAL_OUT), "r"((unsigned int)c)
    );
}

void serial_putc(char c) {
    csr_write_serial(c);
}

void serial_puts(char *str) {
    while (*str) {
        serial_putc(*str);
        str++;
    }
}

// Input
static inline unsigned int csr_read_status(void) {
    unsigned int val;
    asm volatile ("csrr %0, 0x005" : "=r"(val));
    return val;
}

static inline unsigned int csr_read_data(void) {
    unsigned int val;
    asm volatile ("csrr %0, 0x006" : "=r"(val));
    return val;
}

char serial_getc(void) {
    while (!(csr_read_status() & 1)) {
        // busy wait
    }
    return (char)(csr_read_data() & 0xFF);
}

int serial_read(char *buf, int maxlen) {
    int i = 0;
    while (i < maxlen - 1) {
        char c = serial_getc();
        if (c == '\n' || c == '\r') {
            break;
        }
        buf[i++] = c;
    }
    buf[i] = '\0';
    return i;
}