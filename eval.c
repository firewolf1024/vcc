#include "eval.h"

#include <math.h>

#include "token.h"

double eval(struct Token* p_top) {
    if (p_top->type == OPS) {
        switch (p_top->op_type) {
            case ADD:
                return eval(p_top->left) + eval(p_top->right);
                break;
            case SUB:
                return eval(p_top->left) - eval(p_top->right);
                break;
            case MUL:
                return eval(p_top->left) * eval(p_top->right);
                break;
            case DIV:
                return eval(p_top->left) / eval(p_top->right);
                break;
            case POW:
                return powl(eval(p_top->left), eval(p_top->right));
                break;
            default:
                // There you go, GCC
                return 0;
                break;
        }
    } else {
        return p_top->value;
    }
}
