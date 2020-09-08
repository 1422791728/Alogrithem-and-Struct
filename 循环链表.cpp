#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
class CircularNode
{
public:
	int id;
	CircularNode* next;
};
class CircularList
{
public:
	CircularNode* next;
	int length;
};
void Insert(CircularList* clList, int pos, int id)
{
	CircularNode* node = new CircularNode;
	node->id = id;
	node->next = NULL;
	if (pos == 1)
	{
		node->next = clList->next;
		if (clList->length == 0)
		{
			node->next = node;
		}
		else
		{
			CircularNode* lastnode = clList->next;
			for (int i = 1; i < clList->length; i++)
			{
				lastnode = lastnode->next;
			}
			lastnode->next = node;
		}
		clList->next = node;
		clList->length++;
		return;
	}
	if (pos > clList->length + 1)
	{
		cout << "插入失败位置有问题" << endl;
		return;
	}
	CircularNode* curr = clList->next;
	for (int i = 1; (curr != NULL) && i < pos - 1; i++)
	{
		curr = curr->next;
	}
	node->next = curr->next;
	curr->next = node;
	clList->length++;
	/*if (pos == clList->length)
	{
		node->next = clList->next;
	}*/
}
CircularNode* GetNode(CircularList* clist, int id)
{
	CircularNode* node = clist->next;
	if (node)
	{
		do {
			if (node->id == id)
			{
				return node;
			}
			node = node->next;
		} while (node != clist->next);
	}
	return NULL;
}
void Show(CircularList* clist, CircularNode* node)
{
	CircularNode* curr = node;
	if (node == NULL)
	{
		cout << "链表为空" << endl;
		return;
	}
	do {
		cout << curr->id << endl;
		curr = curr->next;
	} while (curr != node);
}
int Delete(CircularList* clist, int pos)
{
	CircularNode* node = clist->next;
	int num = -999;
	if (pos == 1)
	{
		if (node != NULL)
		{
			num = node->id;
			CircularNode* lastnode = clist->next;
			for (int i = 1; i < clist->length; i++)
			{
				lastnode = lastnode->next;
			}
			clist->next = node->next;
			lastnode->next = clist->next;
			delete node;
			clist->length--;
			return num;
		}
	}
	CircularNode* prenode = clist->next;
	for (int i = 1; i < pos; i++)
	{
		prenode = node;
		node = node->next;
	}
	if (node != NULL)
	{
		num = node->id;
		prenode->next = node->next;
		delete node;
		clist->length--;
	}
	return num;

}
void InitCircularList(CircularList* clist, int length, int* num)
{
	for (int i = 0; i < length; i++)
	{
		Insert(clist, i + 1, num[i]);
	}
}
void Show(CircularList* clist)
{
	CircularNode* node = clist->next;
	for (int i = 0; i < clist->length; i++)
	{
		cout << node->id << endl;
		node = node->next;
	}
}
//int main()
//{
//	CircularList clist;
//	clist.length = 0;
//	clist.next = NULL;
//	int num[] = { 1,3,4,5,6 };
//	InitCircularList(&clist, 5, num);
//	//Delete(&clist, 4);
//	//cout << Delete(&clist,4)<<endl;
//	//Show(&clist);
//	Insert(&clist,1,10);
//	//CircularNode* node = GetNode(&clist, 3);
//	Show(&clist, GetNode(&clist, 3));
//	//Show(&clist);
//}