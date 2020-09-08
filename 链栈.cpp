#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
class StackNode {
public:
	int id;
	StackNode* next;
};
class LinkStack {
public:
	int length;
	StackNode* top;
};
void InitLinkedStack(LinkStack* link)
{
	link->top = NULL;
	link->length = 0;
}
bool PushLinkedStack(LinkStack* link, int id)
{
	StackNode* newnode = new StackNode;
	newnode->id = id;
	newnode->next = link->top;
	link->top = newnode;
	link->length++;
	return true;
}
bool PopLinkedStack(LinkStack* link, int* id)
{
	if (!link->top)
	{
		cout << "¿ÕÕ»" << endl;
		return false;
	}
	*id = link->top->id;
	StackNode* popnode = link->top;
	link->top = link->top->next;
	delete popnode;
	link->length--;
	return true;
}
void ClearLinkedStack(LinkStack* link)
{
	while (link->top)
	{
		StackNode* popnode = link->top;
		link->top = link->top->next;
		delete popnode;
		link->length--;
	}
}
void DestroyStack(LinkStack* link)
{
	ClearLinkedStack(link);
	delete link;
	link = NULL;
}
//int main()
//{
//	LinkStack* link = new LinkStack;
//	InitLinkedStack(link);
//	PushLinkedStack(link, 1);
//	PushLinkedStack(link, 2);
//	PushLinkedStack(link, 3);
//	int* pre = new int;
//	PopLinkedStack(link, pre);
//	StackNode* templink = link->top;
//	while (templink)
//	{
//		cout << templink->id << endl;
//		templink = templink->next;
//	}
//
//}