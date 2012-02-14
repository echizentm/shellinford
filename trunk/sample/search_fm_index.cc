#include "shellinford_fm_index.h"
#include <iostream>

using namespace std;
int main(int argc, char **argv) {
  try {
    if (argc < 2) {
      cerr << "USAGE: search_fm_index dicname" << endl;
    }
    shellinford::fm_index fm;
    fm.read(argv[1]);

    string key = "";
    while (cin >> key) {
      map<uint64_t, uint64_t> dids;
      fm.search(key, dids);
      cout << dids.size() << " hits." << endl;

      map<uint64_t, uint64_t>::const_iterator i = dids.begin();
      map<uint64_t, uint64_t>::const_iterator e = dids.end();
      while (i != e) {
        cout << "[" << i->first << "]: "
             << fm.get_document(i->first)
             << "(" << i->second << ")" << endl;
        i++;
      }
      cout << endl;
    }
  } catch (const char *err) {
    cerr << "ERROR: " << err << endl;
  }
  return 0;
}

