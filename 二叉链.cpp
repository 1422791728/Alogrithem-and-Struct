#include<iostream>
#include <string>
using namespace std;
class ElementType
{
public:
	string name;
	int id;
};
class TreeNode
{
public:
	ElementType data;
	TreeNode* left;
	TreeNode* right;
};
class BinaryTree
{
public:
	TreeNode* root;
	int length;//结点个数
	int depth;//深度
	int diameter;//直径
	BinaryTree()
	{
		root = NULL;
		length = 0;
		depth = 0;
		diameter = 0;
	}
};
static int id = 0;//id记录
int CreatBinaryTree(TreeNode* root)
{
	if (!root)
	{
		return 0;
	}
	string name;
	getline(cin, name);
	if (name.empty())
	{
		return 0;
	}
	root->data.id = ++id;
	root->data.name = name;
	cout << "左结点" << endl;
	root->left = new TreeNode; 
	if (CreatBinaryTree(root->left) == 0)
	{
		delete root->left;
		root->left = NULL;
	}
	cout << "右结点" << endl;
	root->right = new TreeNode;
	if (CreatBinaryTree(root->right) == 0)
	{
		delete root->right;
		root->right = NULL;
	}
	return 1;
}
//前序遍历
void PreOrderTraverse(TreeNode* node)
{
	if (node)
	{
		cout << "[" << node->data.id << "," << node->data.name << "]-";
		PreOrderTraverse(node->left);
		PreOrderTraverse(node->right);
	}
}
//中序遍历
void InOrderTraverse(TreeNode* node)
{
	if (node)
	{
		InOrderTraverse(node->left);
		cout << "[" << node->data.id << "," << node->data.name << "]-";
		InOrderTraverse(node->right);
	}
}
//后序遍历
void PostOrderTraverse(TreeNode* node)
{
	if (node)
	{
		PostOrderTraverse(node->left);
		PostOrderTraverse(node->right);
		cout << "[" << node->data.id << "," << node->data.name << "]-";
	}
}
string temp[] = { "A","B","D","\0" ,"\0" ,"E","\0" ,"\0" ,"C","F","\0","\0","G","\0" ,"\0" };
static int tempIndex = 0;
static int _id = 0;
int CreatBinaryTree_Test(TreeNode* root)
{
	if (!root)
	{
		return 0;
	}
	string name;
	name = temp[tempIndex++];
	if (name.empty())
	{
		return 0;
	}
	root->data.id = ++_id;
	root->data.name = name;
	//cout << "左结点" << endl;
	root->left = new TreeNode;
	if (CreatBinaryTree_Test(root->left) == 0)
	{
		delete root->left;
		root->left = NULL;
	}
	//cout << "右结点" << endl;
	root->right = new TreeNode;
	if (CreatBinaryTree_Test(root->right) == 0)
	{
		delete root->right;
		root->right = NULL;
	}
	return 1;
}


//以下是实现非递归中序遍历二叉树的
class StackNode
{
public:
	TreeNode* data;
	StackNode* next;
};
class LinkedStack
{
public:
	StackNode* top;//头端
	int length;
	LinkedStack()
	{
		top = NULL;
		length = 0;
	}
};
bool Push(LinkedStack* linked, TreeNode* node)
{
	StackNode* tempNode = new StackNode;
	tempNode->data = node;
	tempNode->next = linked->top;
	linked->top = tempNode;
	linked->length++;
	return true;
}
bool IsLinkedStackEmpty(LinkedStack* linked)
{
	if (linked->top == NULL || linked->length == 0)
	{
		return 1;
	}
	return 0;
}
bool Pop(LinkedStack* linked, TreeNode** node)
{
	if (IsLinkedStackEmpty(linked))
	{
		return false;
	}
	*node = linked->top->data;
	StackNode* currnode = linked->top;
	linked->top = linked->top->next;
	delete currnode;
	currnode = NULL;
	linked->length--;
	return false;
}
void InOrderTraverse_Re(TreeNode* node)
{
	LinkedStack* linked = new LinkedStack;
	TreeNode* root = node;
	TreeNode* curr = NULL;
	while (root || !IsLinkedStackEmpty(linked))
	{
		if (root)
		{
			Push(linked, root);
			root = root->left;
		}
		else
		{
			Pop(linked, &curr);
			cout << "[" << curr->data.id << "," << curr->data.name << "]-";
			root = curr->right;
		}
	}
	delete linked;
}
//以下是为了层序遍历准备的
class QueueNode
{
public:
	TreeNode* data;
	QueueNode* next;
};
class LinkedQueue
{
public:
	QueueNode* front;
	QueueNode* tail;
	LinkedQueue()
	{
		front = NULL;
		tail = NULL;
	}
};
bool EnQueue(LinkedQueue * queue,TreeNode * node)
{
	QueueNode* tempNode = new QueueNode;
	if (tempNode == NULL)
	{
		exit(-1);
	}
	tempNode->data = node;
	tempNode->next = NULL;
	if (queue->front == NULL)
	{
		queue->front = queue->tail = tempNode;
	}
	else
	{
		queue->tail->next = tempNode;
		queue->tail = tempNode;
	}
	return true;
}
TreeNode* DeQueue(LinkedQueue* queue)
{
	TreeNode* tempNode = NULL;
	if (queue->front == NULL) return tempNode;
	QueueNode* node = queue->front;
	tempNode = queue->front->data;
	if (queue->front == queue->tail)
	{
		queue->front = queue->tail = NULL;
	}
	else
	{
		queue->front = queue->front->next;
	}
	delete node;
	return tempNode;
}
bool IsLinkedQueueEmpty(LinkedQueue* queue)
{
	if (queue->front == NULL)
	{
		return true;
	}
	return false;
}
void ZOrderTraverse(TreeNode * root)
{
	LinkedQueue* queue = new LinkedQueue;
	EnQueue(queue,root);
	while (!IsLinkedQueueEmpty(queue))
	{
		TreeNode* tempNode = NULL;
		tempNode = DeQueue(queue);
		cout << "[" << tempNode->data.id << "," << tempNode->data.name << "]-";
		if (tempNode->left != NULL)
		{
			EnQueue(queue, tempNode->left);
		}
		if (tempNode->right != NULL)
		{
			EnQueue(queue, tempNode->right);
		}
	}
	delete queue;
}
//int main()
//{
//	BinaryTree tree;
//	tree.root = new TreeNode;
//	CreatBinaryTree_Test(tree.root);
//	cout << "根节点";
//	//CreatBinaryTree(tree.root);
//	/*PreOrderTraverse(tree.root);
//	cout << endl;*/
//	//InOrderTraverse(tree.root);
//	//cout << endl;
//	////InOrderTraverse_Re(tree.root);
//	//PostOrderTraverse(tree.root);
//	//cout << endl;
//	ZOrderTraverse(tree.root);
//	//cout << endl;
//}