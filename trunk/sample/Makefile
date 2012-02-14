CC  = /usr/bin/g++
BIN = /usr/local/bin/
LIB = /usr/local/lib/
INC = /usr/local/include/
SRC = make_bit_vector.cc rank_bit_vector.cc select_bit_vector.cc \
      make_wavelet_tree.cc rank_wavelet_tree.cc select_wavelet_tree.cc \
      make_fm_index.cc search_fm_index.cc \
      bwt.cc rbwt.cc
UNAME = $(shell uname)

tools: $(SRC)
	$(CC) -O2 -Wall -g make_bit_vector.cc -lshellinford \
      -o make_bit_vector
	$(CC) -O2 -Wall -g rank_bit_vector.cc -lshellinford \
      -o rank_bit_vector
	$(CC) -O2 -Wall -g select_bit_vector.cc -lshellinford \
      -o select_bit_vector
	$(CC) -O2 -Wall -g make_wavelet_tree.cc -lshellinford \
      -o make_wavelet_tree
	$(CC) -O2 -Wall -g rank_wavelet_tree.cc -lshellinford \
      -o rank_wavelet_tree
	$(CC) -O2 -Wall -g select_wavelet_tree.cc -lshellinford \
      -o select_wavelet_tree
	$(CC) -O2 -Wall -g make_fm_index.cc -lshellinford \
      -o make_fm_index
	$(CC) -O2 -Wall -g search_fm_index.cc -lshellinford \
      -o search_fm_index
	$(CC) -O2 -Wall -g bwt.cc -o bwt
	$(CC) -O2 -Wall -g rbwt.cc -lshellinford -o rbwt

clean:
	- rm -f make_bit_vector 
	- rm -f rank_bit_vector 
	- rm -f select_bit_vector
	- rm -f make_wavelet_tree 
	- rm -f rank_wavelet_tree
	- rm -f select_wavelet_tree
	- rm -f make_fm_index
	- rm -f search_fm_index
	- rm -f bwt
	- rm -f rbwt
	- rm -Rf *.dSYM

