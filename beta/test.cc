#include <iostream>
#include <unordered_map>
#include <exception>
#include <vector>

typedef unsigned int NodeId;
typedef double NodeWeight;
typedef double EdgeWeight;
typedef std::unordered_map<NodeId, NodeWeight> Nodes;
typedef std::unordered_map<NodeId, EdgeWeight> Neighbors;
typedef std::unordered_map<NodeId, Neighbors> Adjacency;

// Fake definition
typedef std::pair<NodeId, NodeWeight> _Node;
typedef std::pair<std::pair<NodeId, NodeId>, EdgeWeight> _Edge;

class UndirectedNet {
    public:
        UndirectedNet ()
            : nodes(), adjs() {}
        ~UndirectedNet () {
            for (auto adj: adjs)
                adj.second.clear();
        }

        void add_node(NodeId idx, NodeWeight weight=1.0) {
            if (nodes.find(idx) != nodes.end())
                return ;
            nodes[idx] = weight;
            Neighbors neighbor;
            adjs[idx] = neighbor;
        }

        void add_edge(NodeId idx1, NodeId idx2, EdgeWeight weight=1.0) {
            if (nodes.find(idx1) == nodes.end())
                add_node(idx1);
            if (nodes.find(idx2) == nodes.end())
                add_node(idx2);
            adjs[idx1][idx2] = weight;
            adjs[idx2][idx1] = weight;
        }

        bool is_neighbor(NodeId idx1, NodeId idx2) {
            if (nodes.find(idx1) == nodes.end() || nodes.find(idx2) == nodes.end())
                return false;
            Neighbors nei1 = adjs[idx1];
            return nei1.find(idx2) != nei1.end();
        }

        void print() {
            std::cout << "Node info:" << std::endl;
            for (auto n: nodes) {
                std::cout << " " << n.first <<
                    ", " << n.second << std::endl;
            }
            std::cout << "info:" << std::endl;
            for (auto adj: adjs) {
                std::cout << " Node "  << adj.first << std::endl;
                for (auto n: adj.second) {
                    std::cout << "  " << n.first <<
                        ", " << n.second << std::endl;
                }
            }
        }

    private:
        Nodes nodes;
        Adjacency adjs;
};


class WellMixNet : public UndirectedNet {
    public:
        WellMixNet(int num){
            for (int i = 0; i < num; i++)
                for (int j = i+1; j < num; j++)
                    add_edge(i, j);
        }

};


int main(void) {
    for (int i = 0; i < 30; ++i) {
        WellMixNet net(600);
        /* std::cout << i << std::endl; */
    }

    return 0;
}


