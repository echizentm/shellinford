#include <cppunit/extensions/HelperMacros.h>
#include "shellinford_wavelet_tree.h"
#include <cstring>

using namespace CPPUNIT_NS;
using namespace std;
using namespace shellinford;
class test_wavelet_tree : public TestFixture {
  CPPUNIT_TEST_SUITE(test_wavelet_tree);
  CPPUNIT_TEST(size);
  CPPUNIT_TEST(get);
  CPPUNIT_TEST(rank);
  CPPUNIT_TEST(select);
  CPPUNIT_TEST(get_boundary);
  CPPUNIT_TEST(rank_boundary);
  CPPUNIT_TEST(select_boundary);
  CPPUNIT_TEST_SUITE_END();

  const char *str;
  vector<vector<uint64_t> > rd;
  vector<vector<uint64_t> > sd;
  wavelet_tree<uint8_t> wt;
  void size() {
    CPPUNIT_ASSERT_EQUAL(uint64_t(strlen(str)), wt.size());
    for (uint64_t c = 0; c < 256; c++) {
      CPPUNIT_ASSERT_EQUAL(rd[c][wt.size()], wt.size(c));
    }
  }
  void get() {
    for (uint64_t i = 0; i < wt.size(); i++) {
      CPPUNIT_ASSERT_EQUAL(str[i], char(wt.get(i)));
    }
  }
  void rank() {
    for (uint64_t c = 0; c < 256; c++) {
      for (uint64_t i = 0; i <= wt.size(); i++) {
        CPPUNIT_ASSERT_EQUAL(rd[c][i], wt.rank(i, c));
      }
    }
  }
  void select() {
    for (uint64_t c = 0; c < 256; c++) {
      for (uint64_t i = 0; i < wt.size(c); i++) {
        CPPUNIT_ASSERT_EQUAL(sd[c][i], wt.select(i, c));
      }
    }
  }
  void get_boundary() {
    try {
      wt.get(strlen(str));
      CPPUNIT_FAIL("wt.get()");
    } catch (const char *s) { }
  }
  void rank_boundary() {
    for (uint64_t c = 0; c < 256; c++) {
      try {
        wt.rank(wt.size() + 1, c);
        CPPUNIT_FAIL("wt.rank()");
      } catch (const char *s) { }
    }
  }
  void select_boundary() {
    for (uint64_t c = 0; c < 256; c++) {
      try {
        wt.select(wt.size(c), c);
        CPPUNIT_FAIL("wt.select()");
      } catch (const char *s) { }
    }
  }

public:
  void setUp() {
    str = "abracadabra";
    wt.build(str);

    rd.reserve(256);
    sd.reserve(256);
    for (uint64_t c = 0; c < 256; c++) {
      rd[c].push_back(0);
    }

    for(uint64_t i = 0; str[i] != '\0'; i++) {
      for (uint64_t c = 0; c < 256; c++) {
        rd[c].push_back(rd[c][i]);
        if (str[i] == char(c)) {
          rd[c][i + 1]++;
          sd[c].push_back(i);
        }
      }
    }
  }
  void tearDown() {
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(test_wavelet_tree);

