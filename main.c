#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "parse.h"
#include "test.h"

int main(int argc, char* argv[]) {
    // getting the input
    char* input = NULL;
    size_t size;

    if (getline(&input, &size, stdin) == -1) {
        fprintf(stderr, "Error getting input\n");
        return 1;
    }

    // input parsing
    int len = strlen(input);
    struct Token tokens[len];

    if (parse_tokenize(input, tokens)) {
        fprintf(stderr, "Error parsing tokens\n");
        return 1;
    }

    free(input);

    struct Token* p_top; // will point to the top of the tree once it's assembled

    if (parse_shunting_yard(tokens, len, &p_top)) {
        fprintf(stderr, "Error converting to tree\n");
        return 1;
    }

    // tokens is still the same pile of wood, only that the wood has now been labelled to indicate how it would fit together as a tree.

    // debug
    //printf("%d\n", p_top->type);
    //test_print_tree(p_top);
}

