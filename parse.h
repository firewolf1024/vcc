#ifndef PARSE_H
#define PARSE_H

#include "token.h"

int parse_tokenize(char* input, struct Expression* expr);

int parse_shunting_yard(struct Expression* expr);

#endif
