#include <iostream>
#include "cimnet/network.h"
#include "cimnet/_base_net.h"

typedef struct {
    std::string desc;
    int amount;
} KindOfData;


void test_construct_net(void) {
    WellMixNet<int, KindOfData> net(3);
    net.add_edge(2, 1, {"123", 3});
    net.node(1) = 5;
    net.edge(1, 2).amount = 1;
    net.edge(1, 2).amount = 1;
    net.node(0) = 3;
    net.add_edge(1, 3, {"new node", 1});
    std::cout << "Neighbor of 1: ";
    for (auto n : net.neighbors(1))
        std::cout << n << " ";
    std::cout << std::endl << std::endl;

    std::cout << "Node data:" << std::endl;
    for (auto i: net.nodes())
        std::cout << " Node " << i << "   data=" << net.node(i) << std::endl;

    std::cout << "Edge data:" << std::endl;
    for (auto e: net.edges()) {
        try {
            std::cout << "[" << e.first << "->" << e.second << "] desc="
                << net.edge(e.first, e.second).desc
                << "  amount=" << net.edge(e.first, e.second).amount
                << std::endl;
        } catch (const NetworkException &e) {
            std::cout << e.what() << std::endl;
            continue;
        }
    }
    std::cout << "End..." << std::endl;
}

void test_modify_net() {
    Network<int, int, KindOfData> n;
    n.add_edge(1, 0);
    n.add_edge(2, 0);
    n.add_edge(3, 0);
    n.add_edge(2, 3);

    std::cout << "Node data:" << std::endl;
    for (auto i: n.nodes())
        std::cout << " Node " << i << "   data=" << n.node(i) << std::endl;

    std::cout << "Edges: " << std::endl;
    for (auto nei: n.edges())
        std::cout << " " << nei.first << "-" << nei.second << std::endl;

    n.remove_node(0);

    std::cout << "============ Remove node 0 ============" << std::endl;
    std::cout << "Node data:" << std::endl;
    for (auto i: n.nodes())
        std::cout << " Node " << i << "   data=" << n.node(i) << std::endl;

    std::cout << "Edges: " << std::endl;
    for (auto nei: n.edges())
        std::cout << " " << nei.first << "-" << nei.second << std::endl;

    n.remove_edge(2, 3);

    std::cout << "============ Remove edge 2-3 ============" << std::endl;
    std::cout << "Node data:" << std::endl;
    for (auto i: n.nodes())
        std::cout << " Node " << i << "   data=" << n.node(i) << std::endl;

    std::cout << "Edges: " << std::endl;
    for (auto nei: n.edges())
        std::cout << " " << nei.first << "-" << nei.second << std::endl;
}

int main(void) {
    test_construct_net();
    test_modify_net();
    return 0;
}

