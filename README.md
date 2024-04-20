# vcc - very cool calculator

A simple terminal-based calculator written in C. It mostly does standard calculator stuff.

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
- Expression caching and option to refer back to previous expression  
    - type `[n]` to include the `n`th expression in the current one  
    - changed variables are interpreted as their new value  
- Type "quit" to quit the program  

### Currently missing features
- Some i/o features:  
    - Editing previous expressions  
    - Using arrow keys to navigate input  
    - Reading from and writing to files  
