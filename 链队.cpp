#include <iostream>
using namespace std;
class QueueNode
{
public:
	int id;
	QueueNode* next;
};
class LinkQueue
{
public:
	QueueNode* pfront;//头指针
	QueueNode* ptail;//尾指针
	int length;
	LinkQueue()
	{
		pfront = NULL;
		ptail = NULL;
		length = 0;
	}
};
bool PushLinkedQueue(LinkQueue* queue, int id)
{
	QueueNode* tempNode = new QueueNode;
	if (tempNode == NULL)
	{
		exit(-1);//内存溢出
	}
	tempNode->id = id;
	tempNode->next = NULL;
	if (queue->pfront == NULL)
	{
		queue->pfront = queue->ptail = tempNode;
	}
	else
	{
		queue->ptail->next = tempNode;
		queue->ptail = queue->ptail->next;
	}
	queue->length++;
	return true;
}
bool PopLinkedQueue(LinkQueue* queue, int* id)
{
	if (queue->pfront == NULL)
	{
		return false;
	}
	QueueNode* tempnode = NULL;
	tempnode = queue->pfront;
	if (queue->pfront == queue->ptail)
	{
		queue->pfront = queue->ptail = NULL;
	}
	else
	{
		queue->pfront = queue->pfront->next;
	}
	*id = tempnode->id;
	queue->length--;
	delete tempnode;
	return true;
}
int GetHead(LinkQueue* queue)
{
	return queue->pfront->id;
}
void Show(LinkQueue* queue)
{
	QueueNode* tempNode = queue->pfront;
	while (tempNode != queue->ptail)
	{
		cout << tempNode->id << " ";
		tempNode = tempNode->next;
	}
	cout << endl;
}
//int main()
//{
//	LinkQueue* queue = new LinkQueue;
//	for (int i = 0; i < 5; i++)
//		PushLinkedQueue(queue, i);
//	Show(queue);
//	int* id = new int;
//	PopLinkedQueue(queue, id);
//	Show(queue);
//	cout << *id << endl;
//}