all: prog.e

 prog.e: main.o leitura.o
	gcc -o prog.e main.o leitura.o

main.o: main.c
	gcc -o main.o -c main.c

leitura.o: leitura.c
	gcc -o leitura.o -c leitura.c

clean:
	rm -f *.o prog.e