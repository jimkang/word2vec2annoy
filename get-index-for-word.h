#ifndef GET_INDEX_FOR_WORD_H
#define GET_INDEX_FOR_WORD_H

#include <string>
#include <vector>
#include <stdio.h>
#include "split.h"

int getIndexForWord(const char *wordIndexPath, const char *word) {
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

#endif