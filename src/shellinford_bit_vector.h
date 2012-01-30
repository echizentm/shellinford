#ifndef SHELLINFORD_BIT_VECTOR
#define SHELLINFORD_BIT_VECTOR

#include <stdint.h>
#include <vector>
#include <fstream>

namespace shellinford {
  const int SMALL_BLOCK_SIZE =  64;
  const int LARGE_BLOCK_SIZE = 512;
  const int BLOCK_RATE       =   8;

  class bit_vector {
    std::vector<uint64_t> v_;
    std::vector<uint64_t> r_;
    uint64_t size_;
    uint64_t size1_;
  public:
    bit_vector();
    ~bit_vector();
    void clear();
    bool get(uint64_t i) const;
    void set(uint64_t i, bool b = true);
    void build();
    uint64_t size() const { return this->size_; }
    uint64_t size1() const { return this->size1_; }
    uint64_t size0() const { return this->size_ - this->size1_; }
    uint64_t rank(uint64_t i, bool b = true) const;
    uint64_t select(uint64_t i, bool b = true) const;
    void write(std::ofstream &ofs) const;
    void write(const char *filename) const;
    void read(std::ifstream &ifs);
    void read(const char *filename);
  };
}

#endif

