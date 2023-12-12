# Use as opções apropriadas para o MinGW no Windows
CC = gcc
CFLAGS = -Wall

all: prog.exe

prog.exe: main.o functions/leitura.o functions/filtro.o functions/scm.o
	$(CC) -o prog.exe main.o functions/leitura.o functions/filtro.o functions/scm.o

main.o: main.c
	$(CC) $(CFLAGS) -o main.o -c main.c

functions/leitura.o: functions/leitura.c
	$(CC) $(CFLAGS) -o functions/leitura.o -c functions/leitura.c

functions/filtro.o: functions/filtro.c
	$(CC) $(CFLAGS) -o functions/filtro.o -c functions/filtro.c

functions/scm.o: functions/scm.c
	$(CC) $(CFLAGS) -o functions/scm.o -c functions/scm.c

clean:
	del *.o prog.exe functions\*.o
