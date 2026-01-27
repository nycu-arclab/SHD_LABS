
#include "utils.h"

// a flag to keep track of the occurence of exception
volatile int exception_triggered = 0;


// ================================= TODO =================================

// Implement a function that computes multiplication without using the MUL instruction.


// main function, the CPU executes this after bootup
int test_main(void){
    printf("Start fuzzing for MUL bug.......\n");
    // TODO: Test different combinations of inputs
    // Compare hardware MUL result with ref_mul()
    // Print any discrepancies found
    printf("End fuzzing!\n");
}

// ================================= TODO =================================





// ================================= SOLUTION =================================
// int acc_mul(int a, int b){
//     int res = 0;
//     for (int i = 0; i < a; i++){
//         res += b;
//     }
//     return res;
// }

// int test_main(void){

//     printf("Start fuzzing for MUL bug.......\n");
//     for (int i = 0; i < 30; i++){
//         for (int j = 0; j < 30; j++){
//             int cal = i * j;
//             if (cal != acc_mul(i,j)){
//                 printf("Bug Detected!!\n");
//                 printf("%d * %d = %d, instead of %d\n", i, j, i * j, acc_mul(i,j));
//             }
//         }
//     }
//     printf("End fuzzing!\n");

//     return 0;
// }
// ================================= SOLUTION =================================