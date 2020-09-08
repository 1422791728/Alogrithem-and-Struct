#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
class DoublyNode {
public:
	int id;
	DoublyNode* next;
	DoublyNode* prev;
};
class DoublyLink {
public:
	int length;
	DoublyNode* next;
};
void Insert(DoublyLink* dlink, int id, int pos)
{
	DoublyNode* node = new DoublyNode;
	node->id = id;
	node->next = NULL;
	node->prev = NULL;
	if (pos == 1)
	{
		node->next = dlink->next;
		dlink->next = node;
		if (node->next != NULL)
		{
			node->next->prev = node;
		}
		dlink->length++;
		return;
	}
	DoublyNode* currNode = dlink->next;
	for (int i = 1; currNode && i < pos - 1; i++)
	{
		currNode = currNode->next;
	}
	if (currNode)
	{
		node->next = currNode->next;
		currNode->next = node;
		node->prev = currNode;
		if (node->next)
		{
			node->next->prev = node;
		}
		dlink->length++;
		return;
	}

}
int Delete(DoublyLink* dlink, int pos)
{
	DoublyNode* node = dlink->next;
	int num = -999;
	if (pos == 1 && node)
	{
		num = node->id;
		dlink->next = node->next;

		if (node->next)
		{
			node->next->prev = NULL;
		}
		delete node;
		dlink->length--;
		return num;
	}
	for (int i = 1; i < pos; i++)
	{
		node = node->next;
	}
	if (node)
	{
		num = node->id;
		node->prev->next = node->next;
		if (node->next)
		{
			node->next->prev = node->prev;
		}
		delete node;
		dlink->length--;
		return num;
	}
}
void Show(DoublyLink* dlink)
{
	DoublyNode* node = dlink->next;
	for (int i = 0; i < dlink->length; i++)
	{
		cout << node->id << endl;
		node = node->next;
	}
}
//int main()
//{
//	DoublyLink dlink;
//	int id = 10;
//	dlink.next = NULL;
//	dlink.length = 0;
//	Insert(&dlink, 10, 1);
//	Insert(&dlink, 9, 2);
//	Show(&dlink);
//	Delete(&dlink, 2);
//	Show(&dlink);
//}
