#include <stdio.h>
#include "annoylib.h"
#include <vector>

const long long max_w = 2000;

void w2vToAnnoy(char *binPath, char *wordIndexPath,
  char *annoyPath, int numberOfTrees,
  long long *numberOfDimensionsPerVector) {

  FILE * fi = fopen(binPath, "rb");
  FILE * fWordIndex = fopen(wordIndexPath, "wb");
  
  long long words, dimensions;
  fscanf(fi, "%lld", &words);
  fscanf(fi, "%lld", &dimensions);
  fscanf(fi, "%*[ ]");
  fscanf(fi, "%*[\n]");

  // printf("dimensions: %lld\n", dimensions);
  *numberOfDimensionsPerVector = dimensions;

  char word[max_w];
  char ch;
  float value;
  int b, a;

  AnnoyIndex<int, float, Angular, RandRandom> annoy =
  AnnoyIndex<int, float, Angular, RandRandom>(dimensions);

  for (b = 0; b < words; b++) {
    if(feof(fi))
      break;

    word[0] = 0;
    fscanf(fi, "%[^ ]", word);
    fscanf(fi, "%c", &ch);

    fprintf(fWordIndex, "%s:%d\n", word, b);

    std::vector<float> vec(dimensions);
    // printf("Number of members of vec initially: %lu\n", vec.size());

    for (a = 0; a < dimensions; a++) {
      fread(&value, sizeof(float), 1, fi);
      vec[a] = value;
      // printf("%lf ", vec[a]);
    }
    fscanf(fi, "%*[\n]");

    // printf("Number of members of vec: %lu\n", vec.size());
    annoy.add_item(b, vec.data());
  }


  printf("Building trees...\n");
  annoy.build(numberOfTrees);

  printf("Saving index.\n");
  annoy.save(annoyPath);

  fclose(fi);
  fclose(fWordIndex);
}
