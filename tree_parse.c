#include "tree_parse.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "parse.h"

int tree_parse_shunting_yard(struct Token* tokens, int len, struct Node* p_top_node) {
    // not actual stacks but you get what I mean
    struct Token* op_stack[len];
    struct Node* out_stack[len];
    // j: top of the output stack, k: top of the operator stack
    // -1 indicates an empty stack
    int j = -1, k = -1;
   
    for (int i = 0; tokens[i].type != END; i++) {
        switch (tokens[i].type) {
            case NUM:
            case VAR:
                j++;
                out_stack[j].token = &tokens[i];
                break;
            
            case SET:
                // TODO
                break;

            case LPR:
                k++;
                op_stack[k] = tokens[i];
                break;

            case RPR:
                while (op_stack[k].type != LPR) {
                    if (k == -1) {
                        fprintf(stderr, "Error: Mismatched parentheses\n");
                        return 1;
                    }
                    struct Node op = {&op_stack[k], &out_stack[-2], &out_stack[-1]};
                    j--;
                    out_stack[j] = op;
                    k--;
                }
                k--; // discard opening parentheses
                break;

            case OPS:
                while (k > -1 && 
                        op_stack[k].type == OPS && 
                        op_stack[k].op_type < tokens[i].op_type) {
                    struct Node op = {&op_stack[k], &out_stack[-2], &out_stack[-1]};
                    j--;
                    out_stack[j] = op;
                    k--;
                }
                k++;
                op_stack[k] = tokens[i];
                break;

            case END:
                break;
        }

        // debug
        printf("Step: %d\nCurrent: %d\nOp Stack: ", i, tokens[i].type);
        for (int l = 0; l <= k; l++) printf("%d, ", op_stack[l].type);
        printf("\nOut Stack: ");
        for (int l = 0; l <= j; l++) printf("%d, ", out_stack[l].token->type);
        printf("\n\n");

    }

    for (; k > -1; k--) {
        if (op_stack[k].type == LPR) {
            fprintf(stderr, "Error: Mismatched parentheses\n");
            return 1;
        }
        struct Node op = {&op_stack[k], &out_stack[-2], &out_stack[-1]};
        j--;
        out_stack[j] = op;
        k--;
    
        // debug
        printf("Step: Finish\nOp Stack: ");
        for (int l = 0; l <= k; l++) printf("%d, ", op_stack[l].type);
        printf("\nOut Stack: ");
        for (int l = 0; l <= j; l++) printf("%d, ", out_stack[l].token->type);
        printf("\n\n");
    }

    // check if the entire output stack has made it into the tree
    if (j > 0) {
        fprintf(stderr, "Error: Missing operator\n");
        return 1;
    }

    p_top_node = &out_stack[0];

    return 0;
}
