#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "parse.h"
#include "test.h"

const char QUIT_SYMBOL = 'q';

int main(int argc, char* argv[]) {
    printf("vcc (very cool calculator)\ntype %c to quit\n", QUIT_SYMBOL);

    while (1) {
        // getting the input
        char* input = NULL;
        size_t size;

        if (getline(&input, &size, stdin) == -1) {
            fprintf(stderr, "Error getting input\n");
            continue;
        }

        int len = strlen(input);
        
        if (input[0] == QUIT_SYMBOL) {
            if (len > 2) {
                fprintf(stderr, "Error: quit symbol cannot be used in a formula\n");
                continue;
            } else {
                return 0;
            }
        }

        // input parsing
        struct Token tokens[len];

        if (parse_tokenize(input, tokens))
            continue;

        free(input);

        struct Token* p_top; // will point to the top of the tree once it's assembled

        if (parse_shunting_yard(tokens, len, &p_top))
            continue;

        // tokens is still the same pile of wood, only that the wood has now been labelled to indicate how it would fit together as a tree.

        test_print_tree(p_top);
    }
}
