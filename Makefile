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
	./basic-test data/text8-vector.bin test-word-index.txt test-annoy.tree 10 \
	big dog

tests/data/text8-vector.bin:
	wget https://dl.dropboxusercontent.com/u/263768/text8-vector.bin -O $(TESTDATADIR)/text8-vector.bin

big-test: tests/basic-test
	cd tests && \
	./basic-test ../../word2vec/GoogleNews-vectors-negative300.bin \
		big-word-index.txt big-annoy.tree 100 \
		king woman

tools/get-dimensions-in-vector-bin:
	$(CC) tools/get-dimensions-in-vector-bin.c -o tools/get-dimensions-in-vector-bin $(CFLAGS)

tools/add-vectors:
	$(CC) tools/add-vectors.c -o tools/add-vectors $(CFLAGS)

tools/w2v-to-json:
	$(CC) tools/w2v-to-json.c -o tools/w2v-to-json $(CFLAGS)
