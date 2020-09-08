#include <iostream>
#include <cstdio>
#include <cstdlib>
#define MAX_SIZE 10
using namespace std;
class SeqStack {
public:
	int elements[MAX_SIZE];
	int top;
	int length;
};
void InitStack(SeqStack* SeqStack)
{
	SeqStack->top = -1;
	SeqStack->length = 0;
}
bool PushStack(SeqStack* SeqStack, int element)
{
	if (SeqStack->top == MAX_SIZE - 1)
	{
		cout << "��ջ����ջʧ��" << endl;
		return false;
	}
	SeqStack->elements[++SeqStack->top] = element;
	SeqStack->length++;
	return true;
}
//ɾ��Ԫ�ز���ȡ��ɾ��Ԫ�ص�����
bool PopStack(SeqStack* SeqStack, int* element)
{
	if (SeqStack->top == -1)
	{
		cout << "��ջ,��ջʧ��" << endl;
		return false;
	}
	*element = SeqStack->elements[SeqStack->top--];
	SeqStack->length--;
	return true;
}
void ClearStack(SeqStack* SeqStack)
{
	SeqStack->top = -1;
	SeqStack->length = 0;
}
int GetTopElement(SeqStack* SeqStack)
{
	if (SeqStack->top == -1)
	{
		cout << "��ջ��Ԫ��" << endl;
		return -1;
	}
	return SeqStack->elements[SeqStack->top];
}
//int main()
//{
//	SeqStack* stack = new SeqStack;
//	int* ptr_i = new int;//�洢��ɾ��������
//	InitStack(stack);
//	for (int i = 0; i < 4; i++)
//		PushStack(stack, i);
//	PopStack(stack, ptr_i);
//	cout << "ɾ����Ԫ����" << *ptr_i << endl;
//	for (int i = 0; i < stack->length; i++)
//		cout << stack->elements[i] << endl;
//}