all: 
	gcc -c funcoes.c
	gcc -c filtros.c
	gcc -c main.c
	gcc -o editor funcoes.o filtros.o main.o

