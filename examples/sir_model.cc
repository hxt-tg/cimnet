#include <iostream>
#include <vector>
#include "cimnet/network.h"
#include "cimnet/random.h"

typedef enum {
    Susceptible,
    Infected,
    Recovered
} Compartment;

typedef struct {
    Compartment status;
} NodeData;

class SIRSimulation {
    typedef Network<int, NodeData, None> SIRNetwork;
    public:
    SIRSimulation(SIRNetwork &n, double beta, double gamma,
            double init_I_rate=0.01)
        : _step(0), _beta(beta), _gamma(gamma), net(n) {
        std::vector<int> nodes = net.nodes();
        for (auto i = 0; i < (int)nodes.size() - 1; i++)
            std::swap(nodes[i], nodes[randi(nodes.size()-i-1)+i+1]);
        int init_I_num = init_I_rate * net.number_of_nodes();

        for (int i = 0; i < net.number_of_nodes(); i++)
            net[nodes[i]].status = i < init_I_num ? Infected : Susceptible;
    }

    void step() {
        _step++;
        auto nodes = net.nodes();
        int N = net.number_of_nodes();
        for (int i = 0; i < N; i++) {
            int x = nodes[randi(N)];
            switch (net[x].status) {
                case Susceptible:
                    {
                        bool has_infected=false;
                        for (auto &n: net.neighbors(x))
                            if (net[n].status == Infected) {
                                has_infected = true;
                                break;
                            }
                        if (has_infected && randf() < _beta)
                            net[x].status = Infected;
                        break;

                    }
                case Infected:
                    if (randf() < _gamma)
                        net[x].status = Recovered;
                    break;
                default:
                    break;
            }
        }
    }

    void stat() {
        int cnt[3] = {0};
        for (auto &n: net.nodes())
            cnt[net[n].status] ++;
        double N = net.number_of_nodes();
        printf("[%4d] S:%6.2lf I:%6.2lf R:%6.2lf\n", _step,
                cnt[Susceptible]/N, cnt[Infected]/N, cnt[Recovered]/N);
    }

    private:
    int _step;
    double _beta;
    double _gamma;
    SIRNetwork net;
};

int main(void) {
    FullConnectedNetwork<NodeData, None> net(100);
    SIRSimulation sir(net, 0.1, 0.08);
    for (int i = 0; i < 100; i++) {
        sir.step();
        sir.stat();
    }
    return 0;
}

