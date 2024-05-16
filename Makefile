all: exec

exec: main.o move.o map.o game.o
	gcc main.o move.o map.o game.o -o exec

main.o: main.c fonction.h
	gcc -c main.c -o main.o

move.o: move.c fonction.h
	gcc -c move.c -o move.o

map.o: map.c fonction.h
	gcc -c map.c -o map.o

game.o: game.c fonction.h
	gcc -c game.c -o game.o

clean:
	rm -f *.o
	rm -f exec
