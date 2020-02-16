# Project: cimnet

vpath %.h include
vpath %.cc src
vpath %.o bin

CPP       = g++
HEADERS   = _types.h _base_net.h _exception.h random.h network.h
LIBS      = -static-libgcc
INC       = -Iinclude
CPPFLAGS  = -std=c++11 -Wall -Wextra -g

.PHONY: all all-before all-release clean test

# Release
all: all-before all-release

all-before:
	mkdir -p bin _Release/cimnet

all-release:
	cp -f $(foreach n, $(HEADERS), include/$n) _Release/cimnet

test: test/test_base.cc
	$(CPP) test/test_base.cc -o bin/test_base.run -I _Release $(CPPFLAGS)


# Clean
clean:
	rm -rf bin _Release

