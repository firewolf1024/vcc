#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "parse.h"

int main(int argc, char* argv[]) {
    // getting the input
    char* input = NULL;
    size_t size;

    if (getline(&input, &size, stdin) == -1) {
        fprintf(stderr, "Error getting input\n");
        return -1;
    }

    // input parsing
    int len = strlen(input);
    struct Token tokens[len];

    if (parse_tokenize(input, tokens)) {
        fprintf(stderr, "Error parsing tokens\n");
        return 1;
    }

    if (parse_shunting_yard(tokens, len)) {
        fprintf(stderr, "Error converting to RPN\n");
        return 1;
    }
}
