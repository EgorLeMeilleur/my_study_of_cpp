//Дан невзвешенный неориентированный граф.Найдите цикл минимальной длины.

#include <iostream>
#include <vector>
#include <queue>

class Graph {
public:

    Graph() = default;
    Graph(int vertices) {
        ribs_array.resize(vertices);
    }

    void add_rib(int from, int to) {
        ribs_array[from].push_back(to);
        ribs_array[to].push_back(from);
    }

    int bfs(int bfs_vertex) {
        int min_cycle = std::numeric_limits<int>::max();
        std::vector<int> distances(ribs_array.size(), std::numeric_limits<int>::max());
        std::vector<int> parents(ribs_array.size(), -1);
        distances[bfs_vertex] = 0;
        std::queue<int> q;
        q.push(bfs_vertex);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int child : ribs_array[v]) {
                if (distances[child] == std::numeric_limits<int>::max()) {
                    distances[child] = distances[v] + 1;
                    parents[child] = v;
                    q.push(child);
                }
                else if (parents[v] != child && parents[child] != v) {
                    min_cycle = std::min(min_cycle, distances[v] + distances[child] + 1);
                }
            }
        }
        return min_cycle;
    }

    int cycle_min_length() {
        int min_length = std::numeric_limits<int>::max();
        for (int i = 0; i < ribs_array.size(); ++i) {
            min_length = std::min(min_length, bfs(i));
        }
        return min_length = (min_length == std::numeric_limits<int>::max() ? -1 : min_length);
    }

private:
    std::vector<std::vector<int>> ribs_array;
};

int main() {
    int vertices = 0, ribs = 0;
    std::cin >> vertices;
    std::cin >> ribs;
    Graph graph(vertices);
    for (int i = 0; i < ribs; ++i) {
        int from = 0, to = 0;
        std::cin >> from >> to;
        graph.add_rib(from, to);
    }
    std::cout << graph.cycle_min_length();
    return 0;
}
