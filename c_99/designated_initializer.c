#include <stdio.h>

struct point {
    int x;
    int y;
    int z;
};

int main() {
    // Designated initializers for structures
    struct point p = { .y = 2, .x = 1, .z = 3 };

    // Designated initializers for arrays
    int arr[10] = { [2] = 20, [5] = 50, [8] = 80 };

    printf("Point: x=%d, y=%d, z=%d\n", p.x, p.y, p.z);
    
    printf("Array elements:\n");
    for (int i = 0; i < 10; i++) {
        if (arr[i] != 0) {
            printf("arr[%d] = %d\n", i, arr[i]);
        }
    }

    return 0;
}
