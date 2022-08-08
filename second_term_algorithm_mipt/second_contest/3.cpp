//Дан ориентированный граф.Определите, какое минимальное число ребер необходимо добавить, чтобы граф стал сильносвязным.В графе возможны петли.

#include <iostream>
#include <vector>
#include <algorithm>

typedef unsigned int uint;

class Graph {
public:
    Graph() = default;

    Graph(uint vertices_count, uint ribs_count) :
        vertices_count_(vertices_count), ribs_count_(ribs_count) {
        graph.resize(vertices_count);
        inverted_graph.resize(vertices_count);
    }

    void add_rib(uint from, uint to) {
        graph[from].push_back(to);
        inverted_graph[to].push_back(from);
    }

    void reverse_dfs(uint vertex, std::vector<uint>& vertices_time, std::vector<bool>& visited) const {
        static uint time = 0;
        visited[vertex] = true;
        for (auto v : inverted_graph[vertex]) {
            if (!visited[v]) {
                reverse_dfs(v, vertices_time, visited);
            }
        }
        vertices_time[vertex] = ++time;
    }

    void dfs(uint v, std::vector<bool>& visited, std::vector<uint>& components, uint component) const {
        visited[v] = true;
        components[v] = component;
        for (auto u : graph[v]) {
            if (!visited[u]) {
                dfs(u, visited, components, component);
            }
        }
    }

    std::vector<uint> main_dfs(const std::vector<uint>& vertices_time) const {
        std::vector<std::pair<uint, uint>> time_and_vertices(vertices_count_);
        for (uint i = 0; i < vertices_count_; ++i) {
            time_and_vertices.emplace_back(vertices_time[i], i);
        }
        std::sort(time_and_vertices.rbegin(), time_and_vertices.rend());
        std::vector<bool> visited(vertices_count_);
        std::vector<uint> components(vertices_count_);
        uint component = 0;
        for (auto v : time_and_vertices) {
            if (!visited[v.second]) {
                dfs(v.second, visited, components, component);
                ++component;
            }
        }
        components.push_back(component);
        return components;
    }

    std::vector<uint> Kosaraju_algorithm() const {
        std::vector<uint> vertices_time(vertices_count_);
        std::vector<bool> visited(vertices_count_);
        for (uint v = 0u; v < vertices_count_; ++v) {
            if (!visited[v]) {
                reverse_dfs(v, vertices_time, visited);
            }
        }
        std::vector<uint> components = main_dfs(vertices_time);
        return components;
    }

    std::vector<std::vector<uint>> make_new_condensed_graph(const std::vector<uint>& components, uint count_components, bool is_inverted_graph) const {
        std::vector<std::vector<uint>> condensed_graph(count_components);
        for (uint i = 0; i < vertices_count_; ++i) {
            std::vector<bool> flag(count_components);
            for (auto v : (is_inverted_graph ? inverted_graph[i] : graph[i])) {
                if (components[i] != components[v] && !flag[components[v]]) {
                    condensed_graph[components[i]].emplace_back(components[v]);
                    flag[components[v]] = true;
                }
            }
        }
        return condensed_graph;
    }

    uint count_ribs_to_strongly_connected() const {
        std::vector<uint> components = Kosaraju_algorithm();
        uint count_components = components[vertices_count_];
        components.pop_back();
        std::vector<std::vector<uint>> graph_condensation = make_new_condensed_graph(components, count_components, false);
        std::vector<std::vector<uint>> inversed_graph_condensation = make_new_condensed_graph(components, count_components, true);
        if (count_components == 1) { return 0; }
        uint origins = 0, drains = 0;
        for (uint i = 0u; i < count_components; ++i) {
            if (graph_condensation[i].empty()) { ++origins; }
        }
        for (uint i = 0; i < count_components; ++i) {
            if (inversed_graph_condensation[i].empty()) { ++drains; }
        }
        return std::max(origins, drains);
    }

private:
    std::vector<std::vector<uint>> graph;
    std::vector<std::vector<uint>> inverted_graph;
    uint vertices_count_;
    uint ribs_count_;
};

int main() {
    uint vertices = 0, ribs = 0;
    std::cin >> vertices >> ribs;
    Graph graph(vertices, ribs);
    for (size_t i = 0u; i < ribs; ++i) {
        uint from = 0, to = 0;
        std::cin >> from >> to;
        graph.add_rib(from - 1, to - 1);
    }
    std::cout << graph.count_ribs_to_strongly_connected();
    return 0;
}
