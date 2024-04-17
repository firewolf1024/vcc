calc: main.c parse.c eval.c test.c
	clear
	gcc -o calc main.c parse.c eval.c test.c -Wall -g -lm
