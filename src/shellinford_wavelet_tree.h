#ifndef SHELLINFORD_WAVELET_TREE
#define SHELLINFORD_WAVELET_TREE

#include "shellinford_bit_vector.h"
#include <cstring>
#include <string>
#include <queue>

namespace shellinford {
  template<class T>
  class wavelet_tree {
    std::vector<bit_vector> bv_;
    uint64_t bitsize_;
    uint64_t size_;

  public:
    wavelet_tree();
    ~wavelet_tree();
    void clear();
    T get(uint64_t i) const;
    void build(const char *s);
    void build(std::vector<T> &v);
    uint64_t bitsize() const { return this->bitsize_; }
    uint64_t size() const { return this->size_; }
    uint64_t size(T c) const {
      return this->rank(this->size(), c);
    }
    uint64_t rank(uint64_t i, T c) const;
    uint64_t select(uint64_t i, T c) const;
    void write(std::ofstream &ofs) const;
    void write(const char *filename) const;
    void read(std::ifstream &ifs);
    void read(const char *filename);
  };

  template<class T>
  struct range {
    uint64_t       pos;
    uint64_t       len;
    uint64_t       depth;
    std::vector<T> vec;
    range(uint64_t p, uint64_t l, uint64_t d,
          const std::vector<T> &v)
     : pos(p), len(l), depth(d), vec(v) {} 
  };
  template<class T>
  bool uint2bit(T c, uint64_t i) {
    return ((c >> (sizeof(T) * 8 - 1 - i)) & 0x1ULL) == 0x1ULL;
  }

  template<class T>
  wavelet_tree<T>::wavelet_tree()
   : bv_(0), bitsize_(sizeof(T) * 8), size_(0) {
  }
  template<class T>
  wavelet_tree<T>::~wavelet_tree() {
  }
  template<class T>
  void wavelet_tree<T>::clear() {
    this->bv_.clear();
    this->size_ = 0;
  }
  template<class T>
  T wavelet_tree<T>::get(uint64_t i) const {
    if (i >= this->size()) { throw "shellinford::wavelet_tree::get()"; }

    T value = 0;
    range<T> r(0, this->size(), 0, std::vector<T>());
    while (r.depth < this->bitsize()) {
      const bit_vector &bv = this->bv_[r.depth];
      bool b = bv.get(r.pos + i);
      value <<= 1;
      if (b) { value |= 0x1ULL; }

      i = bv.rank(r.pos + i, b) - bv.rank(r.pos, b);
      uint64_t pos = r.pos;
      uint64_t len = bv.rank(r.pos + r.len, false)
                     - bv.rank(r.pos, false);
      if (b) {
        pos += len;
        len = r.len - len;
      }
      r = range<T>(pos, len, r.depth + 1, r.vec);
    }
    return value;
  }
  template<class T>
  void wavelet_tree<T>::build(const char *s) {
    std::vector<T> v;
    while (*s != '\0') { v.push_back(*s); s++; }
    this->build(v);
  }
  template<class T>
  void wavelet_tree<T>::build(std::vector<T> &v) {
    this->bv_.clear();
    this->bv_.assign(this->bitsize(), bit_vector());

    this->size_ = v.size();
    std::queue<range<T> > rq;
    rq.push(range<T>(0, this->size(), 0, v));
    while (!(rq.empty())) {
      range<T> r = rq.front();
      rq.pop();
      if (r.len == 0) { continue; }
      bit_vector &bv = this->bv_[r.depth];
      std::vector<T> v1;
      std::vector<T> v0;
      for (uint64_t i = 0; i < r.len; i++) {
         uint64_t pos = r.pos + i;
         bool     bit = uint2bit(r.vec[i], r.depth);
         bv.set(pos, bit);
         if (bit) { v1.push_back(r.vec[i]); }
         else     { v0.push_back(r.vec[i]); }
      }
      bv.build();
      if (r.depth < (this->bitsize() - 1)) {
        uint64_t pos = r.pos;
        uint64_t len = bv.rank(r.pos + r.len, false)
                       - bv.rank(r.pos, false);
        rq.push(range<T>(pos, len, r.depth + 1, v0));
        pos += len;
        len = r.len - len;
        rq.push(range<T>(pos, len, r.depth + 1, v1));
      }
    }
  }
  template<class T>
  uint64_t wavelet_tree<T>::rank(uint64_t i, T c) const {
    if (i > this->size()) { throw "shellinford::wavelet_tree::rank()"; }
    if (i == 0) { return 0; }

    range<T> r(0, this->size(), 0, std::vector<T>());
    while (r.depth < this->bitsize()) {
      const bit_vector &bv = this->bv_[r.depth];
      bool b = uint2bit(c, r.depth);

      i = bv.rank(r.pos + i, b) - bv.rank(r.pos, b);
      uint64_t pos = r.pos;
      uint64_t len = bv.rank(r.pos + r.len, false)
                     - bv.rank(r.pos, false);
      if (b) {
        pos += len;
        len = r.len - len;
      }
      r = range<T>(pos, len, r.depth + 1, r.vec);
    }
    return i;
  }
  template<class T>
  uint64_t wavelet_tree<T>::select(uint64_t i, T c) const {
    if (i >= this->size(c)) { throw "shellinford::wavelet_tree::select()"; }
    return 0;
  }
  template<class T>
  void wavelet_tree<T>::write(std::ofstream &ofs) const {
  }
  template<class T>
  void wavelet_tree<T>::write(const char *filename) const {
  } 
  template<class T>
  void wavelet_tree<T>::read(std::ifstream &ifs) {
  }
  template<class T>
  void wavelet_tree<T>::read(const char *filename) {
  }
}

#endif

