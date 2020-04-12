CC=g++
FLAG=-std=c++17

test: format
	./format

format: main.o
	$(CC) $(FLAG) -o format main.o

main.o: main.cpp format.h
	$(CC) $(FLAG) -c main.cpp

clean:
	rm -rf *.o format