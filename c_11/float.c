#include <stdio.h>
#include <float.h>

int main(void) {
    printf("--- Subnormal Support ---\n");
    printf("Does float support subnormals?       %d\n", FLT_HAS_SUBNORM);
    printf("Does double support subnormals?      %d\n", DBL_HAS_SUBNORM);
    
    // The smallest normal float vs the smallest subnormal float
    printf("\nSmallest normal float:   %e\n", FLT_MIN);
    printf("Smallest subnormal float:  %e\n", FLT_TRUE_MIN); // Added in C11!

    printf("\n--- Serialization Digits (Float) ---\n");
    printf("Trustworthy digits (FLT_DIG):        %d\n", FLT_DIG);
    printf("Round-trip digits (FLT_DECIMAL_DIG): %d\n", FLT_DECIMAL_DIG);

    // Demonstration of the Round-Trip problem
    float original = 0.1f;
    
    // If we only print to FLT_DIG (6 digits)...
    printf("\nPrinted with %%..%df: %.*f\n", FLT_DIG, FLT_DIG, original);
    
    // To guarantee another parser rebuilds the EXACT binary representation of 0.1f,
    // we must print using FLT_DECIMAL_DIG (9 digits).
    printf("Printed with %%..%df: %.*f\n", FLT_DECIMAL_DIG, FLT_DECIMAL_DIG, original);

    return 0;
}
