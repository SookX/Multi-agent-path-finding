all: main.exe
	./main.exe

graph.o: graph/graph.c graph/graph.h
	gcc -c ./graph/graph.c -o graph.o

main.exe: graph.o main.c
	gcc main.c graph.o -o main.exe

clean:
	del /Q *.o *.exe 2>nul
	