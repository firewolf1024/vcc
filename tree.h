#ifndef TREE_H
#define TREE_H

#include "parse.h"

struct Node {
    struct Token* token;
    struct Node* left;
    struct Node* right;
};

#endif
