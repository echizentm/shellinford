#ifndef SHELLINFORD_WAVELET_TREE
#define SHELLINFORD_WAVELET_TREE

#include "shellinford_bit_vector.h"

namespace shellinford {
  class wavelet_tree {
  public:
    wavelet_tree();
    ~wavelet_tree();
    void clear();
    char get(uint64_t i) const;
    void build(const char *s);
    uint64_t size() const { return 0; }
    uint64_t size(char c) const { return 0; }
    uint64_t rank(uint64_t i, char c) const;
    uint64_t select(uint64_t i, char c) const;
    void write(std::ofstream &ofs) const;
    void write(const char *filename) const;
    void read(std::ifstream &ifs);
    void read(const char *filename);
  };
}

#endif

