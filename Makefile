all: main.exe
	./main.exe

graph.o: graph/graph.c graph/graph.h
	gcc -c ./graph/graph.c -o graph.o

object.o: object/object.c object/object.h
	gcc -c ./object/object.c -o object.o

main.exe: graph.o object.o main.c
	gcc main.c graph.o object.o -o main.exe

clean:
	rm -rf *.o *.out 
	