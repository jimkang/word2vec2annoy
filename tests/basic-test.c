#include "../w2v-to-annoy.h"
#include "../load-from-annoy-by-word.h"
#include <string>
#include <vector>
#include <assert.h>

char testBinPath[] = "data/text8-vector.bin";
char testIndexPath[] = "test-index.txt";
char testAnnoyPath[] = "test-annoy.tree";

char testWord[] = "platypus";

void printVector(float *vector, int dimensions) {
  for (int i = 0; i < dimensions; ++i) {
    printf("%f, ", vector[i]);
  }
}

void testFindingNeighbor() {
  // get two indexes by word
  // get vectors for those indexes
  // add those vectors
  // get nns for the sum
}

int main(int argc, char **argv) {
  long long dimensions;
  w2vToAnnoy(testBinPath, testIndexPath, testAnnoyPath, &dimensions);

  float loadedVector[dimensions];

  if (loadFromAnnoyByWord(testIndexPath, testAnnoyPath, testWord, 
    dimensions, loadedVector)) {

    // Correct number of dimensions should be in loaded vector.
    assert(dimensions == 200);
    printVector(loadedVector, dimensions);
  }
  else {
    printf("Could not load vector!\n");
  }
}
