#ifndef TOKEN_H
#define TOKEN_H

enum Token_Types {
    NUM,
    SGN,
    VAR,
    SET,
    FUN,
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

enum Fn_Types {
    SQRT,
    EXP,
    LN,
    SIN,
    COS
};

// capable of forming a binary tree
struct Token {
    enum Token_Types type;
    union {
        enum Op_Types op_type;
        enum Fn_Types fn_type;
        double value;
        char name;
    };
    struct Token* left;
    struct Token* right;
};

struct Expression {
    struct Token* tokens;
    struct Token* p_top;
    int len;
};

#endif
