#include "shellinford_wavelet_tree.h"
#include <cstring>
#include <string>
#include <queue>
#include <iostream>

namespace shellinford {
  using namespace std;

  struct range {
    uint64_t pos;
    uint64_t len;
    uint64_t depth;
    string   str;
    range(uint64_t p, uint64_t l, uint64_t d, const string &s)
     : pos(p), len(l), depth(d), str(s) {} 
  };
  bool char2bit(char c, uint64_t i) {
    return ((c >> (7 - i)) & 0x01) == 0x01;
  }

  wavelet_tree::wavelet_tree()
   : bv_(8), size_(0), sizec_(256, 0) {
  }
  wavelet_tree::~wavelet_tree() {
  }
  void wavelet_tree::clear() {
  }
  char wavelet_tree::get(uint64_t i) const {
    if (i >= this->size()) { throw "shellinford::wavelet_tree::get()"; }

    char value = 0x00;
    range r(0, this->size(), 0, "");
    while (r.depth < 8) {
      const bit_vector &bv = this->bv_[r.depth];
      bool b = bv.get(r.pos + i);
      value <<= 1;
      if (b) { value |= 0x01; }

      i = bv.rank(r.pos + i, b) - bv.rank(r.pos, b);
      uint64_t pos = r.pos;
      uint64_t len = bv.rank(r.pos + r.len, false)
                     - bv.rank(r.pos, false);
      if (b) {
        pos += len;
        len = r.len - len;
      }
      r = range(pos, len, r.depth + 1, "");
    }
    return value;
  }
  void wavelet_tree::build(const char *s) {
    this->size_ = strlen(s);
    queue<range> rq;
    rq.push(range(0, this->size(), 0, s));
    while (!(rq.empty())) {
      range r = rq.front();
      rq.pop();
      bit_vector &bv = this->bv_[r.depth];
      string s1 = "";
      string s0 = "";
      for (uint64_t i = 0; i < r.len; i++) {
         uint64_t pos = r.pos + i;
         bool     bit = char2bit(r.str[i], r.depth);
         bv.set(pos, bit);
         if (bit) { s1 += r.str[i]; }
         else     { s0 += r.str[i]; }
      }
      bv.build();
      if (r.depth < 7) {
        uint64_t pos = r.pos;
        uint64_t len = bv.rank(r.pos + r.len, false)
                       - bv.rank(r.pos, false);
        rq.push(range(pos, len, r.depth + 1, s0));
        pos += len;
        len = r.len - len;
        rq.push(range(pos, len, r.depth + 1, s1));
      }
    }
    vector<uint64_t>::iterator i = this->sizec_.begin();
    vector<uint64_t>::iterator e = this->sizec_.end();
    uint64_t c = 0;
    while (i != e) {
      *i = this->rank(this->size(), c);
      c++;
      i++;
    }
  }
  uint64_t wavelet_tree::rank(uint64_t i, uint8_t c) const {
    if (i > this->size()) { throw "shellinford::wavelet_tree::rank()"; }
    if (i == 0) { return 0; }

    range r(0, this->size(), 0, "");
    while (r.depth < 8) {
      const bit_vector &bv = this->bv_[r.depth];
      bool b = char2bit(c, r.depth);

      i = bv.rank(r.pos + i, b) - bv.rank(r.pos, b);
      uint64_t pos = r.pos;
      uint64_t len = bv.rank(r.pos + r.len, false)
                     - bv.rank(r.pos, false);
      if (b) {
        pos += len;
        len = r.len - len;
      }
      r = range(pos, len, r.depth + 1, "");
    }
    return i;
  }
  uint64_t wavelet_tree::select(uint64_t i, uint8_t c) const {
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

