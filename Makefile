calc: main.c token.h parse.c parse.h eval.c eval.h test.c test.h
	clear
	gcc -o calc main.c parse.c eval.c test.c -Wall -g -lm
