#pragma once
#include "IGraph.h"

class CMatrixGraph : public IGraph {
public:
    CMatrixGraph() = default;
    ~CMatrixGraph() = default;
    explicit CMatrixGraph(IGraph* other);

    virtual void AddEdge(int from, int to) override;

    virtual int VerticesCount() const override;

    virtual void FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const override;
    virtual void FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const override;

protected:
    std::vector<std::vector<int>> adjacency_matrix;

    void check_vertex(int v) const;
};