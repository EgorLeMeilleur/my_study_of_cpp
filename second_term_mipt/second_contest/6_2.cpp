//Найти в связном графе остовное дерево минимального веса. Алгоритм Крускала.

#include <iostream>
#include <vector>
#include <algorithm>

typedef unsigned int uint;

struct Ribs {
	Ribs(uint vertex_from_, uint vertex_to_, uint weight_) :
		vertex_from(vertex_from_), vertex_to(vertex_to_), weight(weight_) {
	}

	uint vertex_from;
	uint vertex_to;
	uint weight;
};

bool comp(const Ribs& first, const Ribs& second) {
	return (first.weight < second.weight);
}

class DisjointSetSystem {
public:
	DisjointSetSystem(uint n) {
		parent_.resize(n);
		for (uint i = 0u; i < n; ++i) {
			parent_[i] = i;
		}
		rank_.resize(n);
	}

	int find(uint v) {
		return (parent_[v] == v) ? v : parent_[v] = find(parent_[v]);
	}

	void unite(uint a, uint b) {
		a = find(a), b = find(b);
		if (rank_[a] > rank_[b]) {
			std::swap(a, b);
		}
		rank_[b] = std::max(rank_[b], rank_[a] + 1);
		parent_[a] = b;

	}

private:
	std::vector<uint> parent_;
	std::vector<uint> rank_;
};

class Graph {
public:
	Graph() = default;

	Graph(const uint vertexes_count, const uint ribs_count) :
		vertexes_count_(vertexes_count), ribs_count_(ribs_count) {
		ribs_array_.reserve(ribs_count_);
	}

	void add_rib(const Ribs& rib) {
		ribs_array_.push_back(rib);
	}

	uint Kruskal_algorithm()
	{
		DisjointSetSystem set_of_trees(vertexes_count_);
		std::sort(ribs_array_.begin(), ribs_array_.end(), comp);
		uint min_ostov_tree = 0;
		for (uint i = 0u; i < ribs_count_; ++i) {
			uint first_tree = ribs_array_[i].vertex_from,
				second_tree = ribs_array_[i].vertex_to,
				weight = ribs_array_[i].weight;
			if (set_of_trees.find(first_tree) != set_of_trees.find(second_tree)) {
				min_ostov_tree += weight;
				set_of_trees.unite(first_tree, second_tree);
			}
		}
		return min_ostov_tree;
	}

private:
	std::vector<Ribs> ribs_array_;
	uint vertexes_count_;
	uint ribs_count_;
};

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	uint vertexes_count = 0, ribs_count = 0;
	std::cin >> vertexes_count >> ribs_count;
	Graph graph(vertexes_count, ribs_count);
	uint vertexes_from = 0, vertexes_to = 0, weight = 0;
	for (uint i = 0u; i < ribs_count; ++i)
	{
		std::cin >> vertexes_from >> vertexes_to >> weight;
		graph.add_rib(Ribs(vertexes_from - 1, vertexes_to - 1, weight));
	}
	std::cout << graph.Kruskal_algorithm();
	return 0;
}