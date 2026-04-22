#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// _Generic selects the function name (pointer), and THEN we invoke it with (X)
#define absolute_value(X) _Generic((X), \
    int: abs,                           \
    float: fabsf,                       \
    double: fabs,                       \
    long double: fabsl,                 \
    default: fabs                       \
)(X)

int main(void) {
    int i = -10;
    float f = -3.14f;
    double d = -9.81;

    // The compiler expands absolute_value(d) to:
    // (fabs)(d)
    // Which is perfectly valid and causes no type conflicts in unselected branches!

    printf("Integer: %d\n", absolute_value(i));
    printf("Float: %f\n", absolute_value(f));
    printf("Double: %f\n", absolute_value(d));

    return 0;
}
