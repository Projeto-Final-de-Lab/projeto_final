all: prog.e

prog.e: main.o functions/leitura.o functions/filtro.o
	gcc -o prog.e main.o functions/leitura.o functions/filtro.o functions/scm.o

main.o: main.c
	gcc -o main.o -c main.c

functions/leitura.o: functions/leitura.c
	gcc -o functions/leitura.o -c functions/leitura.c

functions/filtro.o: functions/filtro.c
	gcc -o functions/filtro.o -c functions/filtro.c

functions/scm.o: functions/scm.o.c
	gcc -o functions/scm.o -c functions/scm.c

clean:
	rm -f *.o prog.e functions/*.o