a.out: main.o
	g++ main.o

main.o: main.cpp onegin.h
	g++ -c main.cpp -o main.o
