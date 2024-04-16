#include "calc.h"

#include <string.h>

#include "parse.h"

double calc_recursive(char* input) {
    char* slice1[strlen(input)];
    char* slice2[strlen(input)];
    int op;

    // parse returns 0 if it finishes in its initial state, meaning either side is a number
    if (parse(input, slice1, slice2, &op))
        // TODO: I have no idea what I'm doing
        double res1 = calc_recursive(slice1);
        double res2 = calc_recursive(slice1);
    
    double res = calc_do_op(parse_to_num(slice1), parse_to_num(slice2), op);

    return res;
}

double calc_do_op(double n1, double n2, int op) {
    switch (op) {
        case ADD:
            return n1 + n2;
        case SUB:
            return n1 - n2;
        case MUL:
            return n1 * n2;
        case DIV:
            return n1 / n2;
        case POW: // TODO
            return n1 + n2;
    }
    return 0;
}
