#include "test.h"

#include <stdio.h>

#include "token.h"

const char* TOKEN_NAMES[] = {"NUM", "SGN", "VAR", "SET", "FUN", "OPS", "LPR", "RPR", "OLD", "END"};
const char* OP_NAMES[] = {"POW", "DIV", "MUL", "SUB", "ADD"};
const char* FN_NAMES[] = {"SQRT", "EXP", "LN", "LOG", "SIN", "COS", "TAN", "ASIN", "ACOS", "ATAN"};

// traverses the tree in post-order to print its contents in RPN
void test_print_tree(struct Token* p_top) {
    if (p_top->left)
        test_print_tree(p_top->left);

    if (p_top->right)
        test_print_tree(p_top->right);
    
    printf("type: %s ", TOKEN_NAMES[p_top->type]);
    switch (p_top->type) {
        case NUM:
            printf("val: %lf", p_top->value);
            break;
        case VAR:
            printf("name: %c", p_top->name);
            break;
        case FUN:
            printf("fn_type: %s", FN_NAMES[p_top->fn_type]);
            break;
        case OPS:
            printf("op_type: %s", OP_NAMES[p_top->op_type]);
            break;
        case SET:
            break;
        default:
            printf("Why is this even in the tree?");
            break;
    }
    printf("\n");
}
