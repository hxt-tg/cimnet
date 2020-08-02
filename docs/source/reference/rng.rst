.. _reference-rng:

随机数生成器
============

CimNet 使用了 `Mersenne twister 随机数生成器 <https://en.wikipedia.org/wiki/Mersenne_Twister>`_\ [#mt_random]_\ ，它被定义在 :file:`cimnet/random.h` 中，可用的函数如下：

.. function:: void sgenrand(unsigned long seed)

   设置随机数种子
   
   :param seed: 非负的随机数种子

.. function:: long randi(unsigned long LIM)

   获取一个随机整数

   :param LIM: 随机数的上限（该上限不可取）
   :return: 范围在 :math:`[0, LIM-1]` 的随机整数
   
.. function:: double randf()

   获取一个随机浮点数

   :return: 范围在 :math:`(0, 1)` 的随机浮点数


.. [#mt_random] `这个算法 <https://en.wikipedia.org/wiki/Mersenne_Twister>`_\ 是由Makoto Matsumoto（松本 眞）和Takuji Nishimura（西村 拓士）于1997年提出的。这个随机数算法运行速度快，产生的随机数分布均匀，适合用于对统计信息较为敏感的场合。
