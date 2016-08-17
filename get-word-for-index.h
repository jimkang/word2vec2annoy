#ifndef GET_WORD_FOR_INDEX_H
#define GET_WORD_FOR_INDEX_H

#include <string>
#include <vector>
#include <stdio.h>
#include "split.h"
#include <string.h>

using namespace std;

int getWordForIndex(const char *wordIndexPath, int index, char *word) {
  FILE * fWordIndex = fopen(wordIndexPath, "rb");
  char line[256];

  // http://stackoverflow.com/questions/9206091/going-through-a-text-file-line-by-line-in-c
  while (fgets(line, sizeof(line), fWordIndex)) {
      /* note that fgets don't strip the terminating \n, checking its
         presence would allow to handle lines longer that sizeof(line) */
    vector<string> parts = split(string(line), ':');
    if (parts.size() == 2 && atoi(parts.at(1).c_str()) == index) {
      // printf("%s", line);
      strcpy(word, parts.at(0).c_str());
      break;
    }
  }

  /* may check feof here to make a difference between eof and io failure -- network
     timeout for instance */

  fclose(fWordIndex);

  return index;  
}

#endif
