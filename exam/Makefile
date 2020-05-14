CC=g++
FLAG=-std=c++17 -O3

test: sum
	./sum

sum: main.o sum.o
	$(CC) $(FLAG) -o sum main.o sum.o

main.o: main.cpp sum.h
	$(CC) $(FLAG) -c main.cpp

sum.o: sum.cpp sum.h pool.h
	$(CC) $(FLAG) -c sum.cpp

clean:
	rm -rf *.o sum