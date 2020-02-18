# Examples of cimnet usage

CPP       = g++
INC       = -I ..
OPT_LEVEL = -O3
CPPFLAGS  = -std=c++11 -Wall -Wextra $(OPT_LEVEL)
EXAMPLES  = internet sir_model

EX_OUT    = $(foreach n, $(EXAMPLES), $n.out)

.PHONY: all clean

all: $(EX_OUT)

clean:
	rm -rf *.o *.out

$(EX_OUT): %.out : %.cc
	$(CPP) $< -o $@ $(INC) $(CPPFLAGS)

