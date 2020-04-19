CC=g++
FLAG=-std=c++17

test: vector
	./vector

vector: main.o
	$(CC) $(FLAG) -o vector main.o

main.o: main.cpp vector.h allocator.h iterator.h
	$(CC) $(FLAG) -c main.cpp

clean:
	rm -rf *.o vector