#ifndef CIMNET_NETWORK
#define CIMNET_NETWORK

#include "_base_net.h"

template <class _NData=None, class _EData=None> class WellMixNet;
template <class _NData, class _EData>
class WellMixNet
: public Network<int, _NData, _EData>{
    public:
        WellMixNet(int num){
            for (int i = 0; i < num; i++)
                for (int j = i+1; j < num; j++)
                    this->add_edge(i, j);

        }
};

#endif /* ifndef CIMNET_NETWORK */
