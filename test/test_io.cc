#include <iostream>
#include <fstream>
#include "cimnet/network.h"
#include "cimnet/_base_net.h"
#include "cimnet/io.h"

void test_save_edge_list(const Network<int> &net) {
    std::cout << "Testing writing edge list of network ...\n";
    std::ofstream out("test_edges.csv", std::ios::out);
    save_edge_list(out, net);
    out.close();
}

void test_save_edge_list(const DirectedNetwork<int> &net) {
    std::cout << "Testing writing edge list of directed network ...\n";
    std::ofstream out("test_edges.csv", std::ios::out);
    save_edge_list(out, net);
    out.close();
}

void test_save_adj_list(const Network<int> &net) {
    std::cout << "Testing writing adjacency list of network ...\n";
    std::ofstream out("test_adj_list.csv", std::ios::out);
    save_adjacency_list(out, net);
    out.close();
}

void test_save_adj_list(const DirectedNetwork<int> &net) {
    std::cout << "Testing writing adjacency list of directed network ...\n";
    std::ofstream out("test_adj_list.csv", std::ios::out);
    save_adjacency_list(out, net);
    out.close();
}

void test_save_adj_matrix(const Network<int> &net) {
    std::cout << "Testing writing adjacency matrix of network ...\n";
    std::ofstream out("test_adj_matrix.csv", std::ios::out);
    save_adjacency_matrix(out, net);
    out.close();
}

void test_save_adj_matrix(const DirectedNetwork<int> &net) {
    std::cout << "Testing writing adjacency matrix of directed network ...\n";
    std::ofstream out("test_adj_matrix.csv", std::ios::out);
    save_adjacency_matrix(out, net);
    out.close();
}

int main() {
    DirectedNetwork<int> n;
    n.add_edge(1, 2);
    n.add_edge(1, 3);
    n.add_edge(4, 1);
    n.add_edge(2, 3);
    n.add_edge(2, 4);

    test_save_edge_list(n);
    test_save_adj_list(n);
    test_save_adj_matrix(n);

    return 0;
}

