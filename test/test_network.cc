#include "cimnet/network.h"
#include <ctime>

typedef Network<int> TestNet;

void test_full_connected() {
    std::cout << "Test FullConnectedNetwork: n=10" << std::endl;
    FullConnectedNetwork<> n(10);
    std::cout << n << std::endl;
}

void test_regular() {
    std::cout << "Test RegularNetwork: n=10, m=3" << std::endl;
    RegularNetwork<> n(10, 3);
    std::cout << n << std::endl;
}

void test_er() {
    std::cout << "Test ERNetwork: n=10, p=0.1 (generate 100 times)" << std::endl;
    int n_edges = 0;
    for (int i = 0; i < 100; ++i) {
        ERNetwork<> n(10, 0.1);
        n_edges += n.number_of_edges();
    }
    std::cout << "Average #(edges)= " << n_edges / 100.0 << std::endl;
}

void test_grid() {
    std::cout << "Test GridNetwork: w=10, h=20" << std::endl;
    GridNetwork<> n(10, 20);
    std::cout << n << std::endl;
}

void test_cubic() {
    std::cout << "Test CubicNetwork: l=4, w=10, h=3" << std::endl;
    CubicNetwork<> n(4, 10, 3);
    std::cout << n << std::endl;
}

void test_honeycomb() {
    std::cout << "Test HoneycombNetwork: hw=4, hh=3" << std::endl;
    HoneycombNetwork<> n(4, 3);
    std::cout << n << std::endl;
}

void test_kagome() {
    std::cout << "Test KagomeNetwork: kw=3, kh=3" << std::endl;
    KagomeNetwork<> n(3, 3);
    std::cout << n << std::endl;
}

void test_scale_free() {
    std::cout << "Test ScaleFreeNetwork: n=100, m=2" << std::endl;
    ScaleFreeNetwork<> n(100, 2);
    std::cout << n << std::endl;
}

/* Function for creating custom mask function */
CustomizableGridNetwork<>::RangeMask cross_mask(double radius) {
    CustomizableGridNetwork<>::RangeMask mask;
    for (int i = 1; i <= (int)radius; i++) {
        mask.push_back(std::make_pair(0, i));
        mask.push_back(std::make_pair(0, -i));
        mask.push_back(std::make_pair(i, 0));
        mask.push_back(std::make_pair(-i, 0));
    }
    return mask;
}

void test_customizable_grid() {
    /* Test for Manhattan distance */
    CustomizableGridNetwork<> ln1(10, 10, 3);
    std::cout << "ManhattanMask grid:" << std::endl
              << ln1 << std::endl;
    /* Test for Euclidean distance */
    CustomizableGridNetwork<> ln2(10, 10, 3,
            CustomizableGridNetwork<>::EuclideanMask);
    std::cout << "EuclideanMask grid:" << std::endl
              << ln2 << std::endl;
    /* Test for custom mask */
    std::vector<std::pair<int, int>> mask;
    mask.push_back(std::make_pair( 0, 1));
    mask.push_back(std::make_pair( 0, 2));
    mask.push_back(std::make_pair( 1, 0));

    CustomizableGridNetwork<> ln3(10, 10, mask);
    std::cout << "Custom mask grid: " << std::endl
              << ln3 << std::endl;
    std::cout << "Node [" << 5 << "]: ";
    for (auto &y : ln3.neighbors(5))
        std::cout << y << " ";
    std::cout << std::endl;

    /* Test for custom mask function */
    CustomizableGridNetwork<> ln4(10, 10, 4, cross_mask);
    std::cout << "Custom mask function grid:" << std::endl
              << ln4 << std::endl;
}


int main(void) {
    unsigned long seed = time(NULL);
    sgenrand(seed);

    test_full_connected();
    test_regular();
    test_er();
    test_grid();
    test_cubic();
    test_honeycomb();
    test_kagome();
    test_scale_free();
    test_customizable_grid();
    return 0;
}
