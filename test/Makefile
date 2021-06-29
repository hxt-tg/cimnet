# Project: cimnet

vpath %.h ../cimnet
vpath %.cc src

VERSION   = 0.1.4
CPP       = g++
HEADERS   = _types.h _base_net.h _exception.h random.h network.h algorithms.h io.h
LIBS      = -static-libgcc
INC       = -I ..
OPT_LEVEL = -O3
CPPFLAGS  = -std=c++11 -Wall -Wextra $(OPT_LEVEL)

.PHONY: all clean

all: test_base.out test_network.out test_algorithms.out test_io.out

clean:
	rm -rf *.out *.csv

test_base.out: test_base.cc $(HEADERS)
	$(CPP) test_base.cc -o test_base.out $(INC) $(CPPFLAGS)

test_network.out: test_network.cc $(HEADERS)
	$(CPP) test_network.cc -o test_network.out $(INC) $(CPPFLAGS)

test_algorithms.out: test_algorithms.cc $(HEADERS)
	$(CPP) test_algorithms.cc -o test_algorithms.out $(INC) $(CPPFLAGS)

test_io.out: test_io.cc $(HEADERS)
	$(CPP) test_io.cc -o test_io.out $(INC) $(CPPFLAGS)
