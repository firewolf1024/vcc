#ifndef TOKEN_H
#define TOKEN_H

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

// capable of forming a binary tree
struct Token {
    enum Token_Types type;
    union {
        long op_type; // so they occupy the same amount of space
        double value;
    };
    struct Token* left;
    struct Token* right;
};

#endif
