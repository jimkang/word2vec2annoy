# CC = gcc
CC = g++
CFLAGS = -lm -pthread -Ofast -march=native -Wall -funroll-loops -Wno-unused-result

all: build-annoy

build-annoy:
	g++ precision_test.cpp -o precision_test -std=c++11

tests/basic-test:
	$(CC) tests/basic-test.c -o tests/basic-test $(CFLAGS)

rebuild-test:
	rm -f tests/basic-test
	$(CC) tests/basic-test.c -o tests/basic-test $(CFLAGS)

test: rebuild-test
	cd tests && ./basic-test
