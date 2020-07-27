# Project: cimnet

vpath %.h cimnet
vpath %.cc src

VERSION   = 0.1.3
CPP       = g++
HEADERS   = _types.h _base_net.h _exception.h random.h network.h
LIBS      = -static-libgcc
INC       = -I .
OPT_LEVEL = -O3
CPPFLAGS  = -std=c++11 -Wall -Wextra $(OPT_LEVEL)

.PHONY: all clean

all: test_base.out test_network.out

clean:
	rm -rf *.o *.out release

test_base.out: test/test_base.cc $(HEADERS)
	$(CPP) test/test_base.cc -o test_base.out $(INC) $(CPPFLAGS)
test_network.out: test/test_network.cc $(HEADERS)
	$(CPP) test/test_network.cc -o test_network.out $(INC) $(CPPFLAGS)
