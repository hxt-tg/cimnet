#ifndef CIMNET_EXCEPTION
#define CIMNET_EXCEPTION

#include <exception>
#include <string>
#include <sstream>

#include "_types.h"

class NetworkException : public std::exception {
    public:
        NetworkException() : _info("Network error: ") {}
        NetworkException(const std::string &info) : _info("Network error: " + info) {}
        void set_info(const std::string &info){
            _info = std::string("Network error: " + info);
        }
        const char *what() const noexcept{
            return _info.c_str();
        }
    public:
        std::string _info;
};

template <class _NId=Id>
class NoEdgeException : public NetworkException {
    public:
        NoEdgeException(const _NId &id1, const _NId &id2){
            std::stringstream stream;
            stream << "No edge between " << id1 <<
                " and " << id2 << ".";
            set_info(stream.str());
        }
};

template <class _NId=Id>
class NoNodeException: public NetworkException {
    public:
        NoNodeException(const _NId &id){
            std::stringstream stream;
            stream << "Node " << id << " not found.";
            set_info(stream.str());
        }
};

#endif /* ifndef CIMNET_EXCEPTION */
