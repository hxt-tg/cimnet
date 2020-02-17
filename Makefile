# Project: cimnet

vpath %.h cimnet
vpath %.cc src

CPP       = g++
HEADERS   = _types.h _base_net.h _exception.h random.h network.h
LIBS      = -static-libgcc
INC       = -I .
CPPFLAGS  = -std=c++11 -Wall -Wextra -g

.PHONY: all clean test

# Release
all: test

test: test/test_base.cc
	$(CPP) test/test_base.cc -o test_base.run $(INC) $(CPPFLAGS)


# Clean
clean:
	rm -rf *.o *.run

