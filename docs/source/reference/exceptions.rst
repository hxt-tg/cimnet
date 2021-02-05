.. _reference-exceptions:

网络异常类
==========

网络异常类在 :file:`cimnet/_exception.h` 内定义，用于标识被抛出的网络相关异常。

通用网络异常类
--------------

.. class:: NetworkException : public std::exception

    构造网络异常的基类。

    .. function:: NetworkException(const std::string &info)

        根据报错信息构造网络异常对象。

        :param info: 网络异常信息字符串
        
    .. function:: void set_info(const std::string &info)
    
        修改异常对象的报错信息。

        :param info: 网络异常信息字符串

.. note::

    抛出异常 :expr:`NetworkException("Cannot create network.")` 时会显示：
    
    （gcc on linux环境）

    .. code-block:: none

        terminate called after throwing an instance of 'NetworkException'
          what():  Network error: Cannot create network.

缺失节点异常类
--------------

.. class:: template <class _NId> \
           NoNodeException : public NetworkException

    当尝试访问网络中不存在的节点时抛出该异常。

    :tparam _NId: 节点编号类型（默认为 :type:`Id`）
    
    .. function:: NoNodeException(const _NId &id)

        构造缺失节点异常对象。

        :param id: 缺失节点的编号

.. note::

    抛出异常 :expr:`NoNodeException<int>(65536)` 时会显示：
    
    .. code-block:: none

        terminate called after throwing an instance of 'NoNodeException<int>'
          what():  Network error: Node 65536 not found.

缺失边异常类
------------

.. class:: template <class _NId> \
           NoEdgeException : public NetworkException

    当尝试访问网络中不存在的边时抛出该异常。
    
    :tparam _NId: 节点编号类型（默认为 :type:`Id`）

    .. function:: NoEdgeException(const _NId &id1, const _NId &id2, bool is_directed=false);

        构造缺失边异常对象。
    
    :param id1: 缺失边的第一个节点编号
    :param id2: 缺失边的第二个节点编号
    :param is_directed: 该缺失边是否为有向边（默认为无向边）

.. note::

    抛出异常 :expr:`NoEdgeException<int>(3, 5)` 时会显示：
    
    .. code-block:: none

        terminate called after throwing an instance of 'NoEdgeException<int>'
          what():  Network error: No edge between 3 and 5.

    抛出异常 :expr:`NoEdgeException<int>(3, 5, true)` 时会显示：
    
    .. code-block:: none

        terminate called after throwing an instance of 'NoEdgeException<int>'
          what():  Network error: No edge from 3 to 5.
