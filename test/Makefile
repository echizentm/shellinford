CC  = /usr/bin/g++
BIN = /usr/local/bin/
LIB = /usr/local/lib/
INC = /usr/local/include/
SRC = test_main.cc test_bit_vector.cc test_wavelet_tree.cc \
      test_fm_index.cc
UNAME = $(shell uname)

tools: $(SRC)
	$(CC) -O2 -Wall -g test_main.cc test_bit_vector.cc \
      -lcppunit -lshellinford -o test_bit_vector
	$(CC) -O2 -Wall -g test_main.cc test_wavelet_tree.cc \
      -lcppunit -lshellinford -o test_wavelet_tree
	$(CC) -O2 -Wall -g test_main.cc test_fm_index.cc \
      -lcppunit -lshellinford -o test_fm_index

clean:
	- rm -f test_bit_vector
	- rm -f test_wavelet_tree
	- rm -f test_fm_index
	- rm -Rf *.dSYM

