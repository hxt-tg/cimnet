/*
 * This file contains code from https://github.com/hxt-tg/cimnet
 * and is covered under the copyright and warranty notices:
 * "Copyright (C) 2020 CimNet Developers
 *  Xintao Hu <hxt.taoge@gmail.com>"
 */

/*
 *  This file contains several types of networks.
 *  For further usage, check out http://doc.hxtcloud.cn.
 *
 *
 *  Node labels are the integers 0 to n-1 if not specified in this docs.
 *
 *
 *  FullConnectedNetwork(int n_nodes)
 *
 *  Parameters
 *  n_nodes: nonnegative integer
 *      The number of nodes the fully connected network is to contain.
 *
 *  Create a fully connected network with n_nodes nodes.
 *
 *
 *  RegularNetwork(int n_nodes, int n_links)
 *
 *  Parameters
 *  n_nodes: nonnegative integer
 *      The number of nodes the regular network is to contain.
 *  n_links: nonnegative integer (less than n_nodes-1)
 *      The number of clockwise links.
 *
 *  Create a regular network with n_nodes nodes, in which degree
 *  of each node is 2 * n_links.
 *
 *
 *  ERNetwork(int n_nodes, double prob_link)
 *
 *  Parameters
 *  n_nodes: nonnegative integer
 *      The number of nodes.
 *  prob_link: floating point number (between 0 and 1)
 *      The probability of link creation.
 *
 *  Create a Erdős-Rényi network with n_nodes nodes and
 *  choose each of possible link with probability prob_link.
 *
 *
 *  GridNetwork(int width, int height, int n_neighbors=4)
 *
 *  Parameters
 *  width: nonnegative integer
 *      The width of the grid.
 *  height: nonnegative integer
 *      The height of the grid.
 *  n_neighbors: nonnegative integer (by default 4)
 *      The number of neighbors per node. Only support 4 & 8.
 *
 *  Create a 2-dimensional grid network of width * height.
 *
 *
 *  CustomizableGridNetwork(int width, int height, double radius,
 *                          MaskFunction mask_func=ManhattanMask)
 *  CustomizableGridNetwork(int width, int height, RangeMask &mask)
 *
 *  Parameters
 *  width: nonnegative integer
 *      The width of the grid.
 *  height: nonnegative integer
 *      The height of the grid.
 *  radius: double number
 *      The radius of neighboring range mask. Supporting Manhattan distance
 *      (ManhattanMask) and Euclidean distance (EuclideanMask).
 *  mask_func: CustomizableGridNetwork<>::MaskFunction (by default ManhattanMask)
 *      A function create a mask given radius of range.
 *  mask: A vector of pairs of integers
 *      A list of RangeShift which indicates the neighboring shift of each node.
 *
 *  Create a 2-dimensional grid network of width * height, where each
 *  node connects to neighbors given radius of range under Manhattan
 *  distance, Euclidean distance or custommized range mask function.
 *  If a customized mask is given, each node connects to neighbors
 *  according to the mask.
 *
 *
 *  CubicNetwork(int length, int width, int height)
 *
 *  Parameters
 *  length: nonnegative integer
 *      The length of the cube.
 *  width: nonnegative integer
 *      The width of the cube.
 *  height: nonnegative integer
 *      The height of the cube.
 *
 *  Create a cubic network of length * width * height.
 *
 *
 *  HoneycombNetwork(int honeycomb_width, int honeycomb_height)
 *
 *  Parameters
 *  honeycomb_width: nonnegative integer
 *      The width of a honeycomb.
 *  honeycomb_height: nonnegative integer
 *      The height of a honeycomb.
 *
 *  Create a honeycomb network given the size of honeycombs.
 *  The honeycomb network is a network whose nodes and edges
 *  are the hexagonal tiling of the plane.
 *  For more details see: https://en.wikipedia.org/wiki/Honeycomb_structure
 *
 *
 *  KagomeNetwork(int kagome_width, int kagome_height)
 *
 *  Parameters
 *  kagome_width: nonnegative integer
 *      The width of a Kagome lattice.
 *  kagome_height: nonnegative integer
 *      The height of a Kagome lattice.
 *
 *  Create a Kagome lattice network given the size of a kagome lattice,
 *  which is combined by equilateral triangles and regular hexagons,
 *  arranged so that each hexagon is surrounded by triangles and vice versa.
 *  For more details see: https://en.wikipedia.org/wiki/Trihexagonal_tiling
 *
 *
 *  ScaleFreeNetwork(int n_nodes, int n_edges_per_node)
 *
 *  Parameters
 *  n_nodes: nonnegative integer
 *      The number of nodes.
 *  n_edges_per_node: nonnegative integer
 *      The number of neighbors of each node.
 *
 *  Create a scale-free (Barabási–Albert) network given the number of nodes
 *  and the number of edges per node.
 *  The scale-free network is constructed by attaching new nodes with
 *  a fixed number of edges that are preferentially attached to
 *  existing high-degree nodes.
 */

#ifndef CIMNET_NETWORK
#define CIMNET_NETWORK

#include "_base_net.h"
#include "random.h"

#include <cmath>


/* Utility functions */
inline int mod(int x, int m) {
    return (x%m + m) % m;
}
/* End of Utility functions */


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
            this->n_neighbors = n_neighbors;
        }
    private:
        int width;
        int height;
        int n_neighbors;
};


template <class _NData=None, class _EData=None>
class CustomizableGridNetwork;
template <class _NData, class _EData>
class CustomizableGridNetwork: public Network<int, _NData, _EData> {
    public:
    typedef std::pair<int, int> RangeShift;
    typedef std::vector<RangeShift> RangeMask;
    typedef RangeMask (*MaskFunction)(double);

    private:
    int width;
    int height;
    void _build(int width, int height, RangeMask &mask) {
        if (width < 0 || height < 0)
            throw NetworkException("Width and height should be positive.");
        int w = width, h = height;
        for (int x = 0; x < h; ++x)
            for (int y = 0; y < w; ++y)
                this->add_node(x * w + y);
        for (int x = 0; x < h; ++x)
            for (int y = 0; y < w; ++y)
                for (RangeShift &s : mask)
                    this->add_edge(x * w + y, mod(x+s.first, w) * w + mod(y+s.second, h));
        this->width = width;
        this->height = height;
    }

    public:
    CustomizableGridNetwork(int width, int height, RangeMask &mask) {
        this->_build(width, height, mask);
    }

    CustomizableGridNetwork(int width, int height, double radius,
            const MaskFunction func=CustomizableGridNetwork::ManhattanMask) {
        RangeMask mask = func(radius);
        this->_build(width, height, mask);
    }

    static RangeMask ManhattanMask(double radius) {
        RangeMask mask;
        int r = radius;
        for (int x = 0; x <= r; ++x)
            for (int y = 1; y <= r-x; ++y) {
                mask.push_back(std::make_pair( x,  y));
                mask.push_back(std::make_pair( y, -x));
                mask.push_back(std::make_pair(-x, -y));
                mask.push_back(std::make_pair(-y,  x));
            }
        return mask;
    }

    static RangeMask EuclideanMask(double radius) {
        RangeMask mask;
        int r = floor(radius);
        double square_radius = radius * radius;
        for (int x = 0; x <= r; ++x)
            for (int y = 1; y <= r; ++y) {
                if (x * x + y * y > square_radius) continue;
                mask.push_back(std::make_pair( x,  y));
                mask.push_back(std::make_pair( y, -x));
                mask.push_back(std::make_pair(-x, -y));
                mask.push_back(std::make_pair(-y,  x));
            }
        return mask;
    }
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
