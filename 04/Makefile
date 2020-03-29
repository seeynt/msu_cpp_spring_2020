CC=g++
FLAG=-std=c++17

test: serializer
	./serializer

serializer: main.o 
	$(CC) $(FLAG) -o serializer main.o

main.o: main.cpp serializer.h
	$(CC) $(FLAG) -c main.cpp

clean:
	rm -rf *.o matrix