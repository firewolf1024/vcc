calc: main.c calc.c parse.c
	clear
	gcc -o calc main.c calc.c parse.c -Wall -g
