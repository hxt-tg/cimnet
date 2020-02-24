# CimNet

_Version: 0.1.0_

CimNet is a pure C++ library for simulations on complex networks.
It follow the standard of `C++11`.

CimNet provides features below:

- easy-to-use tools for creation and modification of complex networks;
- storing self-defined data into nodes and edges;
- several implementations of typical networks;
- the ability to inherite and expand your own network structures.

## Install

CimNet has no necessary to be installed.
Follow these steps to code with CimNet:

1. Clone this repository;
2. Copy the directory `cimnet` to your project;
3. Add `/path/to/your/project` to include directory configuration.
If you use `g++` as your project compiler, compile single file with
```sh
g++ xxx.cc -o xxx.out -std=c++11 -O2 -I /path/to/cimnet
```

## Simple usage

Construct an regular network with 10 nodes and 3 clockwise links for each node.
Then we print network info and neighbors of node 1.

```cpp
#include "cimnet/network.h"

int main(void) {
    RegularNetwork<> net(10, 3);
    std::cout << net << std::endl;
    std::cout << "Neighbors of node 1: ";
    for (auto n : net.neighbors(1))
        std::cout << n << " ";
    std::cout << std::endl;
    return 0;
}
```

## Contributor

Developer: Xintao Hu ([@hxt-tg](https://github.com/hxt-tg),
email: [hxt.taoge@gmail.com](mailto:hxt.taoge@gmail.com))

Code review: Jialong Sun ([@jl-sun](https://github.com/jl-sun))
email: [sunjialong9@gmail.com](mailto:sunjialong9@gmail.com))

(We are at the stage of internal test. If you want to contribute to this
project, send mails to @hxt-tg.)

## Bug reports

CimNet is a private repository until adequately tested.
However, please report any bugs via email to contributors.

If you are one of contributors, report bugs in
[GitHub issues](https://github.com/hxt-tg/cimnet/issues).

## License

CimNet is released under the GNU General Public License Version 3 (GPLv3).

```
Copyright (C) 2020 CimNet Developers
Xintao Hu <hxt.taoge@gmail.com>
```
