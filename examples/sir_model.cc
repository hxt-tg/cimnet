#include <iostream>
#include <vector>
#include "cimnet/_base_net.h"
#include "cimnet/network.h"
#include "cimnet/random.h"

/* TODO:
 * 1. Construct net.
 * 2. Setting Is randomly.
 * 3. loop step:
 *    async update a node (loop N times):
 *      if S: check if neighbors contain I
 *      if I: to R on probability gamma
 *      if R: continue
 */

typedef enum {
    Susceptible,
    Infected,
    Recovered
} Compartment;

typedef struct {
    Compartment status;
} NodeData;

class SIRSimulation {
    typedef Network<int, NodeData, _NoneType> SIRNetwork;
    public:
    SIRSimulation(SIRNetwork &net, double beta, double gamma,
            double init_I_rate=0.01)
        : _step(0), _beta(beta), _gamma(gamma), _n(net) {
        std::vector<int> nodes = _n.nodes();
        for (auto i = 0; i < (int)nodes.size() - 1; i++)
            std::swap(nodes[i], nodes[randi(nodes.size()-i-1)+i+1]);
        int init_I_num = init_I_rate * _n.number_of_nodes();

        for (int i = 0; i < _n.number_of_nodes(); i++)
            _n[nodes[i]].status = i < init_I_num ? Infected : Susceptible;
    }

    void step() {
        _step++;
        auto nodes = _n.nodes();
        int N = _n.number_of_nodes();
        for (int i = 0; i < N; i++) {
            int x = nodes[randi(N)];
            switch (_n[x].status) {
                case Susceptible:
                    bool has_infected;
                    has_infected=false;
                    for (auto n: _n.neighbors(x))
                        if (_n[n].status == Infected) {
                            has_infected = true;
                            break;
                        }
                    if (has_infected && randf() < _beta)
                        _n[x].status = Infected;
                    break;
                case Infected:
                    if (randf() < _gamma)
                        _n[x].status = Recovered;
                    break;
                default:
                    break;
            }
        }
    }

    void stat() {
        int cnt[3] = {0};
        for (auto n: _n.nodes())
            cnt[_n[n].status] ++;
        double N = _n.number_of_nodes();
        printf("[%4d] S:%6.2lf I:%6.2lf R:%6.2lf\n", _step,
                cnt[Susceptible]/N, cnt[Infected]/N, cnt[Recovered]/N);
    }

    private:
    int _step;
    double _beta;
    double _gamma;
    SIRNetwork _n;
};

int main(void) {
    WellMixNet<NodeData, _NoneType> net(100);
    SIRSimulation sir(net, 0.1, 0.08);
    for (int i = 0; i < 100; i++) {
        sir.step();
        sir.stat();
    }
    return 0;
}
