#include <iostream>
#include <chrono>
#include "cimnet/network.h"
#include "cimnet/_base_net.h"

using namespace std::chrono;

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
                << net(e.first, e.second).desc
                << "  amount=" << net(e.first, e.second).amount
                << std::endl;
        } catch (const NetworkException &e) {
            std::cout << e.what() << std::endl;
            continue;
        }
    }
}

void test_construct_net(void) {
    FullConnectedNetwork<int, KindOfData> net(3);
    net.add_edge(2, 1, {"123", 3});
    net.node(1) = 5;
    net(1, 2).amount = 1;
    net(1, 2).amount = 1;
    net[0] = 3;   // Same as net.node(0) = 3;
    net.add_edge(1, 3, {"new node", 1});
    std::cout << "Neighbor of 1: ";
    for (auto n : net.neighbors(1))
        std::cout << n << " ";
    std::cout << std::endl << std::endl;
    print_node_edge_data(net, "net");

    Network<int, int, KindOfData> net_copy(net);
    net_copy(1, 3).desc = "update by copy";
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
        FullConnectedNetwork<> net(1000);
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
                << net(e.first, e.second).desc
                << "  amount=" << net(e.first, e.second).amount
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
                << net2(e.first, e.second).desc
                << "  amount=" << net2(e.first, e.second).amount
                << std::endl;
}

void test_copy_constructor() {
    Network<int, std::string, std::string> n;
    n.add_edge(1, 2, "1 to 2");
    n.add_edge(1, 3, "1 to 3");
    n[1] = "Node 1";
    n[2] = "Node 2";
    n[3] = "Node 3";
    DirectedNetwork<int, std::string, std::string> dn(n);
    std::cout << "Network (copied):" << std::endl;
    for (auto i: dn.nodes())
        std::cout << " Node " << i << "   data=" << dn.node(i) << std::endl;
    for (auto e: dn.edges())
        std::cout << "[" << e.first << "->" << e.second << "] data="
                  << dn(e.first, e.second)
                  << std::endl;
}

void test_random_neighbor() {
    Network<int, std::string, std::string> n;
    n.add_edge(1, 2, "1 to 2");
    n.add_edge(1, 3, "1 to 3");
    n.add_edge(1, 4, "1 to 3");
    n.add_edge(1, 8, "1 to 3");
    n[1] = "Node 1";
    n[2] = "Node 2";
    n[3] = "Node 3";
    n[4] = "Node 4";
    n[8] = "Node 8";
    DirectedNetwork<int, std::string, std::string> dn(n);
    std::cout << " Node " << 1 << "'s random successors:";
    for (auto i = 0; i < 10; i++)
        std::cout << " " << dn.random_successor(1);
    std::cout << std::endl;
}

void test_performance_neighbors(Network<int> &net) {
    auto start = high_resolution_clock::now();
    for (auto i = 0; i < 100000; i++)
        for (const auto &n : net.neighbors(1))
            net.degree(n);
    auto duration = (double)duration_cast<microseconds>(high_resolution_clock::now() - start).count()*
                    microseconds::period::num / microseconds::period::den;
    std::cout << "Neighbors: " << duration << " seconds.\n";
}

void test_performance_iterate_neighbors(Network<int> &net) {
    auto start = high_resolution_clock::now();
    for (auto i = 0; i < 100000; i++)
        for (const auto &n : net.iterate_neighbors(1))
            net.degree(n);
    auto duration = (double)duration_cast<microseconds>(high_resolution_clock::now() - start).count()*
                    microseconds::period::num / microseconds::period::den;
    std::cout << "Iterate neighbors: " << duration << " seconds.\n";
}

void test_performance_iterate_nodes_view(Network<int> &net) {
    std::cout << "Copying directed network...\n";
    auto start = high_resolution_clock::now();
    DirectedNetwork<int> di_net(net);
    for (auto i = 0; i < 1000; i++) {
        for (const auto &n : net.iterate_nodes())
            net.degree(n);
    }
    auto duration = (double)duration_cast<microseconds>(high_resolution_clock::now() - start).count()*
                    microseconds::period::num / microseconds::period::den;
    std::cout << "Iterate nodes in DirectedNetwork: " << duration << " seconds.\n";
}

void temp() {
}

int main() {
//    test_construct_net();
//    test_modify_net();
//    test_efficiency();
//    test_properties();
//    test_directed_network();
//    test_copy_constructor();
//    test_random_neighbor();

    auto start = high_resolution_clock::now();
    FullConnectedNetwork<> net(5000);
    auto duration = (double)duration_cast<microseconds>(high_resolution_clock::now() - start).count()*
            microseconds::period::num / microseconds::period::den;
    std::cout << "Construct 1000 full connected: " << duration << " seconds.\n";

//    test_performance_neighbors(net);
//    test_performance_iterate_neighbors(net);
    test_performance_iterate_nodes_view(net);

    return 0;
}

