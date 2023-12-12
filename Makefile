all: prog.e

prog.e: main.o functions/leitura.o functions/func.o
	gcc -o prog.e main.o functions/leitura.o functions/func.o

main.o: main.c
	gcc -o main.o -c main.c

functions/leitura.o: functions/leitura.c
	gcc -o functions/leitura.o -c functions/leitura.c

functions/func.o: functions/func.c
	gcc -o functions/func.o -c functions/func.c


clean: 
	rm -f *.o prog.e functions/*.o