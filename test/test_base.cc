#include <iostream>
#include "cimnet/network.h"
#include "cimnet/_base_net.h"

typedef struct {
    std::string desc;
    int amount;
} KindOfData;


void print_node_edge_data(Network<int, int, KindOfData> &net,
        std::string tag) {
    std::cout << "Node data: (" << tag << ")" << std::endl;
    for (auto i: net.nodes())
        std::cout << " Node " << i << "   data=" << net.node(i) << std::endl;
    std::cout << "Edge data: (" << tag << ")" << std::endl;
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
}

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
    print_node_edge_data(net, "net");

    Network<int, int, KindOfData> net_copy(net);
    net_copy.edge(1, 3).desc = "update by copy";
    net_copy[1] = 999;
    std::cout << "=================" << std::endl;
    print_node_edge_data(net, "net origin");
    std::cout << "=================" << std::endl;
    print_node_edge_data(net_copy, "net copy");
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

void test_efficiency() {
    for (int i = 0; i < 30; i++)
        WellMixNet<> net(1000);
    std::cout << "Done." << std::endl;
}

void test_properties() {
    Network<> n;
    n.add_edge(1, 2);
    n.add_edge(1, 3);
    for (auto adj : n.adjacency())
        for (auto nei : adj.second)
            std::cout << adj.first << "-" << nei.first << std::endl;
    std::cout << n << std::endl;
}

void test_directed_network() {
    DirectedNetwork<int, Weight, KindOfData> net;
    net.add_edge(1, 2, {"I to II", 1});
    net.add_edge(3, 2, {"III to II", 2});
    net[1] = 2.3;
    net[3] = 4.5;
    std::cout << "Network (raw):" << std::endl;
    for (auto i: net.nodes())
        std::cout << " Node " << i << "   data=" << net.node(i) << std::endl;
    for (auto e: net.edges())
            std::cout << "[" << e.first << "->" << e.second << "] desc="
                << net.edge(e.first, e.second).desc
                << "  amount=" << net.edge(e.first, e.second).amount
                << std::endl;
    DirectedNetwork<int, Weight, KindOfData> net2(net);
    net2[2] = 9.9;
    net2.add_edge(2, 2, {"Self loop", 0});
    net2.add_edge(2, 2, {"Self loop second", 9});
    net2.remove_node(2);
    std::cout << "Network (copied):" << std::endl;
    for (auto i: net2.nodes())
        std::cout << " Node " << i << "   data=" << net2.node(i) << std::endl;
    for (auto e: net2.edges())
            std::cout << "[" << e.first << "->" << e.second << "] desc="
                << net2.edge(e.first, e.second).desc
                << "  amount=" << net2.edge(e.first, e.second).amount
                << std::endl;
}

int main(void) {
    /* test_construct_net(); */
    /* test_modify_net(); */
    /* test_efficiency(); */
    /* test_properties(); */
    test_directed_network();
    return 0;
}

