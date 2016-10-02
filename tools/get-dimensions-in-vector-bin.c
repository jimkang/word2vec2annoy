#include <stdio.h>

long long getDimensionsInVectorBin(char *binPath) {
  FILE * fi = fopen(binPath, "rb");
  
  long long words, dimensions;
  fscanf(fi, "%lld", &words);
  fscanf(fi, "%lld", &dimensions);
  return dimensions;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: get-dimensions-in-vector-bin <bin path>\n");
    return -1;
  }

  char *binPath = argv[1];
  long long dimensions = getDimensionsInVectorBin(binPath);
  printf("%lld\n", dimensions);
}
