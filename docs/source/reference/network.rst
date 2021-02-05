.. _reference-network:

无向网络类
==========

无向网络类在 :file:`cimnet/_base_net.h` 内定义，类的声明如下：

.. class:: template <class _NId, class _NData, class _EData> \
           Network

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

    :class:`Network` 包含以下构造器：

    .. function:: Network()

        构造空的无向网络。

    .. function:: Network(const _NetType &net)

        无向拷贝构造器，根据无向网络构造无向网络。

        :param net: 被拷贝的无向网络

    .. function:: Network(const _DiNetType &net)

        有向拷贝构造器，根据有向网络构造无向网络。

        :param net: 被拷贝的有向网络，任意方向的连边都能产生无向网络中的新边，双向连边仅产生一条新边。

    .. note::

        对于 :func:`无向拷贝构造器<void Network::Network (const _NetType &)>` 和 :func:`有向拷贝构造器<void Network::Network (const _DiNetType &)>` ，被拷贝的网络与目标网络存储数据的类型应该一致。

    .. function:: ~Network ()

        析构函数，释放空间。

    .. function:: friend std::ostream& operator<<(std::ostream& out, const Network& net)

        通过输出流输出网络规模信息。对于空网络它会输出：

        .. code-block:: none

            Network {#(node)=0, #(edge)=0, #(degree)=0}

    .. function:: _NId add_node(const _NId &id, const _NData &node_data)

        向网络中添加一个节点及相应的节点数据。如果这个节点已存在，则用新的节点数据覆盖原有节点数据。
        
        :param id: 待加入的节点编号
        :param node_data: 待加入节点的节点数据，如果未给定则使用 :type:`_NData` 类型的默认构造器构造对象赋值。
        :return: 成功加入的节点编号 :var:`id`

    .. function:: void add_edge(const _NId &id1, const _NId &id2, const _EData &edge_data)

        向网络中添加一条边及相应的边数据。如果这条边已存在，则用新的边数据覆盖原有边数据。如果该边上的两个节点中，任意一个节点不存在，则自动使用 :func:`add_node` 函数创建这个点，并用 :type:`_NData` 构造节点数据。
        
        :param id1: 待加入边的第一个节点编号
        :param id2: 待加入边的第二个节点编号
        :param edge_data: 待加入边的边数据，如果未给定则使用 :type:`_EData` 类型的默认构造器构造对象赋值。

    .. function:: void remove_edge(const _NId &id1, const _NId &id2)

        从网络中移除一条边，相应边的边数据也会被清除。
        
        :param id1: 待删除边的第一个节点编号
        :param id2: 待删除边的第二个节点编号
        :throw NoNodeException: 节点 :var:`id1` 或 :var:`id2` 不存在
        :throw NoEdgeException: 待删除边不存在

    .. function:: void remove_node(const _NId &id)

        从网络中移除节点，并移除所有与其相连的边，存储在上面的节点数据也会被清除。
        
        :param id: 待加入的节点编号
        :throw NoNodeException: 节点 :var:`id` 不存在

    .. function:: bool has_node(const _NId &id) const

        判断网络中是否存在指定节点。
        
        :param id: 待判断的节点编号
        :return: 如果网络中存在节点 :var:`id` ，返回 :expr:`true` ，否则返回 :expr:`false` 。

    .. function:: bool has_edge(const _NId &id1, const _NId &id2) const

        判断网络中是否存在指定边。

        :param id1: 待判断边的第一个节点编号
        :param id2: 待判断边的第二个节点编号
        :return: 如果网络中节点 :var:`id1` 与节点 :var:`id2` 有连边，返回 :expr:`true` ，否则返回 :expr:`false` 。如果任意一个节点不存在也返回 :expr:`false` 。

    .. function:: bool is_neighbor(const _NId &id1, const _NId &id2) const

        同 :func:`has_edge` 方法。
    
    .. function:: _NData &node(const _NId &id)

        访问节点数据，可以读写。

        :param id: 节点编号
        :return: 节点 :var:`id` 上的节点数据对象的引用
        :throw NoNodeException: 节点 :var:`id` 不存在

    .. function:: _NData get_node_data(const _NId &id) const

        访问点数据的一份拷贝，修改该函数返回的变量不会改变 :class:`Network` 对象存储的点数据。

        :param id: 节点编号
        :return: 节点 :var:`id` 上的节点数据对象的拷贝
        :throw NoNodeException: 节点 :var:`id` 不存在

    .. function:: _EData &edge(const _NId &id1, const _NId &id2)

        访问边数据，可以读写。

        :param id1: 边上第一个节点编号
        :param id2: 边上第二个节点编号
        :return: 节点 :var:`id1` 与节点 :var:`id2` 连边上的边数据对象引用
        :throw NoNodeException: 节点 :var:`id1` 或 :var:`id2` 不存在
        :throw NoEdgeException: 节点 :var:`id1` 与节点 :var:`id2` 间的连边不存在

    .. function:: _EData get_edge_data(const _NId &id1, const _NId &id2) const

        访问边数据的一份拷贝，修改该函数返回的变量不会改变 :class:`Network` 对象存储的边数据。

        :param id1: 边上第一个节点编号
        :param id2: 边上第二个节点编号
        :return: 节点 :var:`id1` 与节点 :var:`id2` 连边上的边数据的拷贝
        :throw NoNodeException: 节点 :var:`id1` 或 :var:`id2` 不存在
        :throw NoEdgeException: 节点 :var:`id1` 与节点 :var:`id2` 间的连边不存在

    .. function:: int number_of_nodes() const

        获取节点的总数。

        :return: 网络中所有节点的数目

    .. function:: int number_of_edges() const

        获取边的总数。

        :return: 网络中所有边的数目

    .. function:: int total_degree() const

        获取各节点的度之和。

        :return: 网络的总度数

    .. function:: int degree(const _NId &id) const

        获取节点的度。

        :param id: 节点编号
        :return: 节点 :var:`id` 的度（若该点不存在则返回 :expr:`0` ）

    .. function:: std::vector<_NId> neighbors(const _NId &id) const

        获取该节点的相邻节点的编号数组。

        :param id: 节点编号
        :return: 与节点 :var:`id` 相邻的节点编号数组。（若该点不存在则返回空数组）

    .. function:: std::vector<_NId> nodes() const

        获取所有节点编号的数组。

        :return: 网络中所有节点组成的编号数组

    .. function:: _ESetType edges() const

        获取所有边的点对集合。该集合中的每一项（设为变量 :expr:`edge`）都是一条边，使用 :expr:`edge.first` 获取这条边较小的一个节点的编号，使用 :expr:`edge.second` 获取另一个节点编号。节点编号的大小比较依赖于具体编号类型 :type:`_NId` 的实现，例如 :type:`Id` 类型取无符号整数较小的一个， :expr:`std::string` 取长度较短或字母序靠前的一个字符串等。

        :return: 网络中所有边组成的点对集合

    .. function:: _NData &operator[](const _NId &id)

        网络节点数据的便携访问，同 :func:`node` 方法。

    .. function:: _EData &operator()(const _NId &id1, const _NId &id2)

        网络边数据的便携访问，同 :func:`edge` 方法。
