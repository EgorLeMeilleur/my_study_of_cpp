//Требуется отыскать самый короткий маршрут между городами.Из города может выходить дорога, которая возвращается в этот же город.
//Требуемое время работы O((N + M)log N), где N – количество городов, M – известных дорог между ними.
//N ≤ 10000, M ≤ 250000.
//Длина каждой дороги ≤ 10000.

#include <iostream>
#include <vector>
#include <set>

typedef unsigned int uint;

struct Edge {
    uint Vertex = 0;
    uint Weight = 0;
};

class Graph {
public:

    Graph() = default;

    Graph(uint vertices) {
        distance_list.resize(vertices);
    }

    void add_rib(uint from, uint to, uint length) {
        distance_list[from].push_back({ to, length });
        distance_list[to].push_back({ from, length });
    }

    uint Dijkstra(uint start, uint end) const {
        auto distance = std::vector<uint>(distance_list.size(), std::numeric_limits<uint>::max());
        std::set<std::pair<uint, uint>> q;
        q.insert({ 0, start });
        distance[start] = 0;
        while (!q.empty()) {
            auto it = q.begin();
            uint u = it->second;
            q.erase(it);
            for (auto& e : distance_list[u]) {
                uint v = e.Vertex;
                if (distance[u] + e.Weight < distance[v]) {
                    auto itv = q.find({ distance[v], v });
                    if (itv != q.end()) {
                        q.erase(itv);
                    }
                    distance[v] = distance[u] + e.Weight;
                    q.insert({ distance[v], v });
                }
            }
        }
        return distance[end];
    }

private:
    std::vector<std::vector<Edge>> distance_list;
};

int main() {
    uint vertices = 0, ribs = 0;
    std::cin >> vertices;
    std::cin >> ribs;
    Graph graph(vertices);
    for (uint i = 0; i < ribs; ++i) {
        uint from = 0, to = 0, length = 0;
        std::cin >> from >> to >> length;
        graph.add_rib(from, to, length);
    }
    uint start = 0, end = 0;
    std::cin >> start >> end;
    std::cout << graph.Dijkstra(start, end) << std::endl;
    return 0;
}
