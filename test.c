#include "test.h"

#include <stdio.h>

#include "parse.h"
#include "tree.h"

const char* TOKEN_NAMES[] = {"NUM", "VAR", "SET", "OPS", "LPR", "RPR", "END"};
const char* OP_NAMES[] = {"POW", "DIV", "MUL", "SUB", "ADD"};

// traverses the tree in post-order to print its contents in RPN
void test_print_tree(struct Node* p_top_node) {
    if (p_top_node->left)
        test_print_tree(p_top_node->left);

    if (p_top_node->right)
        test_print_tree(p_top_node->right);
    
    printf("type: %s, op: %s, val: %f\n", 
            TOKEN_NAMES[p_top_node->token->type], 
            OP_NAMES[p_top_node->token->op_type], 
            p_top_node->token->value);
}
