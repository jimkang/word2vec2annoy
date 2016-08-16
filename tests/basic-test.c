#include "../w2v-to-annoy.h"
#include "../load-from-annoy-by-word.h"
#include <string>

char testBinPath[] = "data/text8-vector.bin";
char testIndexPath[] = "test-index.txt";
char testAnnoyPath[] = "test-annoy.tree";

char testWord[] = "cat";

int main(int argc, char **argv) {
  w2vToAnnoy(testBinPath, testIndexPath, testAnnoyPath);

  float loadedVector[40] = {0.0};
  if (loadFromAnnoyByWord(testIndexPath, testAnnoyPath, testWord, loadedVector)) {
    for (int i = 0; i < 40; ++i) {
      printf("%f, ", loadedVector[i]);
    }
  }
  else {
    printf("Could not load vector!\n");
  }
}
