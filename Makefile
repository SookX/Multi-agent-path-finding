all: main.exe
	./main.exe

graph.o: graph/graph.c graph/graph.h
	gcc -c ./graph/graph.c -o graph.o

main.exe: graph.o main.c
	gcc main.c graph.o -o main.exe

clean:
	rm -rf *.o *.out 
	