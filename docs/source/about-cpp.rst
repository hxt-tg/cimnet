.. _cimnet-about-cpp:

关于 C++ 语言
=============

这一部分的内容将帮助你在仅有C语言基础的条件下，快速学习使用 CimNet 所必需的 C++ 语法。此外，阅读 CimNet :file:`example/` 文件夹中提供的例子也能够增加你对语言特性的理解。注意，这里只介绍一些最基本的概念，如果你希望实现一些更加高级的特性，需要额外学习一些专业书籍。

.. _object-oriented:

面向对象
--------

大多数支持面向对象编程的语言拥有四大特性——封装，抽象，继承，多态。

封装和抽象保证了程序模块和模块之间的高度独立和易用。在你使用这个对象的时候，可以不必关心对象的实现细节，使你更加关注程序其他部分的逻辑。你可以使用更加表意的方式修改对象数据，并且保证数据修改的可靠和合理。

在 CimNet 中， :file:`cimnet/network.h` 中所有网络类都继承于 :class:`Network` 类，这意味着你可以在例如 :class:`RegularNetwork` 的对象中访问 :class:`Network` 的方法。其中 :class:`RegularNetwork` 称为子类， :class:`Network` 称为父类或基类。

.. _instantiation-and-template-class:

实例化与模板类
--------------

在 C++ 中，一个类可以实例化一个对象，每一个对象都能访问这个类中的方法，但是对象与对象之间的大部分数据并不共通。所谓方法就是函数，不过这个函数只能针对特定类实例化的对象来调用。你可以使用 :expr:`ClassName var;` 来实例化对象 :expr:`var` ，使用 :expr:`var.method(params, ...)` 来调用 :expr:`ClassName` 的方法。

C++ 提供了一种更加高级的方式来实现一些功能相似但数据类型不一致的类，即模板类。模板类所实现类需要指定一些模板参数，这些模板参数就是指定的数据类型。模板类里会实现针对给定模板参数的属性和方法。使用模板类的语法是在类名后加尖括号，即 :expr:`ClassName<ClassParams, ...>` ，并且用这个模板类实例化所需的对象。这里有一个语法陷阱，如果你想使用一个全部取默认的模板参数的模板类，在 ``C++11`` 的标准下类名后的尖括号是不能省略的，即 :expr:`ClassName<>` 。

以 CimNet 的 :class:`Network` 为例：

.. code-block:: cpp

    Network<int, std::string, double> net;
    net.add_edge(1, 3);

上例中第一行实例化了一个 :class:`Network` 类的空实例 :expr:`n` ，这个模板类接受了三个模板参数。第二行调用了 :class:`Network` 中的 :func:`add_edge<Network::add_edge>` 方法来修改网络 :expr:`net` ，你不能直接修改实现网络的数据结构，只能通过提供的接口来访问内部的数据结构，这些接口会保证进行的修改是合理有效的，一定程度上保证了网络不会出现意外的错误。

.. _pointer-and-reference:

对象的指针与引用
----------------

类似 C 语言中的语法，你可以创建一个对象的指针，手动创建它的内存空间，并且在使用完毕后释放。上例也可以写成如下形式：

.. code-block:: cpp

    typedef Network<int, std::string, double> MyNetwork;
    MyNetwork *net = new MyNetwork;
    net->add_edge(1, 3);
    delete n;

使用 :expr:`typedef` 语句来简化对模板类的表达。程序的第二行实例化了一个 :class:`Network` 对象，分配了它的内存空间，初始化它为一个空的网络，并把它的地址赋值给指针变量 :expr:`net` 。 :expr:`new ClassName(params, ...)` 后的初始化参数列表可以省略，它会在初始化的时候调用默认构造器。指针变量的方法使用 :expr:`->` 而不是 :expr:`.` 访问。最后使用 :expr:`delete` 语句释放 :expr:`net` 的内存。需要注意的是，你要保证程序逻辑里的每一个被 :expr:`new` 创建的对象都被 :expr:`delete` 释放，不然会造成大量内存泄漏。

如果你需要在函数间传递对象，又要避免参数拷贝浪费的时间，建议使用引用。引用可以让你像使用原始变量一样使用引用变量，同时不会占用额外空间和拷贝时间——你修改的就是原始变量。某种意义上，引用变量是原始变量的一个别名。

.. code-block:: cpp
    :linenos:

    typedef Network<int, std::string, double> MyNetwork;

    void print_degree_ref(const MyNetwork &net) {
        std::cout << n.total_degree() << std::endl;
    }

    void print_degree_ptr(const MyNetwork *net) {
        std::cout << net->total_degree() << std::endl;
    }

    int main(void) {
        MyNetwork net;
        net.add_edge(1, 3);
        print_degree_ref(net);
        print_degree_ptr(&net);
        return 0;
    }

程序用两种方式定义了打印网络总度数的函数。参数列表前的 :expr:`const` 保证变量不会在函数内部被改变。两个函数参数中的变量 :expr:`net` 都指代 :expr:`main` 函数里的网络变量 :expr:`net` ，都不会对整个变量进行拷贝，只不过一种是用指针方式，一种是用引用方式。你可以从这个例子中感受这两种方式的差异。

.. _looping-on-stl:

标准容器类的遍历
----------------

``C++11`` 提供了大量模板容器类便于你存储各种结构的数据，我们以最常用的一种容器介绍 ``C++11`` 的语言特性。

:expr:`std::vector` 是标准库提供的一种动态数组容器，以下是一个使用的例子：

.. code-block:: cpp

    std::vector<std::string> array;
    array.push_back("Data 1");
    array.push_back("Data 2");
    array.push_back("Data 3");

:expr:`std::vector<std::string>` 表示这个容器是用来装字符串类型的。 :expr:`array` 中依次插入了三个字符串。你可以用 :expr:`array[2]` 访问字符串 :expr:`"Data 3"` 。如果你想遍历这个容器，常用的方式是这样：

.. code-block:: cpp

    for (int i = 0; i < array.size(); ++i)
        std::cout << array[i] << std::endl;

``C++11`` 提供了一种更方便的方式遍历容器：

.. code-block:: cpp

    for (auto &s : array)
        std::cout << s << std::endl;

与 C 语言中的 :expr:`auto` 不同， C++ 的 :expr:`auto` 表达的是对此处变量类型的推导。也就是此处不需要显示指明变量 :expr:`s` 的类型，编译器可以自行推导。与上文介绍的引用变量一样，这里的 :expr:`s` 也是引用，是容器内存储元素的引用，它在遍历过程中也可以不占用额外空间地快速访问 :expr:`array` 中的元素。（事实上这种遍历方式是通过访问容器迭代器 :expr:`std::vector<_Type>::iterator` 实现的，它是 ``C++11`` 的一个协议式语法糖，不过这里不再讨论其实现细节，只需要知道这种遍历方式十分方便即可。） :class:`Network` 类中的 :func:`neighbors(NodeId id)<Network::neighbors>` 方法返回的就是一个 :expr:`std::vector<NodeId>` ，你可以用一个新的 :expr:`std::vector` 接住这个返回值，也可以用它直接遍历：

.. code-block:: cpp

    for (auto &neighbor : net.neighbors(id))
        std::cout << neighbor << std::endl;

.. _inherit:

继承
----

谈到继承机制，就涉及到 C++ 的高级语法部分了，在该文档内难以赘述。此处提供一个最基础的继承代码范式，你可以替换其中的部分内容完成对 CimNet 网络基类的继承。

.. code-block:: cpp

    class MyNetwork: public Network<NodeId, NodeData, EdgeData>{
        public:
            MyNetwork(params...) {
                // Implementation
            }
    };

你可以将上面的 :expr:`MyNetwork` 替换为你的网络类名，在 :expr:`NodeId` ， :expr:`NodeData` 和 :expr:`EdgeData` 处分别填写网络中存储的 :expr:`节点编号类型` ， :expr:`节点数据` 和 :expr:`边数据` 。在 :expr:`// Implementation` 处编写网络的具体实现。如果你需要编写一个带模板语法的继承，或是在子类中添加独有的属性和方法，可以学习参考 :file:`cimnet/network.h` 中的实现或联系开发者。