AM_CXXFLAGS = -Wall -g -O2 -I../src

check_PROGRAMS = \
  test_bit_vector \
  test_wavelet_tree \
  test_fm_index

test_bit_vector_SOURCES = \
  test_bit_vector.cc \
  test_main.cc
test_bit_vector_LDADD = \
  ../src/libshellinford.la \
  -lcppunit

test_wavelet_tree_SOURCES = \
  test_wavelet_tree.cc \
  test_main.cc
test_wavelet_tree_LDADD = \
  ../src/libshellinford.la \
  -lcppunit

test_fm_index_SOURCES = \
  test_fm_index.cc \
  test_main.cc
test_fm_index_LDADD = \
  ../src/libshellinford.la \
  -lcppunit


