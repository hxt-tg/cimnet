#ifndef CIMNET_BASE_NET
#define CIMNET_BASE_NET

#include <unordered_map>

#include "_types.h"
#include "_exception.h"

template <class _NId=Id, class _NData=_NoneType, class _EData=_NoneType>
class Network;

template <class _NId, class _NData, class _EData>
class Network {
    typedef std::unordered_map<_NId, _NData> _NType;
    typedef std::unordered_map<_NId, _EData *> _NeiType;
    typedef std::unordered_map<_NId, _NeiType> _AdjType;

    public:
    Network (): _nodes(), _adjs() {}
    ~Network () {
        for (auto adj: _adjs)
            remove_node(adj.first);
    }


    void add_node(const _NId &id, const _NData &node_data=_NData()){
        _nodes[id] = node_data;
        _adjs[id] = _NeiType();
    }

    void add_edge(const _NId &id1, const _NId &id2, const _EData &edge_data=_EData()){
        if (!has_node(id1)) add_node(id1);
        if (!has_node(id2)) add_node(id2);
        _EData *data_ptr = new _EData();
        *data_ptr = edge_data;
        _adjs[id1][id2] = data_ptr;
        _adjs[id2][id1] = data_ptr;
    }

    void remove_edge(const _NId &id1, const _NId &id2){
        if (!has_node(id1) || !has_node(id2))
            return ;
        _EData *data_ptr = _adjs.at(id1).at(id2);
        delete data_ptr;
        _NeiType nei = _adjs.at(id1);
        nei.erase(nei.find(id2));
        nei = _adjs.at(id2);
        nei.erase(nei.find(id1));
    }

    void remove_node(const _NId &id){
        if (!has_node(id)) return ;
        for (auto n : _adjs.at(id))
            remove_edge(id, n.first);
        _adjs.erase(_adjs.find(id));
    }

    bool has_node(const _NId &id){
        return _nodes.find(id) != _nodes.end();
    }

    bool has_edge(const _NId &id1, const _NId &id2){
        if (!has_node(id1) || !has_node(id2))
            return false;
        return _adjs[id1].find(id2) != _adjs[id1].end();
    }

    bool is_neighbor(const _NId &id1, const _NId &id2) {
        return has_edge(id1, id2);
    }

    _NData &node(const _NId &id){
        return _nodes.at(id);
    }

    _EData &edge(const _NId &id1, const _NId &id2){
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

    int number_of_nodes(){
        return _nodes.size();
    }

    int number_of_edges(){
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

// TODO: DirectedNetwork

#endif /* ifndef CIMNNET_BASE_NET */
