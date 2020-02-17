#include <iostream>
#include <vector>
#include "cimnet/_base_net.h"

/* Define types */
typedef std::string IpAddr;
typedef struct {
    std::string hostname;
    size_t n_sended;
    size_t n_received;
    size_t n_in_queue;
} HostData;
typedef unsigned int PageViewAmount;

class Internet {
    public:
        Internet() : net() {}
        ~Internet() {}

        IpAddr add_host(const IpAddr &addr, const std::string &hostname) {
            net.add_node(addr, {hostname, 0, 0, 0});
            return addr;
        }

        void add_hyperlink(const IpAddr &addr1, const IpAddr &addr2) {
            net.add_edge(addr1, addr2);
        }

        void send_tcp(const IpAddr &from, const IpAddr &to, size_t amount=1) {
            if (!net.is_neighbor(from, to)) {
                std::cout << from << " and " << to << " is not linked." << std::endl;
            } else {
                std::cout << "[TCP] from " << from << " to " << to
                    << " send " << amount << " packets." << std::endl;
                net[from].n_sended += amount;
                net[to].n_in_queue += amount;
                net[to].n_received += amount;
                net.edge(from, to) += amount;
            }
        }

        void send_udp(const IpAddr &from, const IpAddr &to, size_t amount=1) {
            if (!net.is_neighbor(from, to)) {
                std::cout << from << " and " << to << " is not linked." << std::endl;
            } else {
                std::cout << "[UDP] from " << from << " to " << to
                    << " send " << amount << " packets." << std::endl;
                net[from].n_sended += amount;
                net[to].n_in_queue += amount;
                net[to].n_received += amount;
                for (auto nei: net.neighbors(from))
                    net.edge(from, nei) += amount;
            }
        }

        void digest_packets(const IpAddr &host, size_t amount=1) {
            size_t &n_packets = net[host].n_in_queue;
            if (n_packets < amount)
                n_packets = 0;
            else
                n_packets -= amount;
        }

        void diagnose(const IpAddr &host) {
            std::cout << "Host \"" << net[host].hostname << "\" [ip="
                << host << "]:" << std::endl;
            std::cout << "  Send: " << net[host].n_sended << " packets.\n"
                << "  Receive: " << net[host].n_received << " packets.\n"
                << "  In queue: " << net[host].n_in_queue << " packets."
                << std::endl;
            std::cout << "  Linked host:" << std::endl;
            for (auto nei: net.neighbors(host))
                std::cout << "    To \"" << net[nei].hostname << "\" [ip="
                    << nei << "] traffic: " << net.edge(host, nei) << " packets."
                    << std::endl;
        }

    private:
        Network<IpAddr, HostData, PageViewAmount> net;
};


int main(void) {
    Internet net;

    /* Construct hosts. */
    IpAddr router = net.add_host("192.168.0.1", "ROUTER");
    std::vector<IpAddr> host = {
        net.add_host("192.168.0.100", "HOST 0"),
        net.add_host("192.168.0.101", "HOST 1"),
        net.add_host("192.168.0.102", "HOST 2"),
        net.add_host("192.168.0.103", "HOST 3"),
        net.add_host("192.168.0.104", "HOST 4"),
        net.add_host("192.168.0.105", "HOST 5"),
        net.add_host("192.168.0.106", "HOST 6"),
    };
    IpAddr server = net.add_host("118.26.6.6", "SERVER");

    /* Link hosts. */
    net.add_hyperlink(server, router);
    for (size_t i = 0; i < host.size(); i++)
        net.add_hyperlink(router, host[i]);

    /* Send packets. */
    net.send_tcp(server, router, 10);
    net.send_udp(router, host[2], 66);

    net.digest_packets(router, 999);
    net.digest_packets(server, 999);
    for (size_t i = 0; i < host.size(); i++)
        net.digest_packets(host[i], 5);

    net.diagnose(router);

    return 0;
}
