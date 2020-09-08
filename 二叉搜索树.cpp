// DataStructure.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include <iostream>
#include<iomanip>
#include <vector>
#include<algorithm>
#include <string>
using namespace std;
class BinarySortNode
{
public:
	int key;
	BinarySortNode* leftChild;
	BinarySortNode* rightChild;
	BinarySortNode()
	{
		leftChild = NULL;
		rightChild = NULL;
	}
};
typedef class BinarySortNode* BinarySortTree;
void CreateBST(BinarySortTree& tree, vector<int>& ve, int low, int high)
{
	if (low > high) return;
	if (!tree)//如果该结点不存在则创建空间
	{
		tree = new BinarySortNode;
	}
	int mid = (low + high) / 2;
	tree->key = ve[mid];
	CreateBST(tree->leftChild, ve, low, mid - 1);
	CreateBST(tree->rightChild, ve, mid + 1, high);
}

void InOrderTree(BinarySortTree& node)
{
	if (node)
	{
		InOrderTree(node->leftChild);
		cout << node->key << endl;
		InOrderTree(node->rightChild);
	}
}

BinarySortNode* SearchBST(BinarySortTree node, int key)
{
	if (!node || node->key == key)
	{
		return node;
	}
	else if (key < node->key)
	{
		return SearchBST(node->leftChild, key);
	}
	else
	{
		return SearchBST(node->rightChild, key);
	}
}

void InsertNode(BinarySortTree& tree, int key)
{
	if (!tree)
	{
		tree = new BinarySortNode;
		tree->key = key;
		return;
	}
	else if (tree->key > key)
	{
		InsertNode(tree->leftChild, key);
	}
	else
	{
		InsertNode(tree->rightChild, key);
	}
}
//int main()
//{
//	vector<int> ve = { 1,5,9,3,8,29,31,10 };
//	sort(ve.begin(), ve.end());
//	BinarySortTree tree = NULL;
//	CreateBST(tree, ve, 0, ve.size() - 1);
//	InOrderTree(tree);
//	int key = 0;
//	BinarySortTree  node = SearchBST(tree, key);
//	if (node != NULL)
//		cout << node->key << endl;
//	else
//	{
//		cout << "没有找到" << endl;
//		InsertNode(tree, key);
//		InOrderTree(tree);
//	}
//
//}