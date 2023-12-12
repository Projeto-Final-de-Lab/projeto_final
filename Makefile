all: prog.exe

prog.exe: main.o functions/leitura.o functions/filtro.o
	gcc -o prog.exe main.o functions/leitura.o functions/filtro.o

main.o: main.c
	gcc -o main.o -c main.c

functions/leitura.o: functions/leitura.c
	gcc -o functions/leitura.o -c functions/leitura.c

functions/filtro.o: functions/filtro.c
	gcc -o functions/filtro.o -c functions/filtro.c

clean:
	rm -f *.o prog.exe functions/*.o