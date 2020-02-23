#ifndef CIMNET_NETWORK
#define CIMNET_NETWORK

#include "_base_net.h"
#include "random.h"

template <class _NData=None, class _EData=None>
class FullConnectedNetwork;
template <class _NData, class _EData>
class FullConnectedNetwork: public Network<int, _NData, _EData>{
    public:
        FullConnectedNetwork(int n_nodes) {
            if (n_nodes < 0)
                throw NetworkException("Number of nodes should be positive.");

            for (int i = 0; i < n_nodes; i++)
                for (int j = i+1; j < n_nodes; j++)
                    this->add_edge(i, j);
        }
};


template <class _NData=None, class _EData=None>
class RegularNetwork;
template <class _NData, class _EData>
class RegularNetwork: public Network<int, _NData, _EData>{
    public:
        RegularNetwork(int n_nodes, int n_links) {
            if (n_nodes < 0)
                throw NetworkException("Number of nodes should be positive.");
            if (n_links < 0 || n_links > n_nodes - 1)
                throw NetworkException("Number of clockwise links should be "
                        "positive and less than number of nodes.");

            for (int i = 0; i < n_nodes; i++)
                for (int j = i + 1; j < i + 1 + n_links; j++)
                    this->add_edge(i, j % n_nodes);

            this->n_links = n_links;
        }
    private:
        int n_links;
};


template <class _NData=None, class _EData=None>
class ERNetwork;
template <class _NData, class _EData>
class ERNetwork: public Network<int, _NData, _EData>{
    public:
        ERNetwork(int n_nodes, double prob_link) {
            if (n_nodes < 0)
                throw NetworkException("Number of nodes should be positive.");
            if (prob_link > 1 || prob_link < 0)
                throw NetworkException("Probability of linking should be in [0, 1].");

            for (int i = 0; i < n_nodes; ++i)
                this->add_node(i);
            for (int i = 0; i < n_nodes; ++i)
                for (int j = i + 1; j < n_nodes; ++j)
                    if (randf() < prob_link)
                        this->add_edge(i, j);

            this->prob_link = prob_link;
        }
    private:
        double prob_link;
};


template <class _NData=None, class _EData=None>
class GridNetwork;
template <class _NData, class _EData>
class GridNetwork: public Network<int, _NData, _EData>{
    public:
        GridNetwork(int width, int height, int n_neighbors=4) {
            if (width < 0 || height < 0)
                throw NetworkException("Width and height should be positive.");
            if (n_neighbors < 0 || n_neighbors > width * height ||
                    n_neighbors % 4 != 0)
                throw NetworkException("Number of neighbors should be positive.");

            int w = width, h = height;
            for (int i = 0; i < h; ++i) {
                for (int j = 0; j < w; ++j) {
                    if (n_neighbors >= 4) {
                        this->add_edge(((i + h - 1) % h) * w + j, i * w + j);
                        this->add_edge(i * w + ((j + w - 1) % w), i * w + j);
                    }
                    if (n_neighbors >= 8) {
                        this->add_edge(((i + h - 1) % h) * w + (j + w - 1) % w, i * w + j);
                        this->add_edge(((i + 1) % h) * w + (j + w - 1) % w, i * w + j);
                    }
                }
            }

            this->width = width;
            this->height = height;
        }
    private:
        int width;
        int height;
};


template <class _NData=None, class _EData=None>
class CubicNetwork;
template <class _NData, class _EData>
class CubicNetwork: public Network<int, _NData, _EData>{
    public:
        CubicNetwork(int length, int width, int height) {
            if (length < 0 || width < 0 || height < 0)
                throw NetworkException("Length, width or height should be positive.");

            int h = height, w = width, l = length;
            for (int i = 0; i < h; ++i)
                for (int j = 0; j < l; ++j)
                    for (int k = 0; k < w; ++k) {
                        this->add_edge(((i + h - 1) % h) * w * l + j * w + k, i * w * l + j * w + k);
                        this->add_edge(i * w * l + ((j + l - 1) % l) * l + k, i * w * l + j * w + k);
                        this->add_edge(i * w * l + j * w + ((k + w - 1) % w), i * w * l + j * w + k);
                    }

            this->length = length;
            this->width = width;
            this->height = height;
        }
    private:
        int length;
        int width;
        int height;
};


template <class _NData=None, class _EData=None>
class HoneycombNetwork;
template <class _NData, class _EData>
class HoneycombNetwork: public Network<int, _NData, _EData>{
    public:
        HoneycombNetwork(int honeycomb_width, int honeycomb_height) {
            if (honeycomb_width < 0 || honeycomb_height < 0)
                throw NetworkException("Width or height of honeycomb should be positive.");

            int w = honeycomb_width, h = honeycomb_height;
            for (int i = 0; i < h; ++i) {
                for (int j = 0; j < w; ++j) {
                    this->add_edge(2 * (i * w + j), (2 * (i * w + j) + 2 * w + 1) % (2 * w * h));
                    this->add_edge(2 * (i * w + j), 2 * i * w + ((2 * j + 1) % (2 * w)));
                    this->add_edge(2 * i * w + ((2 * j + 1) % (2 * w)), 2 * i * w + ((2 * j + 2) % (2 * w)));
                }
            }

            this->honeycomb_width = honeycomb_width;
            this->honeycomb_height = honeycomb_height;
        }
    private:
        int honeycomb_width;
        int honeycomb_height;
};


template <class _NData=None, class _EData=None>
class KagomeNetwork;
template <class _NData, class _EData>
class KagomeNetwork: public Network<int, _NData, _EData>{
    public:
        KagomeNetwork(int kagome_width, int kagome_height) {
            if (kagome_width < 0 || kagome_height < 0)
                throw NetworkException("Width or height of kagome should be positive.");

            int w = kagome_width, h = kagome_height;
            for (int i = 0; i < h; ++i) {
                for (int j = 0; j < w; ++j) {
                    this->add_edge(3 * (i * w + j), 3 * (i * w + j) + 1);
                    this->add_edge(3 * (i * w + j), 3 * (i * w + j) + 2);
                    this->add_edge(3 * (i * w + j), 3 * (i * w + (j + 1) % w) + 1);
                    this->add_edge(3 * (i * w + j), 3 * (((i * w + j) + w) % (h * w)) + 2);
                    this->add_edge(3 * (i * w + j) + 2, 3 * (i * w + (j + 1) % w) + 1);
                    this->add_edge(3 * (i * w + j) + 1, 3 * (((i * w + j) + w) % (h * w)) + 2);
                }
            }

            this->kagome_width = kagome_width;
            this->kagome_height = kagome_height;
        }
    private:
        int kagome_width;
        int kagome_height;
};


template <class _NData=None, class _EData=None>
class ScaleFreeNetwork;
template <class _NData, class _EData>
class ScaleFreeNetwork: public Network<int, _NData, _EData>{
    public:
        ScaleFreeNetwork(int n_nodes, int n_edges_per_node) {
            if (n_nodes < 0)
                throw NetworkException("Number of nodes should be positive.");
            if (n_edges_per_node < 0 || n_edges_per_node > n_nodes)
                throw NetworkException("Increment of edges per node should be "
                        "positive and no more than number of nodes.");

            for (int i = 0; i < n_nodes; ++i)
                this->add_node(i);
            int m = n_edges_per_node;
            int vn = this->number_of_nodes(), cur = m;
            int i, j, nv;           /* nv = degree(v) */
            double t, total;        /* t is a copy of total but subjected by linked vex */
            while(cur < vn) {
                total = this->total_degree();
                for (i = 0; i < m; i++) {
                    t = total;
                    for (j = 0; j < cur; j++) {
                        if (this->has_edge(j, cur)) continue;
                        nv = this->degree(j);
                        t -= nv;
                        if (randf() > nv/(t + nv)) continue;
                        this->add_edge(j, cur);
                        total -= nv;
                        break;
                    }
                }
                cur++;
            }
            this->n_edges_per_node = n_edges_per_node;
        }
    private:
        int n_edges_per_node;;
};
#endif /* ifndef CIMNET_NETWORK */
