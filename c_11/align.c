#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdalign.h> // Provides 'alignas' and 'alignof' macros

// Using alignas on a struct member to force the whole struct's alignment
// 64 bytes is a common size for modern CPU cache lines.
struct CacheLineData {
    alignas(64) int data[4]; 
};

int main(void) {
    // --- 1. alignof operator ---
    // Checks the default or forced alignment of types
    printf("Standard char alignment: %zu byte\n", alignof(char));
    printf("CacheLineData struct alignment: %zu bytes\n", alignof(struct CacheLineData));

    // --- 2. alignas specifier ---
    // Forcing a standard char array (normally 1-byte aligned) 
    // to sit on a 32-byte boundary in memory.
    alignas(32) char buffer[128];
    printf("Custom local buffer alignment: %zu bytes\n", alignof(buffer));

    // --- 3. aligned_alloc function ---
    // Usage: aligned_alloc(alignment, size)
    // CRITICAL RULE: 'size' MUST be an integral multiple of 'alignment'
    size_t align = 64;
    size_t size = 256; // 256 is exactly 4 times 64

    void *ptr = aligned_alloc(align, size);

    if (ptr != NULL) {
        printf("\nDynamically allocated memory address: %p\n", ptr);
        
        // Verify the mathematical alignment by casting to an integer type
        if (((uintptr_t)ptr % align) == 0) {
            printf("Success: The pointer is perfectly aligned to a %zu-byte boundary!\n", align);
        }
        
        // Memory allocated with aligned_alloc is freed normally with free()
        free(ptr);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}
