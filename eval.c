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
            return vars[(int) p_top->name - 'a'];
        
        case SET:
            double val = eval(p_top->right, vars);
            vars[p_top->left->name - 'a'] = val;
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
        
        case FUN:
            switch (p_top->fn_type) {
                case SQRT:
                    return sqrt(eval(p_top->left, vars));
                case EXP:
                    return exp(eval(p_top->left, vars));
                case LN:
                    return log(eval(p_top->left, vars));
                case SIN:
                    return sin(eval(p_top->left, vars));
                case COS:
                    return cos(eval(p_top->left, vars));
            }
        
        case OLD:
            return eval(p_top->left, vars);

        default:
            return 0;
    }
}
