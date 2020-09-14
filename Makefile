all: list.o program.o compress.o decompress.o tree.o
	gcc program.o list.o compress.o decompress.o tree.o -o program
list.o: list.c
	gcc list.c -c
program.o: program.c 
	gcc program.c -c
compress.o: compress.c list.h
	gcc compress.c -c
decompress.o: decompress.c list.h
	gcc decompress.c -c
tree.o: tree.c
	gcc tree.c -c

