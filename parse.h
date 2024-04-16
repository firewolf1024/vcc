#ifndef PARSE_H
#define PARSE_H

enum Token_Types {
    NUM,
    VAR,
    SET,
    OPS,
    LPR,
    RPR,
    END
};

// sorted by precedence for the shunting yard algorithm
enum Op_Types {
    POW,
    DIV,
    MUL,
    SUB,
    ADD
};

struct Token {
    enum Token_Types type;
    union {
        long op_type; // so they occupy the same amount of space
        double value;
    };
};

int parse_tokenize(char* input, struct Token* tokens);

int parse_shunting_yard(struct Token* tokens, int len);

#endif
