all: exec

exec: main.o move.o map.o game.o filebestscore.o
	gcc main.o move.o map.o game.o filebestscore.o -o exec

main.o: main.c fonction.h
	gcc -c main.c -o main.o

move.o: move.c fonction.h
	gcc -c move.c -o move.o

map.o: map.c fonction.h
	gcc -c map.c -o map.o

game.o: game.c fonction.h
	gcc -c game.c -o game.o

filebestscore.o: FileBestScores.c fonction.h
	gcc -c FileBestScores.c -o filebestscore.o

clean:
	rm -f *.o
	rm -f exec
