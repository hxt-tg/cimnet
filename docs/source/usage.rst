.. namespace:: nullptr

.. _cimnet-usage:

CimNet 使用说明
===============

如果你之前编写过 C 语言，但是从未接触过 C++ 语言，或者不了解 C++11 标准的新特性，可以跳转到章节“\ :ref:`cimnet-about-cpp`\ ”快速了解 CimNet 使用的语言特性。

.. _file-structure:

文件结构
--------

CimNet 工具包含于 :file:`cimnet` 文件夹内，由以下文件组成：

===========================   ======================
            文件                      内容概述
===========================   ======================
:file:`cimnet/_types.h`       基础数据类型
:file:`cimnet/_exception.h`   网络异常类
:file:`cimnet/_base_net.h`    通用无向/有向网络类
:file:`cimnet/network.h`      已实现的常用网络结构
:file:`cimnet/random.h`       MT随机数生成
===========================   ======================

一般情况下，你只需要引用 :file:`cimnet/network.h` 这个头文件，就可以使用默认的基础数据类型、网络异常类和有向/无向通用网络类。已实现的常用网络结构全部继承于通用无向网络，网络的节点编号类型为整型。

如果你想使用优秀的\ :ref:`reference-rng`\ ，可以引用 :file:`cimnet/random.h` ，也可以使用 C++ 标准库中的随机数函数。

.. _use-net:

使用网络
--------

.. _create-net:

1. 创建网络
^^^^^^^^^^^

你可以用下面的语句创建一个不含任何点边的空的无向网络：

.. code-block:: cpp

    Network<> net;

这个网络用 :type:`Id` 类型作为节点编号的标识（见 CimNet 接口的\ :ref:`reference-types`\ ）。每个节点的编号应该互不相同。创建一个空的有向网络：

.. code-block:: cpp

    DirectedNetwork<> net;

你也可以指定自己节点类型：

.. code-block:: cpp

    Network<std::string> net;

这样一来，在网络 :expr:`net` 中你可以使用 :expr:`std::string` 来唯一标识一个节点。

.. _edit-structure:

2. 编辑网络结构
^^^^^^^^^^^^^^^

你可以向网络中添加节点：

.. code-block:: cpp

    net.add_node(1);

网络中就增加了一个以 :expr:`1` 为编号的节点。如果你指定了节点编号类型为 :expr:`std::string` ，也可以用以下方式添加节点：

.. code-block:: cpp

    net.add_node("A");

你可以使用 :func:`has_node(id)<Network::has_node>` 方法判断网络中是否有以 :expr:`id` 为编号的节点，以上面的网络为例，下列语句： 

.. code-block:: cpp

    std::cout << net.has_node("A") << std::endl;
    std::cout << net.has_node("Not existed") << std::endl;

会打印

.. code-block:: none

    true
    false

两个节点间的连接关系称为边。向网络中添加一条边：

.. code-block:: cpp

    net.add_edge(1, 2);

如果网络 :expr:`net` 为无向网络，可以使用 :func:`has_edge(id1, id2)<Network::has_edge>` 方法判断网络中是否存在边， :expr:`id1` 和 :expr:`id2` 的位置可以调换。你也可以使用 :func:`is_neighbor(id1, id2)<Network::is_neighbor>` 判断网络中 :expr:`id1` 与 :expr:`id2` 是否为邻居节点，它的作用和 :func:`has_edge<Network::has_edge>` 是一样的。

如果网络 :expr:`net` 为有向网络，可以使用 :func:`has_successor(id1, id2)<DirectedNetwork::has_successor>` 判断节点 :expr:`id1` 是否存在后继节点 :expr:`id2` ，使用 :func:`has_predecessor(id1, id2)<DirectedNetwork::has_predecessor>` 判断节点 :expr:`id1` 是否存在前序节点 :expr:`id2` 。有向网络也有 :func:`has_edge<DirectedNetwork::has_edge>` 方法，它和 :func:`has_successor<DirectedNetwork::has_successor>` 方法是等效的。有向网络的 :func:`is_neighbor(id1, id2)<DirectedNetwork::is_neighbor>` 方法在 :expr:`id1` 和 :expr:`id2` 之间存在连边（无论是 :expr:`id1` 指向 :expr:`id2` 或 :expr:`id2` 指向 :expr:`id1` ）时返回 :expr:`true` 。如果有向网络 :expr:`net` 中存在一条以节点 :expr:`1` 指向节点 :expr:`2` 的边，下列表达式：

.. code-block:: cpp

    net.has_successor(1, 2)
    net.has_predecessor(2, 1)
    net.has_edge(1, 2)
    net.is_neighbor(1, 2)
    net.is_neighbor(2, 1)

的值均为 :expr:`true` 。

.. _store-data:

3. 存储节点/边数据
^^^^^^^^^^^^^^^^^^

在存储数据前需要在模板类处指定存储的数据类型。我们定义如下两种类型：

.. code-block:: cpp

    typedef std::string NodeDescribe;
    typedef struct {
        int amount;
        double weight;
    } EdgeDetail;

并且以这种方式声明网络，并添加一条边：

.. code-block:: cpp

    Network<Id, NodeDescribe, EdgeDetail> net;
    net.add_edge(1, 2);

网络中便有了两个点和一条边。接下来你可以这样在网络的节点中添加数据：

.. code-block:: cpp

    net.node(1) = "First node";
    net[2] = "Second node;

上面两个语句都能用来添加数据。第一条语句使用 :func:`node(id)<Network::node>` 方法返回了节点 :expr:`id` 存储的引用，这使得你可以通过引用修改内部存储。网络类也提供了下标的方式返回节点引用（即第二条语句所示），这使得你可以更方便地存取网络节点的数据。在网络的边上添加数据也可以通过类似的方式：

.. code-block:: cpp

    net.edge(1, 2) = {3, 3.14};
    net(1, 2) = {3, 3.14};

同理，第一条语句使用调用函数的形式访问边数据的引用，第二条语句是一种更简便的方式——它重载了这个类的括号操作符。当然，由于 :func:`edge(id1, id2)<Network::edge>` 方法返回的是 :expr:`EdgeDetail` 结构体的引用，你可以使用 ``.`` 直接修改内部成员：

.. code-block:: cpp

    net.edge(1, 2).amount = 4;
    net(1, 2).amount = 4;

点数据和边数据都能存储其它任意的你定义过的类的对象，但是每个点之间或每条边之间存储的类型要一致。

在添加节点和边的方法里也可以直接添加数据：

.. code-block:: cpp

    net.add_node(1, "First node");
    net.add_node(2, "Second node");
    net.add_edge(1, 2, {3, 3.14});

.. _network-copy:

4. 网络拷贝和转换
^^^^^^^^^^^^^^^^^

CimNet 提供拷贝构造器完成网络的拷贝操作。你可以将一个网络及其内部数据完全复制给另一个网络，此后前一个网络的修改不影响拷贝后的网络数据。只需要将原始网络作为参数传入新网络的初始化参数列表中即可。

.. code-block:: cpp

    Network<Id, NodeDescribe, EdgeDetail> net;
    // Add nodes and edges to net
    Network<Id, NodeDescribe, EdgeDetail> net_copy(net);
    DirectedNetwork<Id, NodeDescribe, EdgeDetail> di_net_copy(net);

需要注意拷贝网络的模板参数需要保持一致，它的类既可以是 :class:`Network` 也可以是 :class:`DirectedNetwork` 。如果原网络是无向网络且新网络是有向网络，所有无向边会转化成两条有向且指向相反的连边。如果将有向网络拷贝为无向网络，所有的有向边失去方向，变为无向边；双向边则会变为一条无向边。

.. _network-loop:

5. 网络数据和遍历
^^^^^^^^^^^^^^^^^

在无向网络中使用 :func:`degree(id)<Network::degree>` 方法可以获知节点 :expr:`id` 的度。在有向网络中， :func:`in_degree(id)<DirectedNetwork::in_degree>` 返回节点 :expr:`id` 的入度， :func:`out_degree(id)<DirectedNetwork::out_degree>` 返回节点 :expr:`id` 的出度， :func:`degree(id)<DirectedNetwork::degree>` 返回了入度和出度的和。

:func:`number_of_nodes()<Network::number_of_nodes>` 方法会返回网络的节点数量， :func:`number_of_edges()<Network::number_of_edges>` 方法会返回网络边的数量。 :func:`total_degree()<Network::total_degree>` 方法会返回网络的总度数，它从数值上等于网络总边数的两倍。

你也可以直接使用 :expr:`std::cout` 输出流打印网络信息：

.. code-block:: cpp

    std::cout << net << std::endl;

它会简要打印网络的节点数、边数和总度数信息。

调用 :func:`nodes()<Network::nodes>` 方法可以获取网络中所有的节点编号（ :expr:`std::vector<NodeId>` ）， :func:`edges()<Network::edges>` 方法可以获取网络中所有的边，它是一个点对的集合容器（ :expr:`std::unordered_set<std::pair<NodeId, NodeId>>` ）。 :func:`neighbors(id)<Network::neighbors>` 返回节点 :expr:`id` 的所有邻居（ :expr:`std::vector<NodeId>` ）。可以参考下面的方式遍历网络和邻居的节点编号：

.. code-block:: cpp

    for (auto &node : net.nodes())
        // Visit node
    for (auto &edge : net.edges())
        // Visit edge.first and edge.second
    for (auto &neighbor : net.neighbors())
        // Visit neighbor

其中由于边 :expr:`edge` 是 :expr:`std::pair<NodeId, NodeId>` 类型， C++11 中需要用 :expr:`edge.first` 和 :expr:`edge.second` 访问一条边中的两个节点编号。对于无向网络而言， :expr:`edge.first` 是一条边中较小的一个节点编号（数值较小或字符串字母序靠前的）；有向网络中 :expr:`edge.first` 是前序节点， :expr:`edge.second` 是后继节点。

（如果你支持 C++17 及以上的编译环境，可以尝试将循环替换为 ``for (auto &[i, j] : net.edges())`` ，其中 :expr:`i` 和 :expr:`j` 等效于 :expr:`edge.first` 和 :expr:`edge.second` 。）

另外，对于无向网络而言， :func:`neighbors(id)<Network::neighbors>` 返回了节点 :expr:`id` 所有相邻节点编号。对于有向网络而言， :func:`neighbors(id)<DirectedNetwork::neighbors>` 返回了所有与节点 :expr:`id` 有关联（无论方向）的节点编号。有向网络还提供了 :func:`predecessors(id)<DirectedNetwork::predecessors>` 方法用来返回节点 :expr:`id` 的所有前序节点编号， :func:`successors()<DirectedNetwork::successors>` 方法用来返回节点 :expr:`id` 的所有后继节点编号，它们的遍历方式与 :func:`neighbors(id)<DirectedNetwork::neighbors>` 类似。


.. _implemented-structure:

6. 已实现的网络结构
^^^^^^^^^^^^^^^^^^^

目前所有已实现的网络结构都是模板类，且节点编号都是 :type:`Id` 类型的——所以模板只接受两个模板参数， :expr:`NodeData` 和 :expr:`EdgeData` ，它们默认都是 :type:`None` 。这些网络的用法和通用网络类型基本一致，只是初始化时需要传入指定的参数。这里给出一个较为完整的程序实例：构建一个包含10个节点的规则网络，这个网络的每个节点都和周围6个邻居连边（即，每个节点向顺时针方向的3个邻居添加连边）。最后我们打印网络信息和一号节点的邻居节点编号。

.. code-block:: cpp
    :linenos:
    :emphasize-lines: 1,4,7

    #include "cimnet/network.h"

    int main(void) {
        RegularNetwork<> net(10, 3);
        std::cout << net << std::endl;
        std::cout << "Neighbors of node 1: ";
        for (auto &n : net.neighbors(1))
            std::cout << n << " ";
        std::cout << std::endl;
        return 0;
    }

这段代码的第1行引用了网络结构的头文件。第4行用模板类定义了\ :ref:`regular-network` :expr:`net` ，第7行遍历了网络中1号节点的邻居，变量 :expr:`n` 的值为每次遍历到的一个邻居节点的编号。
