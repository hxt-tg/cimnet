#include <iostream>
#include "cimnet/network.h"

typedef struct {
    std::string desc;
    int amount;
} KindOfData;


int main(void) {
    WellMixNet<int, KindOfData> net(3);
    net.add_edge(2, 1, {"123", 3});
    net.node(1) = 5;
    net.edge(1, 2).amount = 1;
    net.edge(1, 2).amount = 1;
    net.node(0) = 3;

    std::cout << "Node data:" << std::endl;
    for (auto i = 0; i < net.number_of_nodes(); i++)
        std::cout << " Node " << i << "   data=" << net.node(i) << std::endl;
    std::cout << "Edge data:" << std::endl;
    for (auto i = 0; i < net.number_of_nodes(); i++)
        for (auto j = 0; j < net.number_of_nodes(); j++)
            try {
            std::cout << "[" << i << "->" << j << "] desc="
                << net.edge(i, j).desc << "  amount=" << net.edge(i, j).amount
                << std::endl;
    } catch (const NetworkException &e) {
        /* std::cout << e.what() << std::endl; */
        continue;
    }
    return 0;
}


