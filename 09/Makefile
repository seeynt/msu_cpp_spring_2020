CC=g++
FLAG=-std=c++17 -O3

test: sort
	./sort

sort: main.o
	$(CC) $(FLAG) -o sort main.o

main.o: main.cpp sort_.h
	$(CC) $(FLAG) -c main.cpp

clean:
	rm -rf *.o sort test5 test6 sorted_test1 sorted_test2 sorted_test3 sorted_test4 sorted_test5 sorted_test6