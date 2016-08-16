#include <stdio.h>
// #include <stdlib.h>
#include "annoylib.h"
#include <vector>

const long long max_w = 2000;
const int dimensions = 40;

void w2vToAnnoy(char *binPath, char *wordIndexPath, char *annoyPath) {
  FILE * fi = fopen(binPath, "rb");
  FILE * fWordIndex = fopen(wordIndexPath, "wb");
  
  long long words, size;
  fscanf(fi, "%lld", &words);
  fscanf(fi, "%lld", &size);
  fscanf(fi, "%*[ ]");
  fscanf(fi, "%*[\n]");

  // printf("%lld %lld\n", words, size);

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

    // printf("%s ", word);
    fprintf(fWordIndex, "%s:%d\n", word, b);

    // float *vec = (float *) malloc(dimensions * sizeof(float));
    std::vector<float> vec(dimensions);

    for (a = 0; a < size; a++) {
      fread(&value, sizeof(float), 1, fi);
      // printf("%lf ", value);
      // vec[a] = value;
      vec.push_back(value);
    }
    fscanf(fi, "%*[\n]");

    annoy.add_item(b, vec.data());
    // free(vec);
    // printf("\n");

    // printf("Adding item %d\n", b);
  }


  printf("Building trees...\n");
  annoy.build(10);

  printf("Saving index.\n");
  annoy.save(annoyPath);

  fclose(fi);
  fclose(fWordIndex);
}
