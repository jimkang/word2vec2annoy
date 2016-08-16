#include <stdio.h>
#include "annoylib.h"
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// http://stackoverflow.com/a/236803/87798
void split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

int getIndexForWord(char *wordIndexPath, char *word) {
  int index = -1;
  FILE * fWordIndex = fopen(wordIndexPath, "rb");
  char line[256];
  printf("%s\n", wordIndexPath);

  // http://stackoverflow.com/questions/9206091/going-through-a-text-file-line-by-line-in-c
  while (fgets(line, sizeof(line), fWordIndex)) {
      /* note that fgets don't strip the terminating \n, checking its
         presence would allow to handle lines longer that sizeof(line) */
    vector<string> parts = split(string(line), ':');
    if (parts.size() == 2 && strcmp(parts.at(0).c_str(), word) == 0) {
      // printf("%s", line);
      index = atoi(parts.at(1).c_str());
      break;
    }
  }
  /* may check feof here to make a difference between eof and io failure -- network
     timeout for instance */

  fclose(fWordIndex);

  return index;  
}

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
