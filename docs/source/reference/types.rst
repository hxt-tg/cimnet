.. _reference-types:

基本数据类型
============

基本数据类型在 :file:`cimnet/_types.h` 内定义，在引用 :file:`cimnet/network.h` 后可以直接使用。建议使用以下更加表意的类型对你的变量定义。基本数据类型包含以下类型：

.. type:: Id = unsigned int

    默认的节点编号类型。

.. type:: Weight = double

    建议作为网络权重数据的类型。

.. type:: None = class _NoneType

    不存储任何数据的空类，标识“空”的概念。
