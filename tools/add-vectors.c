#include "../w2v-to-annoy.h"
#include "../load-from-annoy-by-word.h"
#include <string>
#include <vector>
#include <assert.h>
#include "../get-index-for-word.h"
#include "../get-word-for-index.h"
#include "../annoylib.h"

char testWord[] = "platypus";

void printVector(float *vector, int dimensions) {
  for (int i = 0; i < dimensions; ++i) {
    printf("%f, ", vector[i]);
  }
  printf("\n");
}

void printIndexes(std::vector<int> indexes, char *wordIndexPath) {
  for (std::vector<int>::iterator index = indexes.begin(); index!=indexes.end(); ++index) {
    printf("%d, ", *index);
    char foundWord[2000];
    getWordForIndex(wordIndexPath, *index, foundWord);
    printf("%s\n", foundWord);
  }
  printf("\n");
}

void addVectors(float *a, float *b, float *sum, int dimensions) {
  for (int i = 0; i < dimensions; ++i) {
    sum[i] = a[i] + b[i];
  }
}

void addVectors(vector<float *> addends, float *sum, int dimensions) {
  for (vector<float *>::iterator it = addends.begin(); it != addends.end(); ++it) {
    for (int i = 0; i < dimensions; ++i) {
      sum[i] = it->a[i] + it->b[i];
    }
  }
}

void subtractVectors(float *a, float *b, float *difference, int dimensions) {
  for (int i = 0; i < dimensions; ++i) {
    difference[i] = a[i] - b[i];
  }
}

void addWords(int dimensions, 
  char *wordIndexPath, char *annoyIndexPath,
  char *nnsTestWord1, char *nnsTestWord2) {

  int index1 = getIndexForWord(wordIndexPath, nnsTestWord1);
  int index2 = getIndexForWord(wordIndexPath, nnsTestWord2);
  printf("index1: %d, index2: %d\n", index1, index2);
  
  AnnoyIndex<int, float, Angular, RandRandom> annoy =
    AnnoyIndex<int, float, Angular, RandRandom>(dimensions);
  // annoy.verbose(true);
  
  bool loaded = annoy.load(annoyIndexPath);
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
  printIndexes(closest, wordIndexPath);
}

int main(int argc, char **argv) {
  if (argc < 6) {
    printf("Usage: add-vectors <dimensions> <word index path> <annoy index path> <add word 1> <add word 2>\n");
    return -1;
  }

  int dimensions = atoi(argv[1]);
  char *wordIndexPath = argv[2];
  char *annoyIndexPath = argv[3];
  char *nnsTestWord1 = argv[4];
  char *nnsTestWord2 = argv[5];
  
  addWords(dimensions, wordIndexPath, annoyIndexPath,
    nnsTestWord1, nnsTestWord2
  );
}
