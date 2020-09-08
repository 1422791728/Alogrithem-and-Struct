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
	return seq->front == seq->rear;//Ϊ�շ���1
}
bool IsSeqQueueFull(SeqQueue* seq)
{
	return (seq->rear + 1) % MAX_SIZE == seq->front;//���˷���1
}
bool OfferSeqQueue(SeqQueue* seq, int data)
{
	if (IsSeqQueueFull(seq))
	{
		cout << "�Բ���ö�������,���ʧ��" << endl;
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
		cout << "����Ϊ�ճ���ʧ��" << endl;
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
//	int& ptr_i = a;//�洢��ɾ��������
//	InitSeqQueue(seq);
//	for (int i = 0; i < 4; i++)
//		OfferSeqQueue(seq, i);
//	for (int i = seq->front; i < seq->front + seq->length; i++)
//		cout << seq->data[i] << endl;
//	PollSeqQueue(seq, ptr_i);
//	cout << "��ɾ����Ԫ����" << endl;
//	cout << ptr_i << endl;
//	cout << endl;
//	cout << endl;
//	for (int i = seq->front; i < seq->front + seq->length; i++)
//		cout << seq->data[i] << endl;
//	return 0;
//}