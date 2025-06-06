all: main.exe
	./main.exe

graph.o: graph/graph.c graph/graph.h
	gcc -c ./graph/graph.c -o graph.o

object.o: object/object.c object/object.h
	gcc -c ./object/object.c -o object.o

pathFinding.o: path-finding/pathFinding.c path-finding/pathFinding.h
	gcc -c ./path-finding/pathFinding.c -o pathFinding.o

main.exe: graph.o object.o pathFinding.o main.c
	gcc main.c graph.o object.o pathFinding.o -o main.exe

clean:
	del *.exe *.o
	