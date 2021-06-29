/*
 * This file contains code from https://github.com/hxt-tg/cimnet
 * and is covered under the copyright and warranty notices:
 * "Copyright (C) 2021 CimNet Developers
 *  Xintao Hu <hxt.taoge@gmail.com>"
 */

/*
 *  This file contains io processing, such as loading and saving networks.
 *  For further usage, check out http://doc.hxtcloud.cn.
 */

#ifndef CIMNET_IO
#define CIMNET_IO

#include "_base_net.h"
#include <fstream>

template<class _NId=Id, class _NData=None, class _EData=None>
void save_edge_list(std::ostream &out, const Network<_NId, _NData, _EData> &net,
                    const char *delimiter = ",") {
    if (!out) return;
    for (auto &e : net.edges())
        out << e.first << delimiter << e.second << "\n";
}

template<class _NId=Id, class _NData=None, class _EData=None>
void save_edge_list(std::ostream &out, const DirectedNetwork<_NId, _NData, _EData> &net,
                    const char *delimiter = ",") {
    if (!out) return;

    for (auto &e : net.edges())
        out << e.first << delimiter << e.second << "\n";
}

template<class _NId=Id, class _NData=None, class _EData=None>
void save_adjacency_list(std::ostream &out, const Network<_NId, _NData, _EData> &net,
                         const char *delimiter = ",") {
    if (!out) return;
    for (auto &node : net.nodes()) {
        out << node;
        if (net.degree(node) == 0) out << delimiter;
        for (auto &n : net.neighbors(node))
            out << delimiter << n;
        out << "\n";
    }
}

template<class _NId=Id, class _NData=None, class _EData=None>
void save_adjacency_list(std::ostream &out, const DirectedNetwork<_NId, _NData, _EData> &net,
                         const char *delimiter = ",") {
    if (!out) return;
    for (auto &node : net.nodes()) {
        out << node;
        if (net.degree(node) == 0) out << delimiter;
        for (auto &n : net.successors(node))
            out << delimiter << n;
        out << "\n";
    }
}

template<class _NId=Id, class _NData=None, class _EData=None>
void save_adjacency_matrix(std::ostream &out, const Network<_NId, _NData, _EData> &net,
                           const std::vector<_NId> &node_list, const char *delimiter = ",", bool keep_headers = true) {
    if (!out) return;
    if (keep_headers) {
        for (auto &n : node_list)
            out << delimiter << n;
        out << "\n";
    }

    for (auto i = 0UL; i < node_list.size(); i++) {
        if (keep_headers)
            out << node_list[i] << delimiter;
        for (auto j = 0UL; j < node_list.size(); j++)
            out << "01"[net.is_neighbor(node_list[i], node_list[j])] << (j == node_list.size()-1 ? "\n" : delimiter);
    }
}

template<class _NId=Id, class _NData=None, class _EData=None>
void save_adjacency_matrix(std::ostream &out, const Network<_NId, _NData, _EData> &net,
                           const char *delimiter = ",", bool keep_headers = true) {
    save_adjacency_matrix(out, net, net.nodes(), delimiter, keep_headers);
}

template<class _NId=Id, class _NData=None, class _EData=None>
void save_adjacency_matrix(std::ostream &out, const DirectedNetwork<_NId, _NData, _EData> &net,
                           const std::vector<_NId> &node_list, const char *delimiter = ",", bool keep_headers = true) {
    if (!out) return;
    if (keep_headers) {
        for (auto &n : node_list)
            out << delimiter << n;
        out << "\n";
    }

    for (auto i = 0UL; i < node_list.size(); i++) {
        if (keep_headers)
            out << node_list[i] << delimiter;
        for (auto j = 0UL; j < node_list.size(); j++)
            out << "01"[net.has_successor(node_list[i], node_list[j])] << (j == node_list.size()-1 ? "\n" : delimiter);
    }
}

template<class _NId=Id, class _NData=None, class _EData=None>
void save_adjacency_matrix(std::ostream &out, const DirectedNetwork<_NId, _NData, _EData> &net,
                           const char *delimiter = ",", bool keep_headers = true) {
    save_adjacency_matrix(out, net, net.nodes(), delimiter, keep_headers);
}


#endif /* ifndef CIMNET_IO */
