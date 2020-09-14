all: pqueue.o program.o
	gcc program.o pqueue.o -o program -lm
pqueue.o: pqueue.c
	gcc pqueue.c -c
program.o: program.c compress.c decompress.c
	gcc program.c -c

