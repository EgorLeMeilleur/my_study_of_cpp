//Дано число N < 106 и последовательность целых чисел из[-231..231] длиной N.
//Требуется построить бинарное дерево поиска, заданное наивным порядком вставки.Т.е., при добавлении очередного числа K в дерево с корнем root, 
//если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
//Выведите элементы в порядке level - order(по слоям, “в ширину”).

#include <iostream>
#include <queue>

struct Node
{
    int key;
    Node* left;
    Node* right;
    explicit Node(int key = 0) :
        key(key), left(nullptr), right(nullptr) {}
};

void add_node(Node* root, Node* new_node)
{
    std::queue<Node*> nodes; 
    if (root != nullptr)
    {
        nodes.push(root);
    }
    while (!nodes.empty())
    {
        root = nodes.front();
        nodes.pop();
        if (new_node->key < root->key && root->left == nullptr)
        {
            root->left = new_node;
        }
        else if (new_node->key > root->key && root->right == nullptr)
        {
            root->right = new_node;
        }
        else if (new_node->key < root->key && root->left != nullptr)
        {
            nodes.push(root->left);
        }
        else 
        {
            nodes.push(root->right);
        }
    }
}
void print_tree(Node* root, std::ostream& stream)
{
    std::queue<Node*> nodes;
    if (root != nullptr)
    {
        nodes.push(root);
    }
    while (!nodes.empty())
    {
        Node* node = nodes.front();
        nodes.pop();
        stream << node->key << " ";
        if (node->left != nullptr)
        {
            nodes.push(node->left);
        }
        if (node->right != nullptr)
        {
            nodes.push(node->right);
        }
    }
}
void clean_tree(Node* root)
{
    std::queue<Node*> nodes;
    if (root != nullptr)
    {
        nodes.push(root);  
    }
    else
    {
        return;
    }
    while (!nodes.empty())
    {
        root = nodes.front();
        nodes.pop();
        if (root->left != nullptr)
        {
            nodes.push(root->left);
        }  
        if (root->right != nullptr)
        {
            nodes.push(root->right);
        }
        delete root;
    }
}
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int nodes_quantity;
    std::cin >> nodes_quantity;
    Node* root = nullptr;
    for (int i = 0; i < nodes_quantity; i++)
    {
        int new_node;
        std::cin >> new_node;
        if (root == nullptr)
        {
            root = new Node(new_node);
        }
        else
        {
            add_node(root, new Node(new_node));
        }
    }
    print_tree(root, std::cout);
    clean_tree(root);
    return 0;
}
