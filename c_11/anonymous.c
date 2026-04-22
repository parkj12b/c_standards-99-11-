#include <stdio.h>

// C11 Style
struct ModernVector {
    union { // <-- Anonymous Union
        struct { float x, y, z; }; // <-- Anonymous Struct
        float array[3];
    }; 
};

int main(void) {
    struct ModernVector v;
    
    // Beautiful, clean access.
    // We are writing to the exact same memory location...
    v.x = 1.0f;
    v.y = 2.0f;
    v.z = 3.0f;

    // ...but we can read it directly as an array without deep nesting!
    for (int i = 0; i < 3; i++) {
        printf("Index %d: %f\n", i, v.array[i]);
    }

    return 0;
}
