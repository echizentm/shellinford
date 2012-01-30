#ifndef SHELLINFORD_WAVELET_TREE
#define SHELLINFORD_WAVELET_TREE

#include "shellinford_bit_vector.h"

namespace shellinford {
  class wavelet_tree {
    std::vector<bit_vector> bv_;
    uint64_t size_;
    std::vector<uint64_t> sizec_;

  public:
    wavelet_tree();
    ~wavelet_tree();
    void clear();
    char get(uint64_t i) const;
    void build(const char *s);
    uint64_t size() const { return this->size_; }
    uint64_t size(uint8_t c) const { return this->sizec_[c]; }
    uint64_t rank(uint64_t i, uint8_t c) const;
    uint64_t select(uint64_t i, uint8_t c) const;
    void write(std::ofstream &ofs) const;
    void write(const char *filename) const;
    void read(std::ifstream &ifs);
    void read(const char *filename);
  };
}

#endif

