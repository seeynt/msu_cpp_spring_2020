CC=g++
FLAG=-std=c++17

test: BigInt test.py
	./BigInt

BigInt: main.o BigInt.o 
	$(CC) $(FLAG) -o BigInt main.o BigInt.o

main.o: main.cpp BigInt.h
	$(CC) $(FLAG) -c main.cpp

BigInt.o: BigInt.cpp BigInt.h
	$(CC) $(FLAG) -c BigInt.cpp

clean:
	rm -rf *.o BigInt