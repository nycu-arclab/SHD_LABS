#include "qemu_virt.h"
#include "types.h"
#include "utils.h"

// Put a single character to UART
void putc(char c) {
    volatile char *UART_TX = (char *)QEMU_VIRT_UART;
    *UART_TX = c;
}

// Get a single character from UART
char getc(void) {
    volatile char *UART_RX = (char *)QEMU_VIRT_UART;
    volatile char *UART_LSR = (char *)QEMU_VIRT_UART_LSR;

    // Wait until data is ready
    while ((*UART_LSR & UART_LSR_DATA_READY_MASK) == 0);

    return *UART_RX;
}

// Print a string to UART
void puts(char *str) {
    while (*str) {
        putc(*str);
        str++;
    }
}

// Read a string from UART (unsafe, for demo only)
void gets(char *str) {
    char *cursor = str;

    while (true) {
        *cursor = getc();
        putc(*cursor);  // Echo back

        if (*cursor == SERIAL_NEWLINE || *cursor == NEWLINE) {
            *cursor = '\0';
            return;
        }
        cursor++;
    }
}

// Print a decimal number (0-999)
void put_int(int32_t val) {
    if (val < 0) {
        putc('-');
        val = -val;
    }

    if (val >= 100) {
        putc('0' + val / 100);
        val %= 100;
        putc('0' + val / 10);
        val %= 10;
    } else if (val >= 10) {
        putc('0' + val / 10);
        val %= 10;
    }
    putc('0' + val);
}

// Read a decimal number from UART
int32_t get_int(void) {
    int32_t result = 0;
    char c;

    while (true) {
        c = getc();
        putc(c);  // Echo back

        if (c == SERIAL_NEWLINE || c == NEWLINE) {
            return result;
        }

        if (c >= '0' && c <= '9') {
            result = result * 10 + (c - '0');
        }
    }
}

// Get string length
size_t strlen(char *str) {
    size_t len = 0;
    while (*str++) len++;
    return len;
}