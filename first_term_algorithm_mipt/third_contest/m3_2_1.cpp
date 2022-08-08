#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cassert>
struct TreapNode
{
	int Key;
	int Priority;
	TreapNode* Left;
	TreapNode* Right;
	explicit TreapNode(int key = 0, int priority = 0) :
		Key(key), Priority(priority), Left(nullptr), Right(nullptr) {}
};

std::pair<TreapNode*, TreapNode*> Split(TreapNode* root, int key)
{
	if (root == nullptr)
	{
		return std::make_pair(nullptr, nullptr);
	}
	if (key < root->Key)
	{
		std::pair<TreapNode*, TreapNode*> left_split = Split(root->Left, key);
		root->Left = left_split.second;
		return std::make_pair(left_split.first, root);
	}
	else
	{
		std::pair<TreapNode*, TreapNode*> right_split = Split(root->Right, key);
		root->Right = right_split.first;
		return std::make_pair(root, right_split.second);
	}
}

TreapNode* add_treap_node(TreapNode* root, TreapNode* new_node)
{
	assert(root != nullptr);
	assert(new_node != nullptr);
	if (new_node->Priority <= root->Priority)
	{
		if (new_node->Key < root->Key)
		{
			if (root->Left != nullptr)
			{
				root->Left = add_treap_node(root->Left, new_node);
			}
			else
			{
				root->Left = new_node;
			}
		}
		else
		{
			if (root->Right != nullptr)
			{
				root->Right = add_treap_node(root->Right, new_node);
			}
			else
			{
				root->Right = new_node;
			}
		}
	}
	else
	{
		std::pair<TreapNode*, TreapNode*> split_result = Split(root, new_node->Key);
		new_node->Left = split_result.first;
		new_node->Right = split_result.second;
		root = new_node;
	}
	return root;
}

void add_binary_tree_node(TreapNode* root, TreapNode* new_node)
{
	assert(root != nullptr);
	assert(new_node != nullptr);
	if (new_node->Key < root->Key)
	{
		if (root->Left != nullptr)
		{
			add_binary_tree_node(root->Left, new_node);
		}
		else
		{
			root->Left = new_node;
		}
	}
	else
	{
		if (root->Right != nullptr)
		{
			add_binary_tree_node(root->Right, new_node);
		}
		else
		{
			root->Right = new_node;
		}
	}
}

void clean_tree(TreapNode* root)
{
	if (root == nullptr)
	{
		return;
	}
	clean_tree(root->Left);
	clean_tree(root->Right);
	delete root;
}

int calc_depth(TreapNode* root)
{
	if (root == nullptr) return 0;
	return std::max(calc_depth(root->Left), calc_depth(root->Right)) + 1;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	int N;
	int nodes_quantity;
	std::cin >> nodes_quantity;
	std::vector < std::pair <int, int>> array(nodes_quantity);
	int key = 0, priority = 0;
	for (int i = 0; i < nodes_quantity; i++)
	{
		std::cin >> key >> priority;
		array[i] = std::make_pair(key, priority);
	}
	TreapNode* root_binary = nullptr;
	for (int i = 0; i < nodes_quantity; i++)
	{
		int binary_node = array[i].first;
		if (root_binary == nullptr)
		{
			root_binary = new TreapNode(binary_node);
		}
		else
		{
			add_binary_tree_node(root_binary, new TreapNode(binary_node));
		}
	}
	int binary_depth = calc_depth(root_binary);
	clean_tree(root_binary);
	TreapNode* root_treap = new TreapNode(array[0].first, array[0].second);
	for (int i = 1; i < nodes_quantity; i++)
	{
		root_treap = add_treap_node(root_treap, new TreapNode(array[i].first, array[i].second));
	}
	int treap_depth = calc_depth(root_treap);
	clean_tree(root_treap);
	std::cout << std::abs(binary_depth - treap_depth);
	return 0;
}