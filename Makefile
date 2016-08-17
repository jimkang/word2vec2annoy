CC = g++
CFLAGS = -lm -pthread -Ofast -march=native -Wall -funroll-loops -Wno-unused-result -std=c++11
TESTDATADIR = tests/data

tests/basic-test:
	$(CC) tests/basic-test.c -o tests/basic-test $(CFLAGS)

rebuild-test:
	rm -f tests/basic-test
	$(CC) tests/basic-test.c -o tests/basic-test $(CFLAGS)

test: rebuild-test tests/data/text8-vector.bin
	cd tests && \
	./basic-test data/text8-vector.bin test-word-index.txt test-annoy.tree \
	big dog

tests/data/text8-vector.bin:
	wget https://dl.dropboxusercontent.com/u/263768/text8-vector.bin -O $(TESTDATADIR)/text8-vector.bin
