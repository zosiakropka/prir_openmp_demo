all: matrix

matrix: objects/matrix.o
	g++ -Wall -fopenmp objects/matrix.o -o matrix

objects/matrix.o: src/matrix.cpp
	gcc -c -Wall -fopenmp src/matrix.cpp -o objects/matrix.o

clean:
	-rm matrix
	-rm objects/*
	-rm output/*
