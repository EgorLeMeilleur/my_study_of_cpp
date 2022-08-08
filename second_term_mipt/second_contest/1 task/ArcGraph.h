#pragma once
#include "IGraph.h"

class CArcGraph : public IGraph {
public:
    CArcGraph() = default;
    ~CArcGraph() = default;
    explicit CArcGraph(IGraph* other);

    virtual void AddEdge(int from, int to) override;

    virtual int VerticesCount() const override;

    virtual void FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const override;
    virtual void FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const override;

protected:
    int verticesCount;
    std::vector<std::pair<int, int>> from_to_list;

    void check_vertex(int v) const;
};