#include <stdio.h>
#include <complex.h>

int main() {
    double complex z1 = 1.0 + 2.0 * I;
    double complex z2 = 3.0 + 4.0 * I;

    double complex sum = z1 + z2;
    double complex product = z1 * z2;

    printf("z1 = %.1f + %.1fi\n", creal(z1), cimag(z1));
    printf("z2 = %.1f + %.1fi\n", creal(z2), cimag(z2));
    printf("Sum: %.1f + %.1fi\n", creal(sum), cimag(sum));
    printf("Product: %.1f + %.1fi\n", creal(product), cimag(product));

    return 0;
}
