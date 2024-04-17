#include "parse.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"

int parse_tokenize(char* input, struct Token* tokens) {
    int i = 0, j = 0; // i: input index, j: token list index

    // TODO: wouldn't it be more elegant to use the END token as a stop condition?
    for (; i < strlen(input); i++) {
        switch (input[i]) {
            case '0' ... '9':
                tokens[j].type = NUM;
                for (; input[i] <= '9' && input[i] >= '0'; i++) {
                    tokens[j].value *= 10;
                    tokens[j].value += input[i] - '0';
                    // TODO: decimal point and negative number support
                }
                i--;
                break;
            
            case '=':
                tokens[j].type = SET;
                break;
          
            case '(':
                tokens[j].type = LPR;
                break;

            case ')':
                tokens[j].type = RPR;
                break;

            case '+':
                tokens[j].type = OPS;
                tokens[j].op_type = ADD;
                break;
            
            case '-':
                tokens[j].type = OPS;
                tokens[j].op_type = SUB;
                break;
            
            case '*':
                tokens[j].type = OPS;
                tokens[j].op_type = MUL;
                break;
            
            case '/':
                tokens[j].type = OPS;
                tokens[j].op_type = DIV;
                break;
            
            case '^':
                tokens[j].type = OPS;
                tokens[j].op_type = POW;
                break;
           
            case 'A' ... 'Z':
            case 'a' ... 'z':
                tokens[j].type = VAR;
                tokens[j].value = input[i];
                // TODO: make variables work
                break;
           
            case '\n':
                tokens[j].type = END;
                break;

            default:
                fprintf(stderr, "Error: unknown token %c\n", input[i]);
                return 1;
        }
        
        j++;
    }
    
    return 0;
}

int parse_shunting_yard(struct Token* tokens, int len, struct Token** pp_top) {
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
                out_stack[j]->left = NULL;
                out_stack[j]->right = NULL;
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
                    op_stack[k]->left = out_stack[j-1];
                    op_stack[k]->right = out_stack[j];
                    j--;
                    out_stack[j] = op_stack[k];
                    k--;
                }
                k--; // discard opening parentheses
                break;

            case OPS:
                while (k > -1 && 
                        op_stack[k]->type == OPS && 
                        (op_stack[k]->op_type < tokens[i].op_type ||
                        (op_stack[k]->op_type == tokens[i].op_type &&
                        op_stack[k]->op_type % 2))) { // Op types 1 and 3 are left-associative
                    if (j < 1) {
                        fprintf(stderr, "Error: Missing operand\n");
                        return 1;
                    }
                    op_stack[k]->left = out_stack[j-1];
                    op_stack[k]->right = out_stack[j];
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
    }

    for (; k > -1; k--) {
        if (op_stack[k]->type == LPR) {
            fprintf(stderr, "Error: Mismatched parentheses\n");
            return 1;
        }
        
        if (j < 1) {
            fprintf(stderr, "Error: Missing operand\n");
            return 1;
        }

        op_stack[k]->left = out_stack[j-1];
        op_stack[k]->right = out_stack[j];
        j--;
        out_stack[j] = op_stack[k];
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
