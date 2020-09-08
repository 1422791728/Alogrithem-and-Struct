#include <iostream>
#include <string>
#include <queue>
using namespace std;
class ElementType
{
public:
	string name;
	int id;
};
typedef struct cbNode
{
	ElementType data;
	struct cbNode* firstChild;
	struct cbNode* nextSibling;
}CBNode, * CBTree;
//二级指针目的是在函数内部开拓空间
void InitCBTree(CBTree* tree)
{
	*tree = new CBNode;
	(*tree)->firstChild = NULL;
	(*tree)->nextSibling = NULL;
}
static int id = 0;
void CreatCBTree(CBNode** node)
{
	string name;
	getline(cin, name);
	if (name.empty())
	{
		return;
	}
	if (*node == NULL)
	{
		InitCBTree(node);
	}
	(*node)->data.id = ++id;
	(*node)->data.name = name;
	cout << "请输入长子结点" << endl;
	CreatCBTree(&((*node)->firstChild));
	cout << "请输入兄弟结点" << endl;
	CreatCBTree(&((*node)->nextSibling));
}

static int tempIndex_ = 0;
static int id_ = 0;
string temp_[] = { "A","B","D","\0" ,"E" ,"\0" ,"\0" ,"C","F","\0","G","\0" ,"I" };
void CreatCBTree_Re(CBNode** node)
{
	string name;
	name = temp_[tempIndex_++];
	if (name.empty())
	{
		return;
	}
	if (*node == NULL)
	{
		InitCBTree(node);
	}
	(*node)->data.id = ++id_;
	(*node)->data.name = name;
	//cout << "请输入长子结点" << endl;
	CreatCBTree_Re(&((*node)->firstChild));
	//cout << "请输入兄弟结点" << endl;
	CreatCBTree_Re(&((*node)->nextSibling));
}
void PreOrderCBTree(CBNode* node)
{
	if (node)
	{
		cout << "[" << node->data.id << "," << node->data.name << "]-";
		PreOrderCBTree(node->firstChild);
		PreOrderCBTree(node->nextSibling);
	}
}
void InOrderCBTree(CBNode* node)
{
	if (node)
	{
		InOrderCBTree(node->firstChild);
		cout << "[" << node->data.id << "," << node->data.name << "]-";
		InOrderCBTree(node->nextSibling);
	}
}

void PostOrderCBTree(CBNode* node)
{
	if (node)
	{
		PostOrderCBTree(node->firstChild);
		PostOrderCBTree(node->nextSibling);
		cout << "[" << node->data.id << "," << node->data.name << "]-";
	}
}

void ZOrderCBTree(CBTree tree)
{

	queue<CBTree> que;
	que.push(tree);
	int zorder = 1;//层数
	CBNode* last = tree;	//该层的最后一个节点
	CBNode* lastChild = tree;//长子层最后一个子节点
	cout << "第一层" << endl;
	while (!que.empty())
	{
		CBNode* node = que.front();
		cout << "[" << node->data.id << "," << node->data.name << "]-";
		que.pop();
		CBNode* temp = node->firstChild;
		while (temp)
		{
			que.push(temp);
			lastChild = temp;
			temp = temp->nextSibling;
		}
		if (last == node && !que.empty())
		{
			zorder++;
			cout << endl;
			cout << zorder << "层" << endl;
			last = lastChild;
		}
	}
}
//int main()
//{
//	CBTree tree;
//	InitCBTree(&tree);
//	CreatCBTree_Re(&tree);
//	//PreOrderCBTree(tree);
//	//InOrderCBTree(tree);
//	//PostOrderCBTree(tree);
//	ZOrderCBTree(tree);
//}