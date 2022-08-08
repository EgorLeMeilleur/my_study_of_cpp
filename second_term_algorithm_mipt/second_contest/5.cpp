//Необходимо написать торгового советника для поиска арбитража.
//Арбитраж - это торговля по цепочке различных валют в надежде заработать на небольших различиях в коэффициентах.Например, есть следующие курсы валют :
//GBP / USD : 0.67
//RUB / GBP : 78.66
//USD / RUB : 0.02
//Имея 1$ и совершив цикл USD->GBP->RUB->USD, получим 1.054$.Таким образом заработав 5.4

#include <iostream>
#include <vector>
#include <queue>

struct Comparator {
    bool operator()(const std::pair<int, int> first, const std::pair<int, int> second) {
        return first.second < second.second;
    }
};

class Graph {
public:
    Graph() = default;

    Graph(unsigned int vertices) {
        valute_matrix.resize(vertices);
        for (size_t i = 0; i < vertices; ++i) {
            valute_matrix[i].resize(vertices);
        }
    }

    std::vector<int> next_vertex(int top) {
        std::vector<int> res;
        for (int i = 0; i < valute_matrix.size(); ++i) {
            if (valute_matrix[top][i] != -1)
                res.push_back(i);
        }
        return res;
    }

    bool arbitration() {
        for (int i = 0; i < valute_matrix.size(); ++i) {
            std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, Comparator> q;
            std::vector<double> trade(valute_matrix.size(), 1);
            q.push(std::make_pair(i, 1));
            while (!q.empty()) {
                auto current_vertex = q.top();
                q.pop();
                if (i == current_vertex.first && trade[i] > 1) { return true; }
                std::vector<int> next = next_vertex(current_vertex.first);
                for (int vertex : next) {
                    double new_trade = trade[current_vertex.first] * valute_matrix[current_vertex.first][vertex];
                    if (new_trade > trade[vertex]) {
                        trade[vertex] = new_trade;
                        q.push(std::pair<int, int>(vertex, trade[vertex]));
                    }
                }
            }
        }
        return false;
    }
    friend std::istream& operator>>(std::istream& out, Graph& value);

private:
    std::vector<std::vector<double>> valute_matrix;
};

std::istream& operator>>(std::istream& in, Graph& graph) {
    for (size_t i = 0; i < graph.valute_matrix.size(); ++i) {
        for (size_t j = 0; j < graph.valute_matrix.size(); ++j) {
            if (i != j) {
                std::cin >> graph.valute_matrix[i][j];
            }
        }
    }
    return in;
}

int main() {
    unsigned int vertices = 0;
    std::cin >> vertices;
    Graph graph(vertices);
    std::cin >> graph;
    std::cout << (graph.arbitration() ? "YES" : "NO");
    return 0;
}
