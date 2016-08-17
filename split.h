#ifndef SPLIT_H
#define SPLIT_H

#include <string>
#include <sstream>
#include <vector>

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

#endif
