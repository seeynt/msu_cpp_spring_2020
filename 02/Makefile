CC=g++
FLAG=-std=c++11

test: parcer test.py
	python test.py

parcer: main.o parcer.o 
	$(CC) $(FLAG) -o parcer main.o parcer.o

main.o: main.cpp parcer.h
	$(CC) $(FLAG) -c main.cpp

parcer.o: parcer.cpp parcer.h
	$(CC) $(FLAG) -c parcer.cpp

clean:
	rm -rf *.o parcer