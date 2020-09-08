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
		cout << "满栈，入栈失败" << endl;
		return false;
	}
	SeqStack->elements[++SeqStack->top] = element;
	SeqStack->length++;
	return true;
}
//删除元素并获取被删除元素的数据
bool PopStack(SeqStack* SeqStack, int* element)
{
	if (SeqStack->top == -1)
	{
		cout << "空栈,出栈失败" << endl;
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
		cout << "空栈无元素" << endl;
		return -1;
	}
	return SeqStack->elements[SeqStack->top];
}
//int main()
//{
//	SeqStack* stack = new SeqStack;
//	int* ptr_i = new int;//存储被删除的数据
//	InitStack(stack);
//	for (int i = 0; i < 4; i++)
//		PushStack(stack, i);
//	PopStack(stack, ptr_i);
//	cout << "删除的元素是" << *ptr_i << endl;
//	for (int i = 0; i < stack->length; i++)
//		cout << stack->elements[i] << endl;
//}