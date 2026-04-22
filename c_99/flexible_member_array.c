#include <stdio.h>
#include <stdlib.h>

// --- Approach 1: Struct with a Pointer ---
struct PointerVector {
    size_t length;
    int *data;
};

// --- Approach 2: Struct with a Flexible Array ---
struct FlexibleVector {
    size_t length;
    int data[]; // Flexible array must be the last member
};

int main() {
    size_t num_items = 5;

    printf("=== Approach 1: Pointer Member (2 Mallocs) ===\n");
    
    // Allocation
    struct PointerVector *p_vec = malloc(sizeof(struct PointerVector));
    if (!p_vec) return 1;
    p_vec->length = num_items;
    p_vec->data = malloc(num_items * sizeof(int));
    if (!p_vec->data) { free(p_vec); return 1; }

    // Print sizes and memory layout
    printf("Reported struct size: %zu bytes\n", sizeof(struct PointerVector));
    printf("Struct is located at: %p\n", (void*)p_vec);
    printf("Data is located at:   %p  <-- Notice the massive jump in memory!\n", (void*)p_vec->data);

    // Cleanup (Order matters!)
    free(p_vec->data);
    free(p_vec);

    printf("\n--------------------------------------------------\n\n");

    printf("=== Approach 2: Flexible Array (1 Malloc) ===\n");

    // Allocation
    size_t total_size = sizeof(struct FlexibleVector) + (num_items * sizeof(int));
    struct FlexibleVector *f_vec = malloc(total_size);
    if (!f_vec) return 1;
    f_vec->length = num_items;

    // Print sizes and memory layout
    printf("Reported struct size: %zu bytes (Notice it's smaller!)\n", sizeof(struct FlexibleVector));
    printf("Struct is located at: %p\n", (void*)f_vec);
    printf("Data is located at:   %p  <-- Notice it is immediately after the struct!\n", (void*)f_vec->data);

    // Cleanup (Just one call)
    free(f_vec);

    return 0;
}
