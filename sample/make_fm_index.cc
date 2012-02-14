#include "shellinford_fm_index.h"
#include <iostream>

using namespace std;
int main(int argc, char **argv) {
  try {
    if (argc < 2) {
      cerr << "USAGE: make_fm_index dicname < filename" << endl;
    }
    shellinford::fm_index fm;
    string s;
    while (cin >> s) { fm.push_back(s); }

    fm.build();
    fm.write(argv[1]);
  } catch (const char *err) {
    cerr << "ERROR: " << err << endl;
  }
  return 0;
}

