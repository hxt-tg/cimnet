#ifndef CIMNET_BASE_NET
#define CIMNET_BASE_NET

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "_types.h"
#include "_exception.h"



struct HashPair {
    template <class T1, class T2>
        std::size_t operator() (std::pair<T1, T2> const &p) const {
            std::size_t h1 = std::hash<T1>()(p.first);
            std::size_t h2 = std::hash<T2>()(p.second);
            return h1 ^ h2;
        }
};

template <class _NId=Id, class _NData=_NoneType, class _EData=_NoneType>
class Network;

template <class _NId, class _NData, class _EData>
class Network {
    typedef std::unordered_map<_NId, _NData> _NType;
    typedef std::pair<_NId, _NId> _EPairType;
    typedef std::unordered_map<_NId, _EData *> _NeiType;
    typedef std::unordered_map<_NId, _NeiType> _AdjType;
    typedef std::unordered_set<std::pair<_NId, _NId>, HashPair> _ESetType;

    public:
    Network (): _nodes(), _adjs() {}
    ~Network () {
        for (auto &n : nodes())
            remove_node(n);
    }

    inline _NId add_node(const _NId &id,
            const _NData &node_data=_NData()) {
        _nodes[id] = node_data;
        _adjs[id] = _NeiType();
        return id;
    }

    inline void add_edge(const _NId &id1, const _NId &id2,
            const _EData &edge_data=_EData()) {
        if (!has_node(id1)) add_node(id1);
        if (!has_node(id2)) add_node(id2);
        if (has_edge(id1, id2)) delete _adjs[id1][id2];
        _EData *data_ptr = new _EData();
        *data_ptr = edge_data;
        _adjs[id1][id2] = data_ptr;
        _adjs[id2][id1] = data_ptr;
    }

    inline void remove_edge(const _NId &id1, const _NId &id2) {
        if (!has_edge(id1, id2)) return ;
        _NeiType &nei1 = _adjs.at(id1);
        _NeiType &nei2 = _adjs.at(id2);
        _EData *data_ptr = nei1.at(id2);
        delete data_ptr;
        nei1.erase(nei1.find(id2));
        nei2.erase(nei2.find(id1));
    }

    inline void remove_node(const _NId &id) {
        if (!has_node(id)) throw NoNodeException<_NId>(id);
        for (auto &n : neighbors(id))
            remove_edge(id, n);
        _adjs.erase(_adjs.find(id));
        _nodes.erase(_nodes.find(id));
    }

    inline bool has_node(const _NId &id) const {
        return _nodes.find(id) != _nodes.end();
    }

    inline bool has_edge(const _NId &id1, const _NId &id2) const {
        if (!has_node(id1) || !has_node(id2))
            return false;
        return _adjs.at(id1).find(id2) != _adjs.at(id1).end();
    }

    inline bool is_neighbor(const _NId &id1, const _NId &id2) const {
        return has_edge(id1, id2);
    }

    inline _NData &node(const _NId &id) {
        if (!has_node(id))
            throw NoNodeException<_NId>(id);
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

    inline int number_of_nodes() const {
        return _nodes.size();
    }

    inline int number_of_edges() const {
        int num = 0;
        for (auto &adj : _adjs)
            num += adj.second.size();
        return num;
    }

    inline int degree(const _NId &id) {
        if (!has_node(id)) return 0;
        return _adjs.at(id).second.size();
    }

    inline std::vector<_NId> neighbors(const _NId &id) const {
        std::vector<_NId> nei;
        if (has_node(id))
            for (auto &n : _adjs.at(id))
                nei.push_back(n.first);
        return nei;
    }

    inline std::vector<_NId> nodes() const {
        std::vector<_NId> nei;
        for (auto &n : _nodes)
            nei.push_back(n.first);
        return nei;
    }

    inline _ESetType edges() const {
        _ESetType e;
        for (auto &i : _adjs)
            for (auto &j : i.second) {
                int _i = i.first, _j = j.first;
                if (_i > _j) std::swap(_i, _j);
                e.insert(std::make_pair(_i, _j));
            }
        return e;
    }

    inline _NData &operator[](const _NId &id) {
        return node(id);
    }

    private:
    _NType _nodes;
    _AdjType _adjs;
};

// TODO: DirectedNetwork

#endif /* ifndef CIMNNET_BASE_NET */
