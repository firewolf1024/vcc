#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "eval.h"
#include "parse.h"
#include "test.h"
#include "token.h"

int main(int argc, char* argv[]) {
    char vars[26];
    struct Token* func_cache = NULL;
    int cache_top = 0;
    char quit_symbol = 'q';

    printf("vcc (very cool calculator)\ntype %c to quit\n", quit_symbol);
    
    while (1) {
        // getting the input
        char* input = NULL;
        size_t size;

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

        // updating the function cache (tokens will be directly written into here)
        struct Token* tmp_func_cache = realloc(func_cache,
                (cache_top + len) * sizeof(struct Token));
        if (tmp_func_cache == NULL) {
            fprintf(stderr, "Error: failed to reallocate memory");
        } else {
            func_cache = tmp_func_cache;
            free(tmp_func_cache);
        }

        // input parsing
        if (parse_tokenize(input, &func_cache[cache_top]))
            continue;

        free(input);

        struct Token* p_top; // will point to the top of the tree once it's assembled

        if (parse_shunting_yard(&func_cache[cache_top], len, &p_top))
            continue;

        // the math happens here
        printf("%f\n", eval(p_top, vars));
        cache_top += len;
    }
}
