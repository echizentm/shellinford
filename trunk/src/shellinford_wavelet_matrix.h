#ifndef SHELLINFORD_WAVELET_MATRIX
#define SHELLINFORD_WAVELET_MATRIX

#include "shellinford_bit_vector.h"
#include <string>

namespace shellinford {
  // wavelet_matrix<T> is template class.
  // T must be uint8_t, uint16_t, uint32_t or uint64_t.
  template<class T>
  class wavelet_matrix {
    std::vector<bit_vector> bv_;
    std::vector<uint64_t>   seps_;
    uint64_t bitsize_;
    uint64_t size_;

  public:
    wavelet_matrix();
    ~wavelet_matrix();
    void clear();
    void build(const char *s);
    void build(std::vector<T> &v);
    uint64_t bitsize() const { return this->bitsize_; }
    uint64_t size() const { return this->size_; }
    uint64_t size(T c) const {
      return this->rank(this->size(), c);
    }
    T get(uint64_t i) const;
    uint64_t rank(uint64_t i, T c) const;
    uint64_t select(uint64_t i, T c) const;
    uint64_t rank_less_than(uint64_t i, T c) const;
    void write(std::ofstream &ofs) const;
    void write(const char *filename) const;
    void read(std::ifstream &ifs);
    void read(const char *filename);
  };

  template<class T>
  bool uint2bit(T c, uint64_t i) {
    return ((c >> (sizeof(T) * 8 - 1 - i)) & 0x1ULL) == 0x1ULL;
  }

  template<class T>
  wavelet_matrix<T>::wavelet_matrix()
   : bitsize_(sizeof(T) * 8), size_(0) {
  }
  template<class T>
  wavelet_matrix<T>::~wavelet_matrix() {
  }
  template<class T>
  void wavelet_matrix<T>::clear() {
    this->bv_.clear();
    this->seps_.clear();
    this->size_ = 0;
  }
  template<class T>
  void wavelet_matrix<T>::build(const char *s) {
    std::vector<T> v;
    while (*s != '\0') { v.push_back(*s); s++; }
    this->build(v);
  }
  template<class T>
  void wavelet_matrix<T>::build(std::vector<T> &v) {
    this->clear();
    this->bv_.assign(this->bitsize(), bit_vector());
    this->seps_.assign(this->bitsize(), 0);
    this->size_ = v.size();
    for (uint64_t i = 0; i < this->size(); i++) {
      this->bv_[0].set(i, uint2bit(v[i], 0));
    }
    this->bv_[0].build();

    uint64_t depth = 1;
    while (depth < this->bitsize()) {
      this->seps_[depth - 1] = this->bv_[depth - 1].size(false);
      uint64_t pos0 = 0;
      uint64_t pos1 = this->seps_[depth - 1];
      std::vector<T> v_tmp(this->size(), 0); 
      for (uint64_t i = 0; i < this->size(); i++) {
        bool b = uint2bit(v[i], depth);
        if (this->bv_[depth - 1].get(i)) {
          this->bv_[depth].set(pos1, b);
          v_tmp[pos1] = v[i];
          pos1++;
        } else {
          this->bv_[depth].set(pos0, b);
          v_tmp[pos0] = v[i];
          pos0++;
        }
      }
      this->bv_[depth].build();
      v = v_tmp;
      depth++;
    }

/*    for (uint64_t i = 0; i < this->bitsize(); i++) {
    for (uint64_t j = 0; j < this->size(); j++) {
      std::cout << this->bv_[i].get(j) << " ";
    }
    std::cout << std::endl;
    }*/
  }
  template<class T>
  T wavelet_matrix<T>::get(uint64_t i) const {
    if (i >= this->size()) {
      throw "shellinford::wavelet_matrix::get()";
    }

    uint64_t value = 0;
    uint64_t depth = 0;
    while (depth < this->bitsize()) {
      bool bit = this->bv_[depth].get(i);
      i = this->bv_[depth].rank(i, bit);
      value <<= 1;
      if (bit) {
        i     += this->seps_[depth];
        value += 1;
      }
      depth++;
    }
    return value;
  }
  template<class T>
  uint64_t wavelet_matrix<T>::rank(uint64_t i, T c) const {
    if (i > this->size()) {
      throw "shellinford::wavelet_matrix::rank()";
    }
    if (i == 0) { return 0; }

    uint64_t begin = 0;
    uint64_t end   = i;
    uint64_t depth = 0;
    while (depth < this->bitsize()) {
      bool bit = uint2bit(c, depth);
      begin    = this->bv_[depth].rank(begin, bit);
      end      = this->bv_[depth].rank(end  , bit);
      if (bit) {
        begin += this->seps_[depth];
        end   += this->seps_[depth];
      }
      depth++;
    }
    return end - begin;
  }
  template<class T>
  uint64_t wavelet_matrix<T>::rank_less_than(uint64_t i, T c) const {
    if (i > this->size()) {
      throw "shellinford::wavelet_matrix::rank_less_than()";
    }
    if (i == 0) { return 0; }

    uint64_t begin = 0;
    uint64_t end   = i;
    uint64_t depth = 0;
    uint64_t rlt   = 0;
    while (depth < this->bitsize()) {
      uint64_t rank0_begin = this->bv_[depth].rank(begin, false);
      uint64_t rank0_end   = this->bv_[depth].rank(end  , false);
      if (uint2bit(c, depth)) {
        rlt += (rank0_end - rank0_begin);
        begin += (this->seps_[depth] - rank0_begin);
        end   += (this->seps_[depth] - rank0_end);
      } else {
        begin = rank0_begin;
        end   = rank0_end;
      }
      depth++;
    }
    return rlt;
  }
  template<class T>
  uint64_t wavelet_matrix<T>::select(uint64_t i, T c) const {
    if (i >= this->size(c)) {
      throw "shellinford::wavelet_matrix::select()";
    }

    uint64_t left  = 0;
    uint64_t right = this->size();
    while (left < right) {
      uint64_t pivot = (left + right) / 2;
      uint64_t value = this->rank(pivot, c);
      if      (i < value) { right = pivot; }
      else if (i > value) { left  = pivot + 1; }
      else {
        while ((pivot > 0) && (this->get(pivot) != c)) {
          pivot++;
        } 
        return pivot;
      }
    }
    throw "shellinford::wavelet_matrix::select()";
  }
  template<class T>
  void wavelet_matrix<T>::write(std::ofstream &ofs) const {
    ofs.write((char *)&(this->size_), sizeof(uint64_t));

    for (uint64_t i = 0; i < this->bitsize(); i++) {
      this->bv_[i].write(ofs);
    }
    for (uint64_t i = 0; i < this->bitsize(); i++) {
      ofs.write((char *)&(this->seps_[i]), sizeof(uint64_t));
    }
  }
  template<class T>
  void wavelet_matrix<T>::write(const char *filename) const {
    std::ofstream ofs(filename,
                  std::ios::out | std::ios::binary | std::ios::trunc);
    if (!ofs) { throw "shellinford::wavelet_matrix::write()"; }
    this->write(ofs);
  } 
  template<class T>
  void wavelet_matrix<T>::read(std::ifstream &ifs) {
    ifs.read((char *)&(this->size_), sizeof(uint64_t));
    if (ifs.eof()) { throw "shellinford::wavelet_matrix::read()"; }

    for (uint64_t i = 0; i < this->bitsize(); i++) {
      this->bv_.push_back(bit_vector());
      this->bv_.back().read(ifs);
    }
    uint64_t sep = 0;
    for (uint64_t i = 0; i < this->bitsize(); i++) {
      ifs.read((char *)&sep, sizeof(uint64_t));
      this->seps_.push_back(sep);
    }
  }
  template<class T>
  void wavelet_matrix<T>::read(const char *filename) {
    std::ifstream ifs(filename, std::ios::in | std::ios::binary);
    if (!ifs) { throw "shellinford::wavelet_matrix::read()"; }
    this->read(ifs);
  }
}

#endif

