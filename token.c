#include "token.h"

#include <stdlib.h>

void free_expr(struct Expresssion expr) {
    free(expr.tokens);
    free(&expr);
}
