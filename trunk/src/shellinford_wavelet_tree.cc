#include "shellinford_wavelet_tree.h"

namespace shellinford {
  using namespace std;

  wavelet_tree::wavelet_tree() {
  }
  wavelet_tree::~wavelet_tree() {
  }
  void wavelet_tree::clear() {
  }
  char wavelet_tree::get(uint64_t i) const {
    if (i >= this->size()) { throw "shellinford::wavelet_tree::get()"; }
    return 0;
  }
  void wavelet_tree::build(const char *s) {
  }
  uint64_t wavelet_tree::rank(uint64_t i, char c) const {
    if (i > this->size()) { throw "shellinford::wavelet_tree::rank()"; }
    if (i == 0) { return 0; }
    return 0;
  }
  uint64_t wavelet_tree::select(uint64_t i, char c) const {
    if (i >= this->size(c)) { throw "shellinford::wavelet_tree::select()"; }
    return 0;
  }
  void wavelet_tree::write(std::ofstream &ofs) const {
  }
  void wavelet_tree::write(const char *filename) const {
  } 
  void wavelet_tree::read(std::ifstream &ifs) {
  }
  void wavelet_tree::read(const char *filename) {
  }
}

