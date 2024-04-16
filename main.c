#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "parse.h"
#include "tree_parse.h"
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

    struct Node top_node;

    if (tree_parse_shunting_yard(tokens, len, &top_node)) {
        fprintf(stderr, "Error converting to tree\n");
        return 1;
    }

    // debug
    printf("%d\n", top_node.token->type);
    test_print_tree(&top_node);
}
