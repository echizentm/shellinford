CC  = /usr/bin/g++
BIN = /usr/local/bin/
LIB = /usr/local/lib/
INC = /usr/local/include/
SRC = shellinford_bit_vector.cc
HDR = shellinford_bit_vector.h  shellinford_wavelet_tree.h
UNAME = $(shell uname)

libshellinford: $(SRC) $(HDR)
ifeq ($(UNAME), Darwin)
	$(CC) -O2 -fno-common -Wall -fPIC -g -c shellinford_bit_vector.cc
	$(CC) -O2 -Wall -g -dynamiclib \
          -install_name=$(LIB)libshellinford.1.0.dylib \
          -o libshellinford.1.0.dylib \
          shellinford_bit_vector.o
else
	$(CC) -O2 -Wall -fPIC -g -c shellinford_bit_vector.cc
	$(CC) -O2 -Wall -g -shared -Wl,-soname,libshellinford.so.1 \
          -o libshellinford.so.1.0 \
          shellinford_bit_vector.o
endif
	rm shellinford_bit_vector.o

clean:
	- rm -f libshellinford.so.1.0
	- rm -f libshellinford.1.0.dylib
	- rm -Rf *.dSYM

install:
ifeq ($(UNAME), Linux)
	cp libshellinford.so.1.0 $(LIB)
	/sbin/ldconfig -n $(LIB)
	ln -fs $(LIB)libshellinford.so.1 $(LIB)libshellinford.so
else
ifeq ($(UNAME), Darwin)
	cp libshellinford.1.0.dylib $(LIB)
	ln -fs $(LIB)libshellinford.1.0.dylib $(LIB)libshellinford.1.dylib
	ln -fs $(LIB)libshellinford.1.dylib $(LIB)libshellinford.dylib
else
	cp libshellinford.so.1.0 $(LIB)
	ln -fs $(LIB)libshellinford.so.1.0 $(LIB)libshellinford.so.1
	/sbin/ldconfig -m $(LIB)
	ln -fs $(LIB)libshellinford.so.1 $(LIB)libshellinford.so
endif
endif
	cp shellinford_*.h $(INC)

uninstall:
	- rm -f $(LIB)libshellinford.so
	- rm -f $(LIB)libshellinford.so.1
	- rm -f $(LIB)libshellinford.so.1.0
	- rm -f $(LIB)libshellinford.dylib
	- rm -f $(LIB)libshellinford.1.dylib
	- rm -f $(LIB)libshellinford.1.0.dylib
	- rm -f $(INC)shellinford_*.h

