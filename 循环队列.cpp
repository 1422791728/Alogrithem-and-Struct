#include <iostream>
#include <cstdio>
#include <cstdlib>
#define MAX_SIZE 10
using namespace std;
class SeqQueue {
public:
	int data[MAX_SIZE];
	int front;
	int rear;
	int length;
};
void InitSeqQueue(SeqQueue* seq)
{
	if (seq == NULL)
	{
		seq = new SeqQueue;
	}
	seq->front = 0;
	seq->rear = 0;
	seq->length = 0;
}
bool IsSeqQueueEmpty(SeqQueue* seq)
{
	return seq->front == seq->rear;//为空返回1
}
bool IsSeqQueueFull(SeqQueue* seq)
{
	return (seq->rear + 1) % MAX_SIZE == seq->front;//满了返回1
}
bool OfferSeqQueue(SeqQueue* seq, int data)
{
	if (IsSeqQueueFull(seq))
	{
		cout << "对不起该队列已满,入队失败" << endl;
		return false;
	}
	seq->data[seq->rear] = data;
	seq->rear = (seq->rear + 1) % MAX_SIZE;
	seq->length++;
	return true;
}
bool PollSeqQueue(SeqQueue* seq, int& id)
{
	if (IsSeqQueueEmpty(seq))
	{
		cout << "队列为空出队失败" << endl;
		return false;
	}
	id = seq->data[seq->front];
	seq->front = (seq->front + 1) % MAX_SIZE;
	seq->length--;
	return true;
}
//int main()
//{
//	SeqQueue* seq = new SeqQueue;
//	int a = 0;
//	int& ptr_i = a;//存储被删除的数据
//	InitSeqQueue(seq);
//	for (int i = 0; i < 4; i++)
//		OfferSeqQueue(seq, i);
//	for (int i = seq->front; i < seq->front + seq->length; i++)
//		cout << seq->data[i] << endl;
//	PollSeqQueue(seq, ptr_i);
//	cout << "被删除的元素是" << endl;
//	cout << ptr_i << endl;
//	cout << endl;
//	cout << endl;
//	for (int i = seq->front; i < seq->front + seq->length; i++)
//		cout << seq->data[i] << endl;
//	return 0;
//}