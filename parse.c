#include "parse.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"

int parse_tokenize(char* input, struct Expression* expr) {
    struct Token* tokens = expr->tokens;
    int i = 0, j = 0; // i: input index, j: token list index
    int end = 0;

    for (; !end; i++) {
        switch (input[i]) {
            case '0' ... '9':
                tokens[j].type = NUM;
                for (; input[i] <= '9' && input[i] >= '0'; i++) {
                    tokens[j].value *= 10;
                    tokens[j].value += input[i] - '0';
                }
                i--;
                break;
           
            case '.':
                double dec = 0;
                i++;
                for (; input[i] <= '9' && input[i] >= '0'; i++) {
                    dec += input[i] - '0';
                    dec /= 10;
                }
                i--;

                if (tokens[j-1].type == NUM) {
                    j--;
                    tokens[j].value += dec;
                } else {
                    tokens[j].type = NUM;
                    tokens[j].value = dec;
                }
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
                if (j == 0 || tokens[j-1].type == LPR || tokens[j-1].type == SET) {
                    tokens[j].type = SGN;
                } else {
                    tokens[j].type = OPS;
                    tokens[j].op_type = SUB;
                }
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
           
            case 'a' ... 'z':
                if (input[i+1] >= 'a' && input[i+1] <= 'z') {
                    char name[expr->len - i];
                    for (int l = i; input[i] >= 'a' && input[i] <= 'z'; i++) {
                        name[i - l] = input[i];
                    }

                    if (!strcmp(name, "quit")) {
                        if (j > 0) {
                            fprintf(stderr, "Error: cannot use quit token in expression\n");
                            return 1;
                        } else {
                            return 2;
                        }
                    }

                    if (input[i] != '(') {
                        fprintf(stderr, "Error: missing function body\n");
                        return 1;
                    }
                    
                    tokens[j].type = FUN;
                    if (!strcmp(name, "sqrt"))
                        tokens[j].fn_type = SQRT;
                    else if (!strcmp(name, "exp"))
                        tokens[j].fn_type = EXP;
                    else if (!strcmp(name, "ln"))
                        tokens[j].fn_type = LN;
                    else if (!strcmp(name, "sin"))
                        tokens[j].fn_type = SIN;
                    else if (!strcmp(name, "cos"))
                        tokens[j].fn_type = COS;
                    else {
                        fprintf(stderr, "Error: unknown function %s\n", name);
                        return 1;
                    }
                    i--;
                
                } else {
                    tokens[j].type = VAR;
                    tokens[j].name = input[i];
                }
                break;
           
            case '\n':
                tokens[j].type = END;
                end = 1;
                break;

            default:
                fprintf(stderr, "Error: unknown token %c\n", input[i]);
                return 1;
        }
        
        j++;
    }
    
    return 0;
}

int parse_shunting_yard(struct Expression* expr) {
    // not actual stacks but you get what I mean
    struct Token* op_stack[expr->len];
    struct Token* out_stack[expr->len];
    struct Token* tokens = expr->tokens;
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
           
            case SGN:
            case SET:
            case FUN:
            case LPR:
                k++;
                op_stack[k] = &tokens[i];
                break;

            case RPR:
                while (op_stack[k]->type != LPR) {
                    if (k == -1) {
                        fprintf(stderr, "Error: Mismatched parentheses\n");
                        return 1;
                    } else if (op_stack[k]->type == OPS || op_stack[k]->type == SET) {
                        op_stack[k]->left = out_stack[j-1];
                        op_stack[k]->right = out_stack[j];
                        j--;
                        out_stack[j] = op_stack[k];
                        k--;
                    } else {
                        op_stack[k]->left = out_stack[j];
                        out_stack[j] = op_stack[k];
                        k--;
                    }
                }
                k--; // discard opening parentheses

                if (op_stack[k]->type == FUN) {
                    op_stack[k]->left = out_stack[j];
                    out_stack[j] = op_stack[k];
                    k--;
                }

                break;
                
            case OPS:
                // there should only be one sign (unless the tokenizer fucked up somehow)
                if (k > -1 && op_stack[k]->type == SGN) {
                    op_stack[k]->left = out_stack[j];
                    out_stack[j] = op_stack[k];
                    k--;
                }

                for (; k > -1 && 
                        (op_stack[k]->type == OPS && 
                        (op_stack[k]->op_type < tokens[i].op_type ||
                        (op_stack[k]->op_type == tokens[i].op_type &&
                        op_stack[k]->op_type % 2))); // op types 1 and 3 are left-associative
                        k--) {
                    if (j < 1) {
                        fprintf(stderr, "Error: Missing operand\n");
                        return 1;
                    }
                    op_stack[k]->left = out_stack[j-1];
                    op_stack[k]->right = out_stack[j];
                    j--;
                    out_stack[j] = op_stack[k];
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
        
        } else if (op_stack[k]->type == OPS || op_stack[k]->type == SET) {
            if (j < 1) {
                fprintf(stderr, "Error: Missing operand\n");
                return 1;
            }

            op_stack[k]->left = out_stack[j-1];
            op_stack[k]->right = out_stack[j];
            j--;
            out_stack[j] = op_stack[k];

        } else {
            op_stack[k]->left = out_stack[j];
            out_stack[j] = op_stack[k];
        }
    }

    // check if the entire output stack has made it into the tree
    if (j > 0) {
        fprintf(stderr, "Error: Missing operator\n");
        return 1;
    }

    //memcpy(p_top, out_stack[0], sizeof(struct Token));
    expr->p_top = out_stack[0];

    return 0;
}
