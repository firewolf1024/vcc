#include <stdio.h>

int main() {
    char* input = NULL;
    size_t size;

    fprintf(stdout, "frog");

    if (getline(&input, &size, stdin) == -1) {
        fprintf(stderr, "Error getting input\n");
        return 1;
    }

    printf(input);
}
