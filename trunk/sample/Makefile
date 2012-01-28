CC  = /usr/bin/g++
BIN = /usr/local/bin/
LIB = /usr/local/lib/
INC = /usr/local/include/
SRC = make_bit_vector.cc rank_bit_vector.cc select_bit_vector.cc
UNAME = $(shell uname)

tools: $(SRC)
	$(CC) -O2 -Wall -g make_bit_vector.cc -lshellinford \
      -o make_bit_vector
	$(CC) -O2 -Wall -g rank_bit_vector.cc -lshellinford \
      -o rank_bit_vector
	$(CC) -O2 -Wall -g select_bit_vector.cc -lshellinford \
      -o select_bit_vector

clean:
	- rm -f make_bit_vector 
	- rm -f rank_bit_vector 
	- rm -f select_bit_vector 
	- rm -Rf *.dSYM

