//Дано невзвешенное дерево.
//Расстоянием между двумя вершинами будем называть количество ребер в пути, соединяющем эти две вершины.
//Для каждой вершины определите расстояние до самой удаленной от нее вершины.
//Время работы должно быть O(n).

#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> CTree;

std::ostream& operator<<(std::ostream& os, const std::vector<int>& data)
{
    for (int i = 0; i < data.size(); i++)
    {
        os << i << " " << data[i] << "\n";
    }
    return os;
}

void traverse(const CTree& tree, int node, std::vector<int>& heights)
{
    for (int child : tree[node])
    {
        traverse(tree, child, heights);
    }
    heights[node] = 0;
    for (int child : tree[node]) 
    {
        if (heights[child] + 1 > heights[node]) 
        {
            heights[node] = heights[child] + 1;
        }
    }
}

void traverse2(const CTree& tree, int node, const std::vector<int>& lengths_down, std::vector<int>& lengths_up)
{
    int max_length_down = -1;
    int second_max_length_down = -1;
    for (int child : tree[node]) 
    {
        if (lengths_down[child] >= max_length_down)
        {
            second_max_length_down = max_length_down;
            max_length_down = lengths_down[child];
        }
        else if (lengths_down[child] > second_max_length_down)
        {
            second_max_length_down = lengths_down[child];
        }
    }   
    for (int child : tree[node])
    {
        lengths_up[child] = lengths_up[node] + 1;
        if (lengths_down[child] == max_length_down)
        {
            lengths_up[child] = std::max(lengths_up[child], second_max_length_down + 2);
        }
        else 
        {
            lengths_up[child] = std::max(lengths_up[child], max_length_down + 2);
        }
        traverse2(tree, child, lengths_down, lengths_up);
    }
}

std::vector<int> calc_max_distances(const CTree& tree)
{
    std::vector<int> lengths_down(tree.size());
    traverse(tree, 0, lengths_down);
    std::vector<int> lengths_up(tree.size());
    traverse2(tree, 0, lengths_down, lengths_up);
    std::vector<int> result(tree.size());
    for (int i = 0; i < lengths_down.size(); i++) 
    {
        result[i] = std::max(lengths_down[i], lengths_up[i]);
    }
    return result;
}

int main()
{
    int n;
    std::cin >> n;
    CTree tree(n);
    for (int i = 0; i < n - 1; i++) 
    {
        int parent, child;
        std::cin >> parent >> child;
        tree[parent].push_back(child);
    }
    std::vector<int> result = calc_max_distances(tree);
    for (int v : result)
    {
        std::cout << v << std::endl;
    }
}
