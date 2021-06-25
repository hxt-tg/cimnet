.. _reference-di-network:

有向网络类
===========

有向网络类在 :file:`cimnet/_base_net.h` 内定义，类的声明如下：

.. class:: template <class _NId, class _NData, class _EData> \
           DirectedNetwork

    :tparam _NId: 节点编号类型（默认为 :type:`Id`）
    :tparam _NData: 节点数据类型（默认为 :type:`None`）
    :tparam _EData: 边数据类型（默认为 :type:`None`）
    
    该类包含以下类型定义：

    .. type:: std::unordered_map<_NId, _NData> _NType;

        含数据的节点类型。

    .. type:: std::pair<_NId, _NId> _EPairType;

        用一对点的形式来表示的边类型。

    .. type:: Network<_NId, _NData, _EData> _NetType;

        类型匹配的无向网络类型。

    .. type:: DirectedNetwork<_NId, _NData, _EData> _DiNetType;

        类型匹配的有向网络类型。

    .. type:: std::unordered_set<std::pair<_NId, _NId>, HashPair> _ESetType;

        边的点对集合类型。

    .. type:: std::unordered_set<_NId> _NeiSetType;

        节点邻居的集合类型。



    :class:`DirectedNetwork` 包含以下构造器：

    .. function:: DirectedNetwork()

        构造空的有向网络。

    .. function:: DirectedNetwork(const _DiNetType &net)

        有向拷贝构造器，根据有向网络构造有向网络。

        :param net: 被拷贝的有向网络


    .. function:: DirectedNetwork(const _NetType &net)

        无向拷贝构造器，根据无向网络构造有向网络。

        :param net: 被拷贝的无向网络，每条无向边都能产生有向网络中的一对双向连边，即新增两条边。

    .. note::

        对于 :func:`无向拷贝构造器<void DirectedNetwork::DirectedNetwork (const _NetType &)>` 和 :func:`有向拷贝构造器<void DirectedNetwork::DirectedNetwork (const _DiNetType &)>` ，被拷贝的网络与目标网络存储数据的类型应该一致。

    .. function:: ~DirectedNetwork ()

        析构函数，释放空间。

    .. function:: friend std::ostream& operator<<(std::ostream& out, const DirectedNetwork& net)

        通过输出流输出网络规模信息。对于空网络它会输出：

        .. code-block:: none

            DirectedNetwork {#(node)=0, #(edge)=0, #(degree)=0}

    .. function:: _NId add_node(const _NId &id, const _NData &node_data)

        向网络中添加一个节点及相应的节点数据。如果这个节点已存在，则用新的节点数据覆盖原有节点数据。
        
        :param id: 待加入的节点编号
        :param node_data: 待加入节点的节点数据，如果未给定则使用 :type:`_NData` 类型的默认构造器构造对象赋值。
        :return: 成功加入的节点编号 :var:`id`

    .. function:: void add_edge(const _NId &id1, const _NId &id2, const _EData &edge_data)

        向网络中添加一条由节点 :var:`id1` 指向节点 :var:`id2` 的连边及相应的边数据。如果这条边已存在，则用新的边数据覆盖原有边数据。如果该边的起始或终止节点不存在，则自动使用 :func:`add_node` 函数创建这个点，并用 :type:`_NData` 构造节点数据。
        
        :param id1: 待加入边的起始节点编号
        :param id2: 待加入边的终止节点编号
        :param edge_data: 待加入边的边数据，如果未给定则使用 :type:`_EData` 类型的默认构造器构造对象赋值。

    .. function:: void remove_edge(const _NId &id1, const _NId &id2)

        从网络中移除一条由节点 :var:`id1` 指向节点 :var:`id2` 的连边，相应边的边数据也会被清除。
        
        :param id1: 待删除边的起始节点编号
        :param id2: 待删除边的终止节点编号
        :throw NoNodeException: 节点 :var:`id1` 或 :var:`id2` 不存在
        :throw NoEdgeException: 待删除有向边不存在

    .. function:: void remove_node(const _NId &id)

        从网络中移除节点，并移除所有与其前序节点和后继节点的连边，存储在上面的数据也会被清除。
        
        :param id: 待加入的节点编号
        :throw NoNodeException: 节点 :var:`id` 不存在

    .. function:: bool has_node(const _NId &id) const

        判断网络中是否存在指定节点。
        
        :param id: 待判断的节点编号
        :return: 如果网络中存在节点 :var:`id` ，返回 :expr:`true` ，否则返回 :expr:`false` 。

    .. function::  bool has_successor(const _NId &id1, const _NId &id2) const

        判断网络中是否存在指定的后继连边关系。

        :param id1: 待判断边的起始节点编号
        :param id2: 待判断边的终止节点编号
        :return: 如果网络中节点 :var:`id1` 存在一个后继节点 :var:`id2` ，返回 :expr:`true` ，否则返回 :expr:`false` 。如果任意一个节点不存在也返回 :expr:`false` 。

    .. function::  bool has_predecessor(const _NId &id1, const _NId &id2) const

        判断网络中是否存在指定的前序连边关系。

        :param id1: 待判断边的终止节点编号
        :param id2: 待判断边的起始节点编号
        :return: 如果网络中节点 :var:`id1` 存在一个前序节点 :var:`id2` ，返回 :expr:`true` ，否则返回 :expr:`false` 。如果任意一个节点不存在也返回 :expr:`false` 。

    .. function::  bool has_edge(const _NId &id1, const _NId &id2) const

        同 :func:`has_successor` 方法。

    .. function:: bool is_neighbor(const _NId &id1, const _NId &id2) const

        判断网络中是否存在连边关系。

        :param id1: 待判断边的第一个节点编号
        :param id2: 待判断边的第二个节点编号
        :return: 如果网络中节点 :var:`id1` 是节点 :var:`id2` 的前序节点或者后继节点（无论指向），返回 :expr:`true` ，否则返回 :expr:`false` 。如果任意一个节点不存在也返回 :expr:`false` 。

    .. function:: _NData &node(const _NId &id)

        访问节点数据，可以读写。

        :param id: 节点编号
        :return: 节点 :var:`id` 上的节点数据对象的引用
        :throw NoNodeException: 节点 :var:`id` 不存在

    .. function:: _NData get_node_data(const _NId &id) const

        访问点数据的一份拷贝，修改该函数返回的变量不会改变 :class:`DirectedNetwork` 对象存储的点数据。

        :param id: 节点编号
        :return: 节点 :var:`id` 上的节点数据对象的拷贝
        :throw NoNodeException: 节点 :var:`id` 不存在

    .. function:: _EData &edge(const _NId &id1, const _NId &id2)

        访问有向边数据，可以读写。

        :param id1: 边上的起始节点编号
        :param id2: 边上的终止节点编号
        :return: 由节点 :var:`id1` 指向节点 :var:`id2` 的有向边上的边数据对象引用
        :throw NoNodeException: 节点 :var:`id1` 或 :var:`id2` 不存在
        :throw NoEdgeException:  由节点 :var:`id1` 指向节点 :var:`id2` 的有向边不存在

    .. function:: _EData get_edge_data(const _NId &id1, const _NId &id2) const

        访问边数据的一份拷贝，修改该函数返回的变量不会改变 :class:`DirectedNetwork` 对象存储的边数据。

        :param id1: 边上的起始节点编号
        :param id2: 边上的终止节点编号
        :return: 由节点 :var:`id1` 指向节点 :var:`id2` 的有向边上的边数据的拷贝
        :throw NoNodeException: 节点 :var:`id1` 或 :var:`id2` 不存在
        :throw NoEdgeException:  由节点 :var:`id1` 指向节点 :var:`id2` 的有向边不存在

    .. function:: int number_of_nodes() const

        获取节点的总数。

        :return: 网络中所有节点的数目

    .. function:: int number_of_edges() const

        获取边的总数。

        :return: 网络中所有有向边的数目

    .. function:: int total_degree() const

        获取各节点的度之和，它的值为边数 :expr:`number_of_edges()` 的两倍。

        :return: 网络的总度数

    .. function:: int in_degree(const _NId &id) const

        获取节点的入度，即指向该节点的边的数量。

        :param id: 节点编号
        :return: 节点 :var:`id` 的入度（若该点不存在则返回 :expr:`0` ）

    .. function:: int out_degree(const _NId &id) const

        获取节点的出度，即该节点指向其他节点的边的数量。

        :param id: 节点编号
        :return: 节点 :var:`id` 的出度（若该点不存在则返回 :expr:`0` ）

    .. function:: int degree(const _NId &id) const

        获取节点的度，它的值为入度和出度的和。

        :param id: 节点编号
        :return: 节点 :var:`id` 的度（若该点不存在则返回 :expr:`0` ）

    .. function:: std::vector<_NId> successors(const _NId &id) const

        获取该节点后继节点的编号数组。（该节点指向其他节点）

        :param id: 节点编号
        :return: 节点 :var:`id` 的后继节点编号数组。（若该点不存在则返回空数组）

    .. function:: std::vector<_NId> predecessors(const _NId &id) const

        获取该节点前序节点的编号数组。（其他节点指向该节点）

        :param id: 节点编号
        :return: 节点 :var:`id` 的前序节点编号数组。（若该点不存在则返回空数组）

    .. function:: _NId random_successor(const _NId &id) const

        获取该节点的一个随机后继节点。

        :param id: 节点编号
        :return: 节点 :var:`id` 的一个随机后继节点
        :throw NoNodeException: 节点 :var:`id` 不存在
        :throw NoNeighborsException: 节点 :var:`id` 没有后继节点

    .. function:: _NId random_predecessor(const _NId &id) const

        获取该节点的一个随机前序节点。

        :param id: 节点编号
        :return: 节点 :var:`id` 的一个随机前序节点
        :throw NoNodeException: 节点 :var:`id` 不存在
        :throw NoNeighborsException: 节点 :var:`id` 没有前序节点

    .. function:: std::vector<_NId> neighbors(const _NId &id) const

        获取与该节点有连边关系的相邻节点编号数组。（无论指向）

        :param id: 节点编号
        :return: 与节点 :var:`id` 有连边关系的相邻节点编号数组。（若该点不存在则返回空数组）

    .. function:: std::vector<_NId> nodes() const

        获取所有节点编号的数组。

        :return: 网络中所有节点组成的编号数组

    .. function:: _ESetType edges() const

        获取所有有向边的点对集合。该集合中的每一项（设为变量 :expr:`edge`）都是一条边，使用 :expr:`edge.first` 获取这条边的前序节点编号，使用 :expr:`edge.second` 获取后继节点编号。

        :return: 网络中所有有向边组成的点对集合

    .. function:: _NData &operator[](const _NId &id)

        网络节点数据的便携访问，同 :func:`node` 方法。

    .. function:: _EData &operator()(const _NId &id1, const _NId &id2)

        网络有向边数据的便携访问，同 :func:`edge` 方法。
