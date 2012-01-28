CC  = /usr/bin/g++
BIN = /usr/local/bin/
LIB = /usr/local/lib/
INC = /usr/local/include/
SRC = test_main.cc test_bit_vector.cc
UNAME = $(shell uname)

tools: $(SRC)
	$(CC) -O2 -Wall -g test_main.cc test_bit_vector.cc \
      -lcppunit -lshellinford -o test_bit_vector

clean:
	- rm -f test_bit_vector
	- rm -Rf *.dSYM

