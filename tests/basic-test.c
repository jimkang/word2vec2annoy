#include "../w2v-to-annoy.h"
#include "../load-from-annoy-by-word.h"
#include <string>
#include <vector>
#include <assert.h>
#include "../get-index-for-word.h"
#include "../get-word-for-index.h"
#include "../annoylib.h"

char testBinPath[] = "data/text8-vector.bin";
char testIndexPath[] = "test-index.txt";
char testAnnoyPath[] = "test-annoy.tree";

char testWord[] = "platypus";

char nnsTestWord1[] = "natural";
char nnsTestWord2[] = "house";

void printVector(float *vector, int dimensions) {
  for (int i = 0; i < dimensions; ++i) {
    printf("%f, ", vector[i]);
  }
  printf("\n");
}

void printIndexes(std::vector<int> indexes) {
  for (std::vector<int>::iterator index = indexes.begin(); index!=indexes.end(); ++index) {
    printf("%d, ", *index);
    char foundWord[2000];
    getWordForIndex(testIndexPath, *index, foundWord);
    printf("%s\n", foundWord);
  }
  printf("\n");
}

void addVectors(float *a, float *b, float *sum, int dimensions) {
  for (int i = 0; i < dimensions; ++i) {
    sum[i] = a[i] + b[i];
  }
}

void subtractVectors(float *a, float *b, float *difference, int dimensions) {
  for (int i = 0; i < dimensions; ++i) {
    difference[i] = a[i] - b[i];
  }
}

void testFindingNeighbor(long long dimensions) {
  int index1 = getIndexForWord(testIndexPath, nnsTestWord1);
  int index2 = getIndexForWord(testIndexPath, nnsTestWord2);
  printf("index1: %d, index2: %d\n", index1, index2);
  
  AnnoyIndex<int, float, Angular, RandRandom> annoy =
    AnnoyIndex<int, float, Angular, RandRandom>(dimensions);
  // annoy.verbose(true);
  
  bool loaded = annoy.load(testAnnoyPath);
  assert(loaded);

  float vector1[dimensions];
  float vector2[dimensions];
  float sum[dimensions];

  annoy.get_item(index1, vector1);
  annoy.get_item(index2, vector2);
  addVectors(vector1, vector2, sum, dimensions);

  printVector(vector1, dimensions);
  printVector(vector2, dimensions);
  printVector(sum, dimensions);

  std::vector<int> closest;
  annoy.get_nns_by_vector(sum, 10, -1, &closest, nullptr);
  printIndexes(closest);
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

  testFindingNeighbor(dimensions);
}
