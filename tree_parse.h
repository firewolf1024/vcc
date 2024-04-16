#ifndef TREE_PARSE_H
#define TREE_PARSE_H

#include "tree.h"
#include "parse.h"

int tree_parse_shunting_yard(struct Token* tokens, int len, struct Node* p_top_node);

#endif
