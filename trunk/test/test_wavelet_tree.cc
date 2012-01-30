#include <cppunit/extensions/HelperMacros.h>
#include "shellinford_wavelet_tree.h"

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

  wavelet_tree wt;
  void size() {
  }
  void get() {
  }
  void rank() {
  }
  void select() {
  }
  void get_boundary() {
  }
  void rank_boundary() {
  }
  void select_boundary() {
  }

public:
  void setUp() {
  }
  void tearDown() {
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(test_wavelet_tree);

