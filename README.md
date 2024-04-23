# vcc - very cool calculator

A simple terminal-based calculator written in C. It mostly does standard calculator stuff.

## Instructions

### Compatibility

Only tested on Linux, but should work pretty much everywhere. If it doesn't, please open an issue, or submit a PR if you know how to fix it.

### Installation

For now, just run `make` wherever you downloaded the code and run the program with `./vcc`. To invoke vcc from the command line, you'll have to manually move the binary wherever you keep them. I'll add a configure script and a better makefile eventually.

### Usage

- Run the program using `./vcc` in the directory where you installed it, or `vcc` anywhere if you moved the binary to your binary directory.  
- Recognized operators: `+`, `-`, `*`, `/`, `^`  
- Floating point syntax: Use a period instead of a comma. `.x` is equivalent to `0.x`.  
- Assign variables using `=` (e.g. `a=7`, `b=4.2`, `c=a/4`). Only lowercase letters are permitted.
- Function arguments have to be in parentheses.
- Type `[n]` to include the `n`th expression in the current one. It is treated as if it were in parentheses.  
- Type "quit" to quit the program.  

## Features
- Basic operations  
- Integer and non-integer exponentials  
- Currently implemented functions:
    - `sqrt`  
    - `exp`  
    - `ln` (natural logarithm)  
    - `log` (base 10 logarithm)
    - `sin`
    - `cos`
    - `tan`
    - `asin`
    - `acos`
    - `atan`
- Option to set and use variables (a...z)  
    - Changing a variable also changes all variables that depend on it
- Expression caching and option to refer back to previous expression  
    - Changed variables are interpreted as their new value  

### Currently missing features
- Some i/o features:  
    - Editing previous expressions  
    - Using arrow keys to navigate input  
    - Reading from and writing to files  
- A better Makefile and configure script
- A `--help` option and man pages

## Contributing

Contributions are welcome, but keep in mind that this is just the hobby project of a college kid with enough to do already. Please be patient and keep PRs to a manageable size.
