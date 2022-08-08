#pragma once
#include "IGraph.h"

class CSetGraph : public IGraph {
public:
    CSetGraph() = default;
    ~CSetGraph() = default;
    explicit CSetGraph(IGraph* other);

    virtual void AddEdge(int from, int to) override;

    virtual int VerticesCount() const override;

    virtual void FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const override;
    virtual void FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const override;

protected:
    std::vector<std::unordered_set<int>> set_graph_lists;

    void check_vertex(int v) const;
    bool is_vertex_in_list(const std::unordered_set<int>& l, int vertex) const;

    static void array_to_set(const std::vector<int>& array, std::unordered_set<int>& set);
    static void set_to_array(std::vector<int>& array, const std::unordered_set<int>& set);
};