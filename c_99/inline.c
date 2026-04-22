#include <stdio.h>
#include <time.h>
#include "../config.h"

// 1. Force the compiler NOT to inline this funcion
__attribute__((noinline)) void add_one(int *x) {
    *x += 1;
}

// 2. Force the compiler to ALWAYS inline this function
__attribute__((always_inline)) static inline void add_one_inline(int *x) {
    *x += 1;
}

double get_time_in_seconds() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + (ts.tv_nsec / 1e9);
}

// A global volatile sink to prevent the compiler from deleting the loops entirely
volatile int global_sink = 0;

int main() {
#ifdef CONFIG_RUN_INLINE_BENCHMARK
    // 4. Use standard local integers so the CPU can keep them in fast registers
    int a = 0; 
    int b = 0;
    double start, end;

    printf("Starting benchmark with %d iterations...\n", CONFIG_INLINE_ITERATIONS);

    // Test 1: Standard Call
    start = get_time_in_seconds();
    for (int i = 0; i < CONFIG_INLINE_ITERATIONS; i++) {
        add_one(&a);
    }
    end = get_time_in_seconds();
    printf("Standard call: %f seconds\n", end - start);

    // Test 2: Inline Call
    start = get_time_in_seconds();
    for (int i = 0; i < CONFIG_INLINE_ITERATIONS; i++) {
        add_one_inline(&b);
    }
    end = get_time_in_seconds();
    printf("Inline call:   %f seconds\n", end - start);

    // Dump results into the volatile sink so the optimizer can't cheat
    global_sink = a + b; 
    printf("Final value (to prevent optimization): %d\n", global_sink); 
#else
    printf("Inline benchmark is disabled in Kconfig.\n");
#endif

    return 0;
}
