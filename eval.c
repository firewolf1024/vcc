#include "eval.h"

#include <math.h>
#include <stdio.h>

#include "token.h"

double eval(struct Token* p_top, char* vars) {
    switch (p_top->type) {
        case NUM:
            return p_top->value;
        
        case SGN:
            return eval(p_top->left, vars) * -1;
        
        case VAR:
            return vars[(int) p_top->value - 'a'];
        
        case SET:
            double val = eval(p_top->right, vars);
            vars[(int) p_top->left->value - 'a'] = val;
            printf("value %lf assigned to variable %c (index %d)\n",
                    val,
                    (int) p_top->left->value,
                    (int) p_top->left->value - 'a');
            return val;
        
        case OPS:
            switch (p_top->op_type) {
                case ADD:
                    return eval(p_top->left, vars) + eval(p_top->right, vars);
                    break;
                
                case SUB:
                    return eval(p_top->left, vars) - eval(p_top->right, vars);
                    break;
                
                case MUL:
                    return eval(p_top->left, vars) * eval(p_top->right, vars);
                    break;
                
                case DIV:
                    return eval(p_top->left, vars) / eval(p_top->right, vars);
                    break;
                
                case POW:
                    return powl(eval(p_top->left, vars), eval(p_top->right, vars));
                    break;
                
                default:
                    // There you go, GCC
                    return 0;
            }
        
        default:
            return 0;
    }
}
