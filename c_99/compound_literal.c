#include <stdio.h>

struct Point {
    int x;
    int y;
};

// A simple function that expects a struct
void draw_point(struct Point p) {
    printf("Drawing at X:%d, Y:%d\n", p.x, p.y);
}

// A function that expects a POINTER to a struct
void move_point(struct Point *p, int dx, int dy) {
    p->x += dx;
    p->y += dy;
    printf("Moved to X:%d, Y:%d\n", p->x, p->y);
}

int main() {
    // --- The Old Way (C89) ---
    // We have to pollute our scope with a variable we only use once
    struct Point temp_p = {10, 20};
    draw_point(temp_p);

    // --- The New Way (Compound Literal) ---
    // We create an unnamed struct directly inside the function call!
    draw_point((struct Point){30, 40});

    // --- The "Ultimate" Way ---
    // Combining compound literals WITH designated initializers
    draw_point((struct Point){ .y = 100, .x = 50 });

    // --- The Magic Trick (Taking the address) ---
    // Unlike standard literals (like the number 5), compound literals actually 
    // exist in memory. That means you can take their address using '&'!
    move_point(&(struct Point){1, 1}, 5, 5);

    return 0;
}
