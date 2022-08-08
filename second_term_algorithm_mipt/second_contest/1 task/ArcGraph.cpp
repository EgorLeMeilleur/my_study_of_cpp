#include "ArcGraph.h"

CArcGraph::CArcGraph(IGraph* other) {
	verticesCount = (*other).VerticesCount();
	from_to_list.clear();
	for (int i = 0; i < (*other).VerticesCount(); ++i) {
		std::vector<int> neighbours;
		(*other).FindAllAdjacentOut(i, neighbours);
		for (int to : neighbours) {
			from_to_list.push_back(std::make_pair(i, to));
		}
	}
}

void CArcGraph::AddEdge(int from, int to) {
	check_vertex(from);
	check_vertex(to);
	assert(from != to);
	assert(std::find(from_to_list.begin(), from_to_list.end(), std::pair<int, int>(from, to)) == from_to_list.end());
	from_to_list.push_back(std::make_pair(from, to));
}

int CArcGraph::VerticesCount() const {
	return verticesCount;
}

void CArcGraph::FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const {
	check_vertex(vertex);
	vertices.clear();
	vertices.reserve(VerticesCount());
	for (const auto& edge : from_to_list) {
		if (edge.second == vertex) {
			vertices.push_back(edge.first);
		}
	}
}

void CArcGraph::FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const {
	check_vertex(vertex);
	vertices.clear();
	vertices.reserve(VerticesCount());
	for (const auto& edge : from_to_list) {
		if (edge.first == vertex) {
			vertices.push_back(edge.second);
		}
	}
}

void CArcGraph::check_vertex(int v) const {
	assert(v >= 0 && v < verticesCount);
}
