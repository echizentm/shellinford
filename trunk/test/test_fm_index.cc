#include <cppunit/extensions/HelperMacros.h>
#include "shellinford_fm_index.h"
#include <string>
#include <algorithm>
#include <utility>
#include <vector>

using namespace CPPUNIT_NS;
using namespace std;
using namespace shellinford;
class test_fm_index : public TestFixture {
  CPPUNIT_TEST_SUITE(test_fm_index);
  CPPUNIT_TEST(size);
  CPPUNIT_TEST(get_rows);
  CPPUNIT_TEST(get_position);
  CPPUNIT_TEST(get_substring);
  CPPUNIT_TEST(get_position_boundary);
  CPPUNIT_TEST(get_substring_boundary);
  CPPUNIT_TEST_SUITE_END();

  string str;
  map<string, uint64_t> rd;
  vector<uint64_t> pd;
  vector<string> sd;
  fm_index fm;
  void size() {
    CPPUNIT_ASSERT_EQUAL(uint64_t(str.size()), fm.size());
  }
  void get_rows() {
    for (uint64_t i = 0;     i < fm.size(); i++) {
    for (uint64_t j = i + 1; j < fm.size(); j++) {
      string s = str.substr(i, j);
      CPPUNIT_ASSERT_EQUAL(rd[s], fm.get_rows(s.c_str()));
    }
    }
  }
  void get_position() {
    for (uint64_t i = 0; i < fm.size(); i++) {
      CPPUNIT_ASSERT_EQUAL(pd[i], fm.get_position(i));
    }
  }
  void get_substring() {
    for (uint64_t i = 0; i < fm.size(); i++) {
      CPPUNIT_ASSERT_EQUAL(sd[i], fm.get_substring(i, fm.size()));
    }
  }
  void get_position_boundary() {
    try {
      fm.get_position(str.size());
      CPPUNIT_FAIL("fm.get_position()");
    } catch (const char *s) { }
  }
  void get_substring_boundary() {
    try {
      fm.get_substring(str.size(), 0);
      CPPUNIT_FAIL("fm.get_substring()");
    } catch (const char *s) { }
  }

public:
  void setUp() {
    str = "abracadabra mississippi";
    fm.build(str.c_str(), 3);

    for (uint64_t i = 0; i < str.size(); i++) {
    for (uint64_t j = 1; j <= (str.size() - i); j++) {
      string s = str.substr(i, j);
      rd[s]++;
    }
    }

    vector<pair<string, uint64_t> > v;
    for (uint64_t i = 0; i < str.size(); i++) {
      string s = str.substr(i, str.size() - i) + str.substr(0, i);
      v.push_back(pair<string, uint64_t>(s, i));
    }
    sort(v.begin(), v.end());
    vector<pair<string, uint64_t> >::const_iterator i = v.begin();
    vector<pair<string, uint64_t> >::const_iterator e = v.end();
    while (i != e) {
      pd.push_back(i->second);
      i++;
    }

    for (uint64_t i = 0; i < str.size(); i++) {
      sd.push_back(str.substr(i));
    }
  }
  void tearDown() {
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(test_fm_index);

