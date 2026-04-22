#include <stdio.h>

// The '...' means this macro accepts extra arguments.
// __VA_ARGS__ is replaced by whatever those extra arguments are.
#define LOG_INFO(format, ...) printf("[INFO] " format "\n", __VA_ARGS__)

int main() {
    int users = 5;
    char *system = "Database";

    // Expands to: printf("[INFO] " "System %s has %d users." "\n", system, users)
    LOG_INFO("System %s has %d users.", system, users);

    return 0;
}
