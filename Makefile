# Project: cimnet

vpath %.h cimnet
vpath %.cc src

CPP       = g++
HEADERS   = _types.h _base_net.h _exception.h random.h network.h
LIBS      = -static-libgcc
INC       = -I .
OPT_LEVEL = -O3
CPPFLAGS  = -std=c++11 -Wall -Wextra $(OPT_LEVEL)

.PHONY: all clean test

all: test

clean:
	rm -rf *.o *.out

test: test/test_base.cc
	$(CPP) test/test_base.cc -o test_base.out $(INC) $(CPPFLAGS)

