#include <stdio.h>
#include <stdlib.h>
#include <threads.h>   // C11 Threads, Mutexes, and thread_local
#include <stdatomic.h> // C11 Atomics

#define NUM_THREADS 5
#define ITERATIONS 10000

// --- Global Variables ---

// 1. Mutex-protected shared variable
mtx_t shared_mutex;
int shared_counter = 0;

// 2. Atomic lock-free shared variable
atomic_int atomic_counter = 0;

// 3. Thread-local variable (each thread gets its own initialized to 0)
thread_local int local_counter = 0; 

// --- The Thread Function ---
// Must return int and take a void* argument
int worker_thread(void *arg) {
    int thread_id = *(int*)arg;

    for (int i = 0; i < ITERATIONS; i++) {
        // --- Mutex Protected ---
        mtx_lock(&shared_mutex);
        shared_counter++; 
        mtx_unlock(&shared_mutex);

        // --- Atomic Protected ---
        // atomic_counter++ safely increments without a mutex lock
        atomic_counter++; 

        // --- Thread Local ---
        // Completely safe to modify without locks; no other thread can see this.
        local_counter++; 
    }

    printf("Thread %d finished. Its local_counter is: %d\n", thread_id, local_counter);
    return thrd_success;
}

int main(void) {
    thrd_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Initialize the mutex (mtx_plain means a standard, non-recursive mutex)
    if (mtx_init(&shared_mutex, mtx_plain) != thrd_success) {
        fprintf(stderr, "Failed to initialize mutex.\n");
        return 1;
    }

    // Create the threads
    printf("Starting %d threads...\n\n", NUM_THREADS);
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        if (thrd_create(&threads[i], worker_thread, &thread_ids[i]) != thrd_success) {
            fprintf(stderr, "Failed to create thread %d.\n", i);
            return 1;
        }
    }

    // Wait for all threads to finish (Join them)
    for (int i = 0; i < NUM_THREADS; i++) {
        thrd_join(threads[i], NULL);
    }

    // Clean up
    mtx_destroy(&shared_mutex);

    // Print final results
    printf("\n--- Final Results ---\n");
    printf("Expected total for shared counters: %d\n", NUM_THREADS * ITERATIONS);
    printf("Mutex shared_counter:  %d\n", shared_counter);
    printf("Atomic atomic_counter: %d\n", atomic_counter);

    return 0;
}
