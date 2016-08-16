word2vec2annoy
====================

Loads pretrained word2vec models into Annoy for fast searching.

[word2vec](https://code.google.com/p/word2vec/) is neat! You can do things like add the vector for "king" to the vector for "woman" to get the vector for "queen"! Unfortunately, it doesn't give you a way to do that search for the "queen" vector. Once you add the two vectors, you're on your own if you want to find the vector that's closest to an arbitrary sum vector.

Fortunately, there's a lot of libraries out there that implement an [approximate nearest neighbor](https://en.wikipedia.org/wiki/Nearest_neighbor_search#Approximate_nearest_neighbor) search algorithm. [Annoy](https://github.com/spotify/annoy) is one of them. It has these particularly appealing features:

> Annoy also decouples creating indexes from loading them, so you can pass around indexes as files and map them into memory quickly. Another nice thing of Annoy is that it tries to minimize memory footprint so the indexes are quite small.

This utility is intended to get you up and running quickly with word2vec by building an Annoy index using a word2vec pre-trained model binary (a binary file containing vectors for a bunch of words). It uses code from the really nice [convertvec](https://github.com/marekrei/convertvec) to read the binary, and uses what it reads to build an Annoy index, as well as a mapping of words to Annoy indexes (integers) for easy lookup.

Usage
-----

Build:

	make build-annoy

TODO: Explain how to read from the Annoy index and how to use it to run searches.

TODO: Add target for setting up tests/data.

Test
----

    make test
