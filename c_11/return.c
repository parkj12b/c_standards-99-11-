#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h> // Defines 'noreturn' as '_Noreturn'

// This function will either exit the program or loop forever.
// It never hands control back to main().
void stop_everything(const char *msg) {
    fprintf(stderr, "Fatal: %s\n", msg);
    exit(1); 
}

int main(void) {
    printf("Initializing system...\n");

    int critical_error = 1;

    if (critical_error) {
        stop_everything("Hardware failure detected.");
        
        // The compiler knows this part of the code is "dead."
        // Most compilers will give you a warning: "code will never be executed"
        printf("This line will never, ever run.\n");
    }

    return 0;
}
