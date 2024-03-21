#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "calc.h"
#include "ops.h"
#include "parse.h"

int main(int argc, char* argv[]) {
    // getting the input
    char* input = NULL;
    size_t size;

    if (getline(&input, &size, stdin) == -1) {
        fprintf(stderr, "Error getting input\n");
        return -1;
    }

    // recurive parsing and calculation
    int res = calc_recursive(input);

    // output
    printf("%d\n", res);
}
