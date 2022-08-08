#include "SetGraph.h"

CSetGraph::CSetGraph(IGraph* other) {
	set_graph_lists.clear();
	set_graph_lists.resize((*other).VerticesCount());
	for (int i = 0; i < (*other).VerticesCount(); ++i) {
		std::vector<int> neighbours;
		(*other).FindAllAdjacentOut(i, neighbours);
		array_to_set(neighbours, set_graph_lists[i]);
	}
}

void CSetGraph::AddEdge(int from, int to) {
	check_vertex(from);
	check_vertex(to);
	assert(from != to);
	assert(is_vertex_in_list(set_graph_lists[from], to));
	set_graph_lists[from].insert(to);
}

int CSetGraph::VerticesCount() const {
	return static_cast<int>(set_graph_lists.size());
}

void CSetGraph::FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const {
	check_vertex(vertex);
	vertices.clear();
	vertices.reserve(VerticesCount());
	for (int from = 0; from < set_graph_lists.size(); ++from) {
		if (is_vertex_in_list(set_graph_lists[from], vertex)) {
			vertices.push_back(from);
		}
	}
}

void CSetGraph::FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const {
	check_vertex(vertex);
	set_to_array(vertices, set_graph_lists[vertex]);
}

void CSetGraph::check_vertex(int v) const {
	assert(v >= 0 && v < set_graph_lists.size());
}

bool CSetGraph::is_vertex_in_list(const std::unordered_set<int>& l, int vertex) const {
	return std::find(l.begin(), l.end(), vertex) != l.end();
}

void CSetGraph::array_to_set(const std::vector<int>& array, std::unordered_set<int>& set) {
	set.clear();
	for (int i = 0; i < array.size(); ++i) {
		set.insert(array[i]);
	}
}

void CSetGraph::set_to_array(std::vector<int>& array, const std::unordered_set<int>& set) {
	array.clear();
	array.reserve(set.size());
	for (auto i = set.begin(); i != set.end(); ++i) {
		array.push_back(*i);
	}
}