# Project: cimnet

vpath %.h cimnet
vpath %.cc src

VERSION   = 0.1.4
CPP       = g++
HEADERS   = _types.h _base_net.h _exception.h random.h network.h
LIBS      = -static-libgcc
INC       = -I ..
OPT_LEVEL = -O3
CPPFLAGS  = -std=c++11 -Wall -Wextra $(OPT_LEVEL)

.PHONY: all clean

all: test

clean:
	rm -rf bin

test: test_base.cc $(HEADERS)
	$(CPP) test_base.cc -o bin/test_base.out $(INC) $(CPPFLAGS)
	$(CPP) test_network.cc -o bin/test_network.out $(INC) $(CPPFLAGS)
