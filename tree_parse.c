#include "tree_parse.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse.h"

int tree_parse_shunting_yard(struct Token* tokens, int len, struct Token** pp_top) {
    // not actual stacks but you get what I mean
    struct Token* op_stack[len];
    struct Token* out_stack[len];
    // j: top of the output stack, k: top of the operator stack
    // -1 indicates an empty stack
    int j = -1, k = -1;
   
    for (int i = 0; tokens[i].type != END; i++) {
        switch (tokens[i].type) {
            case NUM:
            case VAR:
                j++;
                out_stack[j] = &tokens[i];
                break;
            
            case SET:
                // TODO
                break;

            case LPR:
                k++;
                op_stack[k] = &tokens[i];
                break;

            case RPR:
                while (op_stack[k]->type != LPR) {
                    if (k == -1) {
                        fprintf(stderr, "Error: Mismatched parentheses\n");
                        return 1;
                    }
                    op_stack[k]->left = out_stack[-2];
                    op_stack[k]->right = out_stack[-1];
                    j--;
                    out_stack[j] = op_stack[k];
                    k--;
                }
                k--; // discard opening parentheses
                break;

            case OPS:
                while (k > -1 && 
                        op_stack[k]->type == OPS && 
                        op_stack[k]->op_type < tokens[i].op_type) {
                    op_stack[k]->left = out_stack[-2];
                    op_stack[k]->right = out_stack[-1];
                    j--;
                    out_stack[j] = op_stack[k];
                    k--;
                }
                k++;
                op_stack[k] = &tokens[i];
                break;

            case END:
                // this shouldn't happen, but I'll include it to stop GCC from complaining
                break;
        }

        // debug
        printf("Step: %d\nCurrent: %d\nOp Stack: ", i, tokens[i].type);
        for (int l = 0; l <= k; l++) printf("%d, ", op_stack[l]->type);
        printf("\nOut Stack: ");
        for (int l = 0; l <= j; l++) printf("%d, ", out_stack[l]->type);
        printf("\n\n");
    }

    for (; k > -1; k--) {
        if (op_stack[k]->type == LPR) {
            fprintf(stderr, "Error: Mismatched parentheses\n");
            return 1;
        }
        op_stack[k]->left = out_stack[-2];
        op_stack[k]->right = out_stack[-1];
        j--;
        out_stack[j] = op_stack[k];
        k--;
    
        // debug
        printf("Step: Finish\nOp Stack: ");
        for (int l = 0; l <= k; l++) printf("%d, ", op_stack[l]->type);
        printf("\nOut Stack: ");
        for (int l = 0; l <= j; l++) printf("%d, ", out_stack[l]->type);
        printf("\n\n");
    }

    // check if the entire output stack has made it into the tree
    if (j > 0) {
        fprintf(stderr, "Error: Missing operator\n");
        return 1;
    }

    //memcpy(p_top, out_stack[0], sizeof(struct Token));
    *pp_top = out_stack[0];

    return 0;
}
