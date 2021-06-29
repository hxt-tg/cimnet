# CimNet

_Version: 0.1.4_

CimNet is a pure C++ library for simulations on complex networks.
It follows the standard of `C++11`.

CimNet provides features below:

- easy-to-use tools for creation and modification of complex networks;
- storing self-defined data into nodes and edges;
- several implementations of typical networks;
- the ability to inherit and expand your own network structures.

## Install

CimNet has no necessary to be installed.
Follow these steps to code with CimNet:

1. Clone this repository;
2. Copy the directory `cimnet` to your project;
3. Add `/path/to/your/project` to include directory configuration.
If you use `g++` as your project compiler, compile single file with
```sh
g++ xxx.cc -o xxx.out -std=c++11 -O2 -I /path/to/your/project
```

## Simple usage

Construct a regular network with 10 nodes and 3 clockwise links for each node.
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

Public documentation could be found at **docs/zh-cn.md**. (We only have Chinese version currently. You may need some translator to read.)

Documentation was written by [Haroopad](http://pad.haroopress.com/). (You may have better experience if you installed it.)

## Contributor

Developer: Xintao Hu ([@hxt-tg](https://github.com/hxt-tg),
email: [hxt.taoge@gmail.com](mailto:hxt.taoge@gmail.com))

Review & part of docs: Jialong Sun ([@jl-sun](https://github.com/jl-sun))
email: [sunjialong9@gmail.com](mailto:sunjialong9@gmail.com))


## Bug reports

Report bugs in
[GitHub issues](https://github.com/hxt-tg/cimnet/issues).

## License

CimNet is released under the GNU General Public License Version 3 (GPLv3).

```
Copyright (C) 2021 CimNet Developers
Xintao Hu <hxt.taoge@gmail.com>
```
