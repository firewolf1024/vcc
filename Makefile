CFILES = main.c parse.c eval.c
HFILES = token.h parse.h eval.h
FLAGS = -Wall -g -lm

calc: $(CFILES) $(HFILES)
	clear
	gcc -o vcc $(CFILES) $(FLAGS)

test: $(CFILES) $(HFILES) test.c test.h
	clear
	gcc -o calc $(CFILES) test.c $(FLAGS)

clean:
	rm vcc
