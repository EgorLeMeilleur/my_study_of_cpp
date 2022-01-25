//Дано число N и N строк.Каждая строка содержащит команду добавления или удаления натуральных чисел, а также запрос на получение k - ой порядковой статистики.
//Команда добавления числа A задается положительным числом A, команда удаления числа A задается отрицательным числом “ - A”.
//Запрос на получение k - ой порядковой статистики задается числом k.Требуемая скорость выполнения запроса - O(log n).

#include <iostream>
#include <queue>
#include <cassert>

struct Node
{
    int Key;
    Node* Left;
    Node* Right;
    unsigned char Height;
    int Count;
    explicit Node(int key = 0) :
        Key(key), Left(nullptr), Right(nullptr), Height(1), Count(1) {}
};

int height(Node* node)
{
    return node != nullptr ? node->Height : 0;
}
int height_difference(Node* node)
{
    assert(node != nullptr);
    return height(node->Left) - height(node->Right);
}
void update_height(Node* node)
{
    assert(node != nullptr);
    node->Height = std::max(height(node->Left), height(node->Right)) + 1;
}

int Count(Node* node)
{
    return node != nullptr ? node->Count : 0;
}
void update_Count(Node*& node)
{
    node->Count = Count(node->Right) + Count(node->Left) + 1;
}

Node* rotate_right(Node* left, Node* parent)
{
    assert(left != nullptr);
    assert(parent != nullptr);
    parent->Left = left->Right;
    left->Right = parent;
    update_height(parent);
    update_height(left);
    update_Count(parent);
    update_Count(left);
    return left;
}
Node* rotate_left(Node* right, Node* parent)
{
    assert(right != nullptr);
    assert(parent != nullptr);
    parent->Right = right->Left;
    right->Left = parent;
    update_height(parent);
    update_height(right);
    update_Count(parent);
    update_Count(right);
    return right;
}

Node* recover_invariant(Node* node)
{
    update_Count(node);
    update_height(node);
    const int height_diff = height_difference(node);
    assert(std::abs(height_diff) <= 2);
    if (height_diff == 2) {
        // Либо малое правое, либо большое правое.
        if (height_difference(node->Left) < 0) {
            node->Left = rotate_left(node->Left->Right, node->Left);
        }
        node = rotate_right(node->Left, node);
    }
    else if (height_diff == -2) {
        // Либо малое левое, либо большое леве.
        if (height_difference(node->Right) > 0) {
            node->Right = rotate_right(node->Right->Left, node->Right);
        }
        node = rotate_left(node->Right, node);
    }
    return node;
}

Node* add_node(Node* root, int new_key)
{
    if (root == nullptr)
    {
        return new Node(new_key);
    }
    if (new_key < root->Key) {
        root->Left = add_node(root->Left, new_key);
    }
    else {
        root->Right = add_node(root->Right, new_key);
    }
    return recover_invariant(root);
}

Node* find_min(Node* root)
{
    assert(root != nullptr);
    while (root->Left != nullptr)
    {
        root = root->Left;
    }
    return root;
}
Node* detach_min_node(Node* root)
{
    if (root->Left != nullptr)
    {
        root->Left = detach_min_node(root->Left);
    }
    else
    {
        return root->Right;
    }
    return recover_invariant(root);
}

Node* delete_node(Node* root, int key)
{
    if (root == nullptr)
    {
        return root;
    }
    if (key < root->Key)
    {
        root->Left = delete_node(root->Left, key);
    }
    else if (key > root->Key)
    {
        root->Right = delete_node(root->Right, key);
    }
    else
    {
        if (root->Left == nullptr || root->Right == nullptr)
        {
            Node* child = root->Left ? root->Left : root->Right;
            delete root;
            return child;
        }
        else
        {
            Node* min_node = find_min(root->Right);
            min_node->Right = detach_min_node(root->Right);
            min_node->Left = root->Left;
            delete root;
            root = min_node;
        }
    }
    return recover_invariant(root);
}

int find_k_order(Node* root, int k_order)
{
    assert(root != 0);
    int index = Count(root->Left);
    while (index != k_order)
    {
        if (k_order <= index)
        {
            root = root->Left;
            index = index - (1 + Count(root->Right));
        }
        else
        {
            root = root->Right;
            index = index + (1 + Count(root->Left));
        }
    }
    return root->Key;
}

void clean_tree(Node* node)
{
    if (node == nullptr)
    {
        return;
    }
    clean_tree(node->Left);
    clean_tree(node->Right);
    delete node;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int N;
    std::cin >> N;
    std::vector<int> vec(N);
    Node* root = nullptr;
    for (int i = 0; i < N; i++)
    {
        int key = 0, kstatistics = 0;
        std::cin >> key >> kstatistics;
        if (key > 0)
        {
            if (root == nullptr)
            {
                root = new Node(key);
            }
            else
            {
                root = add_node(root, key);
            }
        }
        else
        {
            root = delete_node(root, std::abs(key));
        }
        vec[i] = find_k_order(root, kstatistics);
    }
    for (int i = 0; i < N; i++)
    {
        std::cout << vec[i] << " ";
    }
    clean_tree(root);
    return 0;
}
