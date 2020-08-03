.. _reference-impl-networks:

常用网络
========

已实现的常用网络在 :file:`cimnet/network.h` 内定义，它们均继承于无向网络类。

这些常用网络均以 :type:`Id` 作为节点编号，且均为模板类，支持传入两个模板参数，依次为节点数据类型 :type:`_NData<Network::_NData>` 和边数据类型 :type:`_EData<Network::_EData>` ，它们默认均为 :type:`None` 。

.. _full-connected-network:

全连接网络
----------

.. class:: template <class _NData, class _EData> \
           FullConnectedNetwork: public Network<int, _NData, _EData>

    .. function:: FullConnectedNetwork(int n_nodes)
    
        构造一个全连接网络。网络中的节点彼此相连，每个点的度都为 :expr:`n_nodes - 1`。
    
        :param n_nodes: 总节点数
        :throw NetworkException: :var:`n_nodes` 小于 0

.. _regular-network:

规则网络
--------

.. class:: template <class _NData, class _EData> \
           RegularNetwork: public Network<int, _NData, _EData>

    .. function:: RegularNetwork(int n_nodes, int n_links)

        构造一个规则网络。初始是一个没有连边的环状网络，随后每个节点都依次连接它们顺时针方向的 :var:`n_links` 个邻居，每个节点的度均为 :expr:`2 * n_links` 。
    
        :param n_nodes: 总节点数
        :param n_links: 每个节点顺时针方向新增的边数
        :throw NetworkException: :var:`n_nodes` 小于 0
        :throw NetworkException: :var:`n_links` 小于 0 或大于 :expr:`n_nodes - 1`

.. _er-network:

ER随机图
--------

.. class:: template <class _NData, class _EData> \
           ERNetwork : public Network<int, _NData, _EData>

    .. function:: ERNetwork (int n_nodes, double prob_link)
    
        构造一个ER随机图。

        :param n_nodes: 总节点数
        :param prob_link: 每两对节点间的连边概率
        :throw NetworkException: :var:`n_nodes` 小于 0
        :throw NetworkException: :var:`prob_link` 不在 :expr:`[0, 1]` 范围内

.. _grid-network:

格子网络
----------

.. class:: template <class _NData, class _EData> \
           GridNetwork: public Network<int, _NData, _EData>

    .. function:: GridNetwork(int width, int height, int n_neighbors)
    
        构造一个格子网络。格子网络是循环边界的结构，即每一行的末尾与开头相连，列向同理。

        :param width: 格子的宽
        :param height: 格子的高
        :param n_neighbors: 每个节点邻居的数量（默认为 :expr:`4` ）
        :throw NetworkException: :var:`width` 或 :var:`height` 小于 0
        :throw NetworkException: :var:`n_neighbors` 不为 :expr:`4` 或 :Expr:`8` 

    .. note::

        :class:`GridNetwork` 只支持 :var:`n_neighbors` 为 :expr:`4` 和 :Expr:`8` 的情况，如果需要其他邻居情况请使用 :class:`CustomizableGridNetwork` 。

.. _customizable-grid-network:

可定制化的格子网络
------------------

.. class:: template <class _NData, class _EData> \
           CustomizableGridNetwork: public Network<int, _NData, _EData>

    该网络初始为一个不包含连边的二维格点网络。你需要为它指定一个  :type:`范围遮罩<RangeMask>` ，之后对每个节点进行连边时都会按照这个 :type:`范围遮罩<RangeMask>` 内包含的 :type:`连边偏移量<RangeShift>` 计算在空格点网络中的行列偏移值，并连接相应节点与该节点。

    可定制化的格子网络是循环边界的结构，即每一行的末尾与开头相连，列向同理。
    
    该网络定义了以下类型/概念：

    .. type:: std::pair<int, int> RangeShift;

        一对整数构成的 :type:`连边偏移量<RangeShift>` 。第一个值是每行向右的偏移量，第二个值是每列向下的偏移量。每个节点向周围节点连边时都会参照偏移量。

    .. type:: std::vector<RangeShift> RangeMask;

        以偏移量组成的连边偏移量数组，称为 :type:`范围遮罩<RangeMask>` 。

    .. type:: RangeMask (*MaskFunction)(double);

        给定半径构造 :type:`范围遮罩<RangeMask>` 的函数的指针，称为 :type:`范围遮罩构造器<MaskFunction>` 。

    该类实现了两种 :type:`范围遮罩构造器<MaskFunction>` ：

    .. function:: static RangeMask ManhattanMask(double radius)

        返回的 :type:`范围遮罩<RangeMask>` 包含所有曼哈顿距离\ **不小于** :var:`radius` 的偏移量。（类似菱形）

    .. function:: static RangeMask EuclideanMask(double radius)

        返回的 :type:`范围遮罩<RangeMask>` 包含所有欧几里得距离\ **不小于** :var:`radius` 的偏移量。（类似圆形）

    构造网络时支持两种形式的输入：

    .. function:: CustomizableGridNetwork(int width, int height, RangeMask &mask)
    
        给定 :type:`范围遮罩<RangeMask>` 构造可定制化的格子网络。
    
        :param width: 格子的宽
        :param height: 格子的高
        :param mask: 节点连边时参考的 :type:`范围遮罩<RangeMask>` 
        :throw NetworkException: :var:`width` 或 :var:`height` 小于 0

    .. function:: CustomizableGridNetwork(int width, int height, double radius, const MaskFunction func)
    
        给定 :type:`范围遮罩构造器<MaskFunction>` 以及传递给函数的连边范围值，构造可定制化的格子网络。
    
        :param width: 格子的宽
        :param height: 格子的高
        :param radius: 传递给 :type:`范围遮罩构造器<MaskFunction>` 的范围值
        :param func: :type:`范围遮罩构造器<MaskFunction>` （默认为 :func:`ManhattanMask` ）
        :throw NetworkException: :var:`width` 或 :var:`height` 小于 0

    .. note::

        对于可定制化的格子网络，可以参考以下例子：

        .. code-block:: cpp
            :linenos:

            /* 创建自定义的连边范围函数：（例如radius=2)
                    o
                    o
                o o x o o
                    o
                    o
            */
            CustomizableGridNetwork<>::RangeMask cross_mask(double radius) {
                CustomizableGridNetwork<>::RangeMask mask;
                for (int i = 1; i <= (int)radius; i++) {
                    mask.push_back(std::make_pair(0, i));
                    mask.push_back(std::make_pair(0, -i));
                    mask.push_back(std::make_pair(i, 0));
                    mask.push_back(std::make_pair(-i, 0));
                }
                return mask;
            }

            void test_custom_grid() {
                /* 10x10的二维格子，按曼哈顿距离小于等于3的范围对每个节点进行连边 */
                CustomizableGridNetwork<> net(10, 10, 3);
                /* 10x10的二维格子，按欧式距离小于等于3的范围对每个节点进行连边 */
                CustomizableGridNetwork<> net(10, 10, 3, CustomizableGridNetwork<>::EuclideanMask);
                /* 定义一个范围数组 */
                std::vector<std::pair<int, int>> mask;
                mask.push_back(std::make_pair(0, 1));
                mask.push_back(std::make_pair(0, 2));
                mask.push_back(std::make_pair(1, 0));
                /* 10x10的二维格子，按给定范围数组的偏移对每个节点进行连边 */
                CustomizableGridNetwork<> net(10, 10, mask);
                /* 10x10的二维格子，按自定义连边函数的半径小于等于3的范围对每个节点进行连边 */
                CustomizableGridNetwork<> net(10, 10, 4, cross_mask);
            }

.. _cubic-network:

立方体网络
----------

.. class:: template <class _NData, class _EData> \
           CubicNetwork: public Network<int, _NData, _EData>

    .. function:: CubicNetwork(int length, int width, int height)
    
        构造一个立方体网络。网络中的每个节点与其上、下、左、右、前、后六个方向的相邻节点进行连边。立方体网络是循环边界的结构，即每一行的末尾与开头相连，列向同理。
    
        :param length: 立方体的长
        :param width: 立方体的宽
        :param height: 立方体的高
        :throw NetworkException: :var:`length` 、 :var:`width` 或 :var:`height` 小于 0

.. _honeycomb-network:

蜂窝网络
--------

.. class:: template <class _NData, class _EData> \
           HoneycombNetwork: public Network<int, _NData, _EData>

    .. function:: HoneycombNetwork(int honeycomb_width, int honeycomb_height)
    
        构造一个蜂窝网络。蜂窝网络是循环边界的结构，即每一行的末尾与开头相连，列向同理。

        蜂窝结构与节点的关系见下面的图，其节点数量等于 :expr:`2 * honeycomb_width * honeycomb_height` 。
    
        :param honeycomb_width: 蜂窝的宽
        :param honeycomb_height: 蜂窝的高
        :throw NetworkException: :var:`honeycomb_width` 或 :var:`honeycomb_height` 小于 0

    .. image:: /_static/images/Honeycomb.*

.. _kagome-network:

Kagome 晶格网络
---------------

.. class:: template <class _NData, class _EData> \
           KagomeNetwork: public Network<int, _NData, _EData>

    .. function:: KagomeNetwork(int kagome_width, int kagome_height)
    
        构造一个 Kagome 晶格网络。Kagome 晶格网络是循环边界的结构，即每一行的末尾与开头相连，列向同理。

        Kagome 晶格结构与节点的关系见下图，其节点数量等于 :expr:`3 * kagome_width * kagome_height` 。
    
        :param kagome_width: Kagome 晶格的宽
        :param kagome_height: Kagome 晶格的高
        :throw NetworkException: :var:`kagome_width` 或 :var:`kagome_height` 小于 0

    .. image:: /_static/images/Kagome.*

.. _scale-free-network:

BA 无标度网络
-------------

.. class:: template <class _NData, class _EData> \
           ScaleFreeNetwork: public Network<int, _NData, _EData>

    .. function:: ScaleFreeNetwork(int n_nodes, int n_edges_per_node)
    
        构造一个 BA 无标度网络\ [#scale-free]_\ 。BA 无标度网络初始由没有连边的 :var:`n_edges_per_node` 个节点组成（第一个节点编号为 :expr:`0` ）。 :expr:`n_edges_per_node` 号节点与所有 :expr:`n_edges_per_node` 个已存在的节点进行连边。之后从 :expr:`n_edges_per_node + 1` 号节点开始，每个节点 :math:`i` 都以概率

        .. math::
            \mathbb{P}_i = \frac{d_i}{\sum_{j=1}^n d_j}
        
        向已存在的节点连边，其中 :math:`d_i` 表示 :math:`i` 号节点的度。
    
        :param n_nodes: 网络最终状态的总节点数
        :param n_edges_per_node: 每个新增节点的连边数
        :throw NetworkException: :var:`n_nodes` 小于 0
        :throw NetworkException: :var:`n_edges_per_node` 小于 0 或大于 :var:`n_nodes`

.. [#scale-free] 无标度网络的 Barabási–Albert 模型：https://en.wikipedia.org/wiki/Scale-free_network#The_Barab%C3%A1si%E2%80%93Albert_model
