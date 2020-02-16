TGT_TEST    = test.out
OPTM_LEVEL  = -O3
CPPFLAGS    = --std=c++11 $(OPTM_LEVEL) -g
INC         =


.PHONY: all clean

all: $(TGT_TEST)

clean:
	rm -f *.out *.o

$(TGT_TEST): test.cc
	g++ -o $(TGT_TEST) $(CPPFLAGS) test.cc $(INC)


