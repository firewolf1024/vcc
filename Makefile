calc: main.c parse.c test.c
	clear
	gcc -o calc main.c parse.c test.c -Wall -g
