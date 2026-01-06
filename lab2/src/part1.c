#include "utils.h"
#include "types.h"

extern void part1_start(void);

void main(void) {
    part1_start();
}

bool check_sum(int32_t a, int32_t b, int32_t c) {
    puts("Checking: a=0x");
    put_hex(a);
    puts(" b=0x");
    put_hex(b);
    puts(" c=0x");
    put_hex(c);
    puts("\r\n");

    if (a + b == c) {
        puts("Problem A Passed!\r\n");
        return true;
    }
    puts("Problem A Failed!\r\n");
    return false;
}

bool check_string(char *str) {
    if (str == NULL) {
        puts("String is NULL\r\n");
        puts("Problem B Failed!\r\n");
        return false;
    }

    puts("Required String: NYCU\r\n");
    puts("String you sent: ");
    puts(str);
    puts("\r\n");

    if (strcmp(str, "NYCU") == 0) {
        puts("Problem B Passed!\r\n");
        return true;
    }
    puts("Problem B Failed!\r\n");
    return false;
}
