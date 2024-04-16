#include "test.h"

#include <stdio.h>

#include "token.h"

const char* TOKEN_NAMES[] = {"NUM", "VAR", "SET", "OPS", "LPR", "RPR", "END"};
const char* OP_NAMES[] = {"POW", "DIV", "MUL", "SUB", "ADD"};

// traverses the tree in post-order to print its contents in RPN
void test_print_tree(struct Token* p_top) {
    if (p_top->left)
        test_print_tree(p_top->left);

    if (p_top->right)
        test_print_tree(p_top->right);
    
    printf("type: %s, op: %s, val: %f\n", 
            TOKEN_NAMES[p_top->type], 
            OP_NAMES[p_top->op_type], 
            p_top->value);
}
