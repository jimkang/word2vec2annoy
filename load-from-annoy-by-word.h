#include "annoylib.h"
#include "get-index-for-word.h"

bool loadFromAnnoyByWord(char *wordIndexPath, char *annoyPath, char *word,
  long long dimensions, float *vector) {

  int index = getIndexForWord(wordIndexPath, word);
  printf("index: %d\n", index);

  AnnoyIndex<int, float, Angular, RandRandom> annoy =
    AnnoyIndex<int, float, Angular, RandRandom>(dimensions);
  // annoy.verbose(true);
  
  if (annoy.load(annoyPath)) {
    annoy.get_item(index, vector);
    return true;
  }
  else {
    return false;
  }
}
