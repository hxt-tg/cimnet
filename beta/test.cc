#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <exception>
#include <vector>

typedef double Weight;
typedef unsigned int Id;

class _NoneType {};

class NetworkException : public std::exception {
    public:
        NetworkException() : _info("Network error: ") {}
        NetworkException(const std::string &info) : _info("Network error: " + info) {}
        void set_info(const std::string &info) {
            _info = std::string("Network error: " + info);
        }
        const char *what() const noexcept {
            return _info.c_str();
        }
    public:
        std::string _info;
};

template <class _NId=Id>
class NoEdgeException : public NetworkException {
    public:
        NoEdgeException(const _NId &id1, const _NId &id2) {
            std::stringstream stream;
            stream << "No edge between " << id1 <<
                " and " << id2 << ".";
            set_info(stream.str());
        }
};

template <class _NId=Id>
class NoNodeException: public NetworkException {
    public:
        NoNodeException(const _NId &id) {
            std::stringstream stream;
            stream << "Node " << id << " not found.";
            set_info(stream.str());
        }
};

template <class _NId=Id, class _NData=_NoneType, class _EData=_NoneType>
class UndirectedNet;

template <class _NId, class _NData, class _EData>
class UndirectedNet {
    typedef std::unordered_map<_NId, _NData> _NType;
    typedef std::unordered_map<_NId, _EData *> _NeiType;
    typedef std::unordered_map<_NId, _NeiType> _AdjType;

    public:
    UndirectedNet (): _nodes(), _adjs() {}
    ~UndirectedNet () {
        for (auto adj: _adjs) {
            for (auto n: adj.second)
                delete n.second;
            adj.second.clear();
        }
    }

    inline void add_node(const _NId &id, const _NData &node_data=_NData()) {
        _nodes[id] = node_data;
        _adjs[id] = _NeiType();
    }

    inline void add_edge(const _NId &id1, const _NId &id2, const _EData &edge_data=_EData()) {
        if (!has_node(id1)) add_node(id1);
        if (!has_node(id2)) add_node(id2);
        _EData *data_ptr = new _EData();
        *data_ptr = edge_data;
        _adjs[id1][id2] = data_ptr;
        _adjs[id2][id1] = data_ptr;
    }

    inline void remove_edge(const _NId &id1, const _NId &id2) {
        if (!has_node(id1) || !has_node(id2))
            return ;
        _EData *data_ptr = _adjs.at(id1).at(id2);
        delete data_ptr;
        _NeiType nei = _adjs.at(id1);
        nei.erase(nei.find(id2));
        nei = _adjs.at(id2);
        nei.erase(nei.find(id1));
    }

    inline void remove_node(const _NId &id) {
        if (!has_node(id)) return ;
        for (auto n : _adjs.at(id))
            remove_edge(id, n.first);
        _adjs.erase(_adjs.find(id));
    }

    inline bool has_node(const _NId &id) {
        return _nodes.find(id) != _nodes.end();
    }

    inline bool has_edge(const _NId &id1, const _NId &id2) {
        if (!has_node(id1) || !has_node(id2))
            return false;
        return _adjs[id1].find(id2) != _adjs[id1].end();
    }

    inline bool is_neighbor(const _NId &id1, const _NId &id2) {
        return has_edge(id1, id2);
    }

    inline _NData &node(const _NId &id) {
        return _nodes.at(id);
    }

    inline _EData &edge(const _NId &id1, const _NId &id2) {
        if (!has_node(id1))
            throw NoNodeException<_NId>(id1);
        if (!has_node(id2))
            throw NoNodeException<_NId>(id2);
        try {
            return *(_adjs.at(id1).at(id2));
        } catch (std::exception e){
            throw NoEdgeException<_NId>(id1, id2);
        }
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

    _NeiType &operator[](const _NId &id) {
        return _adjs.at(id);
    }

    private:
    _NType _nodes;
    _AdjType _adjs;
};


template <class _NData=_NoneType, class _EData=_NoneType>
class WellMixNet;
template <class _NData, class _EData>
class WellMixNet
: public UndirectedNet<int, _NData, _EData>{
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
            /* try { */
            std::cout << "[" << i << "->" << j << "] desc="
                << net.edge(i, j).desc << "  amount=" << net.edge(i, j).amount
                << std::endl;
    /* } catch (const NetworkException &e) { */
    /*     /1* std::cout << e.what() << std::endl; *1/ */
    /*     continue; */
    /* } */
    return 0;
}


