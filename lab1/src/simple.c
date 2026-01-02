#include "utils.h"

// External assembly function (defined in compute.S)
extern int32_t compute(int32_t n);

int main(void) {
    int32_t n, result;

    puts("Enter n: ");
    n = get_int();
    puts("\n");

    // Call assembly function to compute sum
    result = compute(n);

    puts("Sum(1..");
    put_int(n);
    puts(") = ");
    put_int(result);
    puts("\n");

    return 0;
}