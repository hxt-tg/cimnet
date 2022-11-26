/*
 * This file contains code from https://github.com/hxt-tg/cimnet
 * and is covered under the copyright and warranty notices:
 * "Copyright (C) 2022 CimNet Developers
 *  Xintao Hu <hxt.taoge@gmail.com>"
 */

/*
 *  This file contains exception classes for CimNet.
 *  For further usage, check out http://doc.hxtcloud.cn.
 */

#ifndef CIMNET_EXCEPTION
#define CIMNET_EXCEPTION

#include <exception>
#include <string>
#include <sstream>

#include "_types.h"

class NetworkException : public std::exception {
    public:
        NetworkException() : _info("Network error: ") {}
        explicit NetworkException(const std::string &info) : _info("Network error: " + info) {}
        void set_info(const std::string &info){
            _info = std::string("Network error: " + info);
        }
        const char *what() const noexcept override {
            return _info.c_str();
        }
    public:
        std::string _info;
};

template <class _NId=Id>
class NoEdgeException : public NetworkException {
    public:
        NoEdgeException(const _NId &id1, const _NId &id2, bool is_directed=false) {
            std::stringstream stream;
            if (is_directed)
                stream << "No edge from " << id1 <<
                    " to " << id2 << ".";
            else
                stream << "No edge between " << id1 <<
                    " and " << id2 << ".";
            set_info(stream.str());
        }
};

template <class _NId=Id>
class NoNodeException: public NetworkException {
public:
    explicit NoNodeException(const _NId &id){
        std::stringstream stream;
        stream << "Node " << id << " not found.";
        set_info(stream.str());
    }
};

template <class _NId=Id>
class NoNeighborsException: public NetworkException {
public:
    explicit NoNeighborsException(const _NId &id){
        std::stringstream stream;
        stream << "Node " << id << " has no neighbors.";
        set_info(stream.str());
    }
};

#endif /* ifndef CIMNET_EXCEPTION */
