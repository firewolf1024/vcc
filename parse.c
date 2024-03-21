#include "parse.h"

#include <stdio.h>
#include <unistd.h>

#include "ops.h"

int parse(char* input, int* nums, int* op) {
    // TODO: There surely is a faster way (use regular expressions, maybe?)
    int num_index = 0;

    for (int i = 0; input[i] != '\n'; i++) {
        switch (input[i]) {
            case 48 ... 57:
                nums[num_index] *= 10;
                nums[num_index] += input[i] - 48; 
                break;
            case 43:
                *op = ADD;
                num_index++;
                break;
            case 45:
                *op = SUB;
                num_index++;
                break;
            case 42:
                *op = MUL;
                num_index++;
                break;
            case 47:
                *op = DIV;
                num_index++;
                break;
            case 94:
                *op = POW;
                num_index++;
                break;
            default:
                fprintf(stderr, "Syntax error: illegal character '%d'\n", input[i]);
                return -1;
        }
    }

    return 0;
} 
