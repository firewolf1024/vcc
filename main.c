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

    printf("vcc (very cool calculator)\n");
    
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
        
        struct Expression expr;
        expr.tokens = malloc(sizeof(struct Token) * len);
        expr.p_top = &expr.tokens[0];
        expr.len = len;

        // input parsing
        switch (parse_tokenize(input, &expr)) {
            case 1:
                continue;
            case 2:
                return 0;
            default:
                break;
        }

        if (parse_shunting_yard(&expr, &expr_cache, n_expr))
            continue;

        //test_print_tree(expr.p_top); // debug

        if (n_expr >= cache_size) {
            struct Expression* new_expr_cache = realloc(expr_cache, 
                (n_expr * 3 / 2) * sizeof(struct Expression));
            if (!new_expr_cache) {
                fprintf(stderr, "Error: failed to reallocate memory");
                continue;
            } else {
                expr_cache = new_expr_cache;
                cache_size *= 1.5;
            }
        }
        expr_cache[n_expr] = expr;
       
        // the math happens here
        printf("%f\n", eval(expr.p_top, vars));
        
        free(input);
        n_expr++;
    }

    for (int i = 0; i < n_expr; i++) {
        free(&expr_cache[i].tokens);
        free(&expr_cache[i]);
    }
    free(expr_cache);
    free(vars);
}
