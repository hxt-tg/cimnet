#include <iostream>
#include <string>
#include <unordered_map>
#include <exception>
#include <vector>

typedef double Weight;
typedef unsigned int Id;
class NoneType {};

template <class NodeId=Id, class NodeData=NoneType, class EdgeData=NoneType>
class UndirectedNet;

template <class NodeId, class NodeData, class EdgeData>
class UndirectedNet {
    typedef std::unordered_map<NodeId, NodeData> Nodes;
    typedef std::unordered_map<NodeId, EdgeData> Neighbors;
    typedef std::unordered_map<NodeId, Neighbors> Adjacency;

    public:
    UndirectedNet (): _nodes(), _adjs() {}
    ~UndirectedNet () {
        for (auto adj: _adjs)
            adj.second.clear();
    }

    inline void add_node(const NodeId id, const NodeData data=NodeData()) {
        _nodes[id] = data;
        Neighbors neighbor;
        _adjs[id] = neighbor;
    }

    inline void add_edge(const NodeId id1, const NodeId id2, const EdgeData &data=EdgeData()) {
        if (!has_node(id1)) add_node(id1);
        if (!has_node(id2)) add_node(id2);
        _adjs[id1][id2] = data;
        _adjs[id2][id1] = data;
    }

    inline bool has_node(const NodeId id) {
        return _nodes.find(id) != _nodes.end();
    }

    inline bool is_neighbor(const NodeId id1, const NodeId id2) {
        if (!has_node(id1) || !has_node(id2))
            return false;
        return _adjs[id1].find(id2) != _adjs[id1].end();
    }

    void print() {
        std::cout << "Node info:" << std::endl;
        for (auto n: _nodes) {
            std::cout << " " << n.first <<
                ", " << n.second << std::endl;
        }
        std::cout << "info:" << std::endl;
        for (auto adj: _adjs) {
            std::cout << " Node "  << adj.first << std::endl;
            for (auto n: adj.second) {
                std::cout << "  " << n.first <<
                    ", " << n.second << std::endl;
            }
        }
    }

    inline Nodes &nodes() {
        return _nodes;
    }

    inline int number_of_nodes() {
        return _nodes.size();
    }

    inline int number_of_edges() {
        int num = 0;
        for (auto adj : _adjs)
            num += adj.second.size();
        return num;
    }

    Neighbors &operator[](const NodeId id) {
        return _adjs.at(id);
    }

    private:
    Nodes _nodes;
    Adjacency _adjs;
};


template <class NodeData=NoneType, class EdgeData=NoneType>
class WellMixNet;
template <class NodeData, class EdgeData>
class WellMixNet
: public UndirectedNet<int, NodeData, EdgeData>{
    public:
        WellMixNet(int num){
            for (int i = 0; i < num; i++)
                for (int j = i+1; j < num; j++)
                    this->add_edge(i, j);
        }
};

typedef struct {
    std::string desc;
    int amount;
} KindOfData;

int main(void) {
    WellMixNet<int, KindOfData> net(3);
    net.nodes()[1] = 5;
    net.add_edge(2, 1, {"123", 3});
    // TODO: Ban this way to assign.
    net[0][1].amount = 3;

    std::cout << "Node data:" << std::endl;
    for (auto i = 0; i < net.number_of_nodes(); i++)
        std::cout << " Node " << i << "   data=" << net.nodes()[i] << std::endl;
    std::cout << "Edge data:" << std::endl;
    for (auto i = 0; i < net.number_of_nodes(); i++)
        for (auto j = 0; j < net.number_of_nodes(); j++)
            std::cout << "[" << i << "->" << j << "] desc="
                << net[i][j].desc << "  amount=" << net[i][j].amount
                << std::endl;
    return 0;
}


