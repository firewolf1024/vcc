#include "calc.h"

#include "ops.h"
#include "parse.h"

int calc_recursive(char* input) {
    int nums[2] = {0, 0};
    int op;
    parse(input, nums, &op);
    int res = calc_do_op(nums[0], nums[1], op);
    return res;
}

int calc_do_op(int n1, int n2, int op) {
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
        case FAC: // TODO
            return n1 + n2;
    }
    return 0;
}
