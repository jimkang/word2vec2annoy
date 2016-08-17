# CC = gcc
CC = g++
CFLAGS = -lm -pthread -Ofast -march=native -Wall -funroll-loops -Wno-unused-result
TESTDATADIR = tests/data

all: build-annoy

build-annoy:
	g++ precision_test.cpp -o precision_test -std=c++11

tests/basic-test:
	$(CC) tests/basic-test.c -o tests/basic-test $(CFLAGS)

rebuild-test:
	rm -f tests/basic-test
	$(CC) tests/basic-test.c -o tests/basic-test $(CFLAGS)

test: rebuild-test tests/data/text8-vector.bin
	cd tests && ./basic-test

tests/data/text8-vector.bin:
	wget https://dl.dropboxusercontent.com/u/263768/text8-vector.bin -O $(TESTDATADIR)/text8-vector.bin
