#include <stdio.h>
#include <assert.h> // Provides the static_assert macro

// Guarantee that we are compiling on a 64-bit system where pointers are 8 bytes.
static_assert(sizeof(void *) == 8, "This code requires a 64-bit architecture!");

// Guarantee that an integer is exactly 32 bits (4 bytes).
static_assert(sizeof(int) == 4, "Integers must be exactly 32 bits.");

int main(void) {
    printf("Architecture checks passed! Compiling...\n");
    return 0;
}
