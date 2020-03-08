CC=g++

test: mem test.py
	python test.py

mem: main.o mem.o 
	$(CC) -o mem main.o mem.o

main.o: main.cpp mem.h
	$(CC) -c main.cpp

mem.o: mem.cpp mem.h
	$(CC) -c mem.cpp

clean:
	rm -rf *.o mem