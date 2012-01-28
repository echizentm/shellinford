#include <cppunit/extensions/HelperMacros.h>
#include "shellinford_bit_vector.h"
#include <vector>

using namespace CPPUNIT_NS;
using namespace std;
using namespace shellinford;
class test_bit_vector : public TestFixture {
  CPPUNIT_TEST_SUITE(test_bit_vector);
  CPPUNIT_TEST(size);
  CPPUNIT_TEST(get);
  CPPUNIT_TEST(rank);
  CPPUNIT_TEST(select);
  CPPUNIT_TEST(get_boundary);
  CPPUNIT_TEST(rank_boundary);
  CPPUNIT_TEST(select_boundary);
  CPPUNIT_TEST_SUITE_END();

  vector<uint64_t> values;
  bit_vector bv;
  void size() {
    CPPUNIT_ASSERT_EQUAL(uint64_t(3001), bv.size());
    CPPUNIT_ASSERT_EQUAL(uint64_t(3)   , bv.size1());
    CPPUNIT_ASSERT_EQUAL(uint64_t(2998), bv.size0());
  }
  void get() {
    vector<uint64_t>::const_iterator i = values.begin();
    vector<uint64_t>::const_iterator e = values.end();
    while (i != e) {
      uint64_t v = *i;
      CPPUNIT_ASSERT_EQUAL(false, bv.get(v - 1));
      CPPUNIT_ASSERT_EQUAL(true , bv.get(v));
      if ((v + 1) < bv.size()) {
        CPPUNIT_ASSERT_EQUAL(false, bv.get(v + 1));
      }
      i++;
    }
  }
  void rank() {
    vector<uint64_t>::const_iterator i = values.begin();
    vector<uint64_t>::const_iterator e = values.end();
    uint64_t ct = 0;
    while (i != e) {
      uint64_t v = *i;
      CPPUNIT_ASSERT_EQUAL(ct    , bv.rank(v    , true));
      CPPUNIT_ASSERT_EQUAL(ct + 1, bv.rank(v + 1, true));
      CPPUNIT_ASSERT_EQUAL(v - ct, bv.rank(v    , false));
      CPPUNIT_ASSERT_EQUAL(v - ct, bv.rank(v + 1, false));
      ct++;
      i++;
    }
  }
  void select() {
    vector<uint64_t>::const_iterator i = values.begin();
    vector<uint64_t>::const_iterator e = values.end();
    uint64_t ct = 0;
    while (i != e) {
      uint64_t v = *i;
      CPPUNIT_ASSERT_EQUAL(v    , bv.select(ct        , true));
      CPPUNIT_ASSERT_EQUAL(v - 1, bv.select(v - ct - 1, false));
      if ((v - ct) < bv.size0()) {
        CPPUNIT_ASSERT_EQUAL(v + 1, bv.select(v - ct, false));
      }
      ct++;
      i++;
    }
  }


  void get_boundary() {
    try {
      bv.get(bv.size());
      CPPUNIT_FAIL("");
    } catch (const char *s) { }
  }
  void rank_boundary() {
    try {
      bv.rank(bv.size() + 1, true);
      CPPUNIT_FAIL("rank1 boundary");
    } catch (const char *s) { }
    try {
      bv.rank(bv.size() + 1, false);
      CPPUNIT_FAIL("rank0 boundary");
    } catch (const char *s) { }
  }
  void select_boundary() {
    try {
      bv.select(bv.size1(), true);
      CPPUNIT_FAIL("select1 boundary");
    } catch (const char *s) { }
    try {
      bv.select(bv.size0(), false);
      CPPUNIT_FAIL("select0 boundary");
    } catch (const char *s) { }
  }

public:
  void setUp() {
    values.push_back(1000);
    values.push_back(2000);
    values.push_back(3000);
    vector<uint64_t>::const_iterator i = values.begin();
    vector<uint64_t>::const_iterator e = values.end();
    while (i != e) { bv.set(*i); i++; }
    bv.build();
  }
  void tearDown() {
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(test_bit_vector);

