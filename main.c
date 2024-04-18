#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "eval.h"
#include "parse.h"
#include "test.h"
#include "token.h"

int main(int argc, char* argv[]) {
    char vars[26];
    struct Expression* expr_cache = malloc(sizeof(struct Expression) * 2);
    int cache_size = 2;
    int n_expr = 0;
    char quit_symbol = 'q';

    printf("vcc (very cool calculator)\ntype %c to quit\n", quit_symbol);
    
    while (1) {
        // getting the input
        char* input = NULL;
        size_t size;

        printf("[%d] ", n_expr);

        if (getline(&input, &size, stdin) == -1) {
            fprintf(stderr, "Error getting input\n");
            continue;
        }

        int len = strlen(input);
        
        if (input[0] == quit_symbol) {
            if (len > 2) {
                fprintf(stderr, "Error: quit symbol cannot be used in a formula\n");
                continue;
            } else {
                return 0;
            }
        }

        struct Expression expr;
        expr.tokens = malloc(sizeof(struct Token) * len);
        expr.p_top = &expr.tokens[0];
        expr.len = len;

        if (n_expr >= cache_size) {
            struct Expression* new_expr_cache = realloc(expr_cache, 
                (n_expr * 3 / 2) * sizeof(struct Expression));
            if (!new_expr_cache) {
                fprintf(stderr, "Error: failed to reallocate memory");
                continue;
            } else {
                expr_cache = new_expr_cache;
                expr_cache[n_expr] = expr;
                cache_size *= 1.5;
            }
        }

        // input parsing
        if (parse_tokenize(input, &expr))
            continue;

        if (parse_shunting_yard(&expr))
            continue;

        // the math happens here
        printf("%f\n", eval(expr.p_top, vars));
        n_expr++;
        
        free(input);
    }
    
    for (int i = 0; i < n_expr; i++) {
        free_expr(expr_cache[i]);
    }
    free(expr_cache);
    free(vars);
}
