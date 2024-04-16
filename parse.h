#ifndef PARSE_H
#define PARSE_H

#include "token.h"

int parse_tokenize(char* input, struct Token* tokens);

int parse_shunting_yard(struct Token* tokens, int len);

#endif
