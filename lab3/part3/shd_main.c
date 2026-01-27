
#include "utils.h"
#include "serial.h"

// a flag to keep track of the occurence of exception
volatile int exception_triggered = 0;

#define MAX_SIZE 100

// Reference Multiplication
int acc_mul(int a, int b) {
    int result = 0;
    for (int i = 0; i < a; i++) {
        result += b;
    }
    return result;
}

void vulnerable_function(void) {
    char inputbuf[MAX_SIZE];
    int a, b;

    printf("+------------------------+\n");
    printf("|   Secure Data Reader   |\n");
    printf("+------------------------+\n");
    printf("inputbuf is at 0x%x\n", (unsigned int)inputbuf);

    printf("Enter number of data: ");
    serial_read(inputbuf, 16);
    a = atoi(inputbuf);

    printf("Enter length of each data: ");
    serial_read(inputbuf, 16);
    b = atoi(inputbuf);

    // Bounds check 
    int total_size = a * b;
    printf("Calculated size: %d\n", total_size);

    if (total_size > MAX_SIZE) {
        printf("Error: Too much data (max %d bytes)!\n", MAX_SIZE);
        return;
    }

    int actual_size = acc_mul(a, b);
    printf("Enter your data (%d bytes): ", actual_size);
    serial_read(inputbuf, actual_size);

    printf("Received: %s\n", inputbuf);
}

int test_main(void) {
    vulnerable_function();
    printf("Program finished normally.\n");
    return 0;
}