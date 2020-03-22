CC=g++
FLAG=-Wall

test: matrix
	./matrix

matrix: matrix.o main.o 
	$(CC) $(FLAG) -o matrix main.o matrix.o

main.o: main.cpp matrix.h
	$(CC) $(FLAG) -c main.cpp

matrix.o: matrix.cpp matrix.h
	$(CC) $(FLAG) -c matrix.cpp

clean:
	rm -rf *.o matrix