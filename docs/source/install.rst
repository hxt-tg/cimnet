.. _cimnet-install:

安装 CimNet
===========

CimNet 最新版发布地址：`GitHub Releases <https://github.com/hxt-tg/cimnet/releases>`__

CimNet 无需安装，按照下述步骤使用这个库：

1. 在上面的发布地址下载 zip 文件；
2. 解压 zip 文件，将其中的 :file:`cimnet` 文件夹复制到你的工程文件夹下（或者你存放库的位置）；
3. 将你的工程目录加入编译环境的Include查询目录中。例如，如果你使用 :program:`g++` 作为编译器，可以用下面的命令编译一个单独的源码文件 :file:`main.cc` 。

    .. code-block:: sh

        g++ main.cc -o main.out -std=c++11 -O2 -I /path/to/your/project
