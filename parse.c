#include "parse.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int parse_shunting_yard(struct Token* tokens, int len) {
    // i: top of token stack, j: top of output stack, k: top of the operator stack
    // -1 indicates an empty stack
    int i = -1, j = -1, k = -1;
    struct Token op_stack[len];

    for (; tokens[i].type != END; ++i) {
        switch (tokens[i].type) {
            case NUM:
            case VAR:
                j++;
                tokens[j] = tokens[i];
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
                    j++;
                    tokens[j] = op_stack[k];
                    k--;
                }
                k--; // discard opening parentheses
                break;

            case OPS:
                while (k > -1 && 
                        op_stack[k].type == OPS && 
                        op_stack[k].op_type < tokens[i].op_type) {
                    j++;
                    tokens[j] = op_stack[k];
                    k--;
                }
                k++;
                op_stack[k] = tokens[i];
                break;

            case END:
                break;
        }
    }

    for (; k > -1; k--) {
        if (op_stack[k].type == LPR) {
            fprintf(stderr, "Error: Mismatched parentheses\n");
            return 1;
        }
        j++;
        tokens[j] = op_stack[k];
    }
    tokens[j++].type = END;
    return 0;
}
