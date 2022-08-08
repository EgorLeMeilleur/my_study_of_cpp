#pragma once
#include "IGraph.h"

class CListGraph : public IGraph {
public:
    CListGraph() = default;
    ~CListGraph() = default;
    explicit CListGraph(IGraph* other);

    virtual void AddEdge(int from, int to) override;

    virtual int VerticesCount() const override;

    virtual void FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const override;
    virtual void FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const override;

protected:
    std::vector<std::vector<int>> adjacency_lists;

    void check_vertex(int v) const;
    bool is_vertex_in_list(const std::vector<int>& l, int vertex) const;
};
