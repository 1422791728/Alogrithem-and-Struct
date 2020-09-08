#include <iostream>
#include <cstdio>
#include <cstdlib>
#define MAX_SIZE 10
using namespace std;
typedef struct
{
public:
	int id;
	int next;//游标
}Staticlink[MAX_SIZE];
void Init(Staticlink stalist)
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		stalist[i].next = i + 1;
		stalist[i].id = 0;
	}
	stalist[MAX_SIZE - 1].next = 0;
	stalist[MAX_SIZE - 2].next = 0;
}
int Getlength(Staticlink stalink)
{
	int count = 0;
	int cursor = stalink[0].next;
	while (cursor != 0)
	{
		cursor = stalink[cursor].next;
		count++;
	}
	return count;
}
void Show(Staticlink stalist)
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		cout << stalist[i].id << stalist[i].next << endl;
	}
}
int  Malloc(Staticlink stalist)
{
	int cursor = stalist[0].next;//记录当前备用链表的第一个结点
	if (cursor)
	{
		stalist[0].next = stalist[cursor].next;
	}
	return cursor;

}
void Free(Staticlink stalist, int index)
{
	//把该结点放回到备用链表中的第一个结点 把他链接到现在备用第一个结点
	stalist[index].next = stalist[0].next;
	//把第一个元素指向其刚加进去的第一个结点
	stalist[0].next = index;
}
void Delete(Staticlink stalist, int pos)
{
	int cursor = MAX_SIZE - 1;//前缀元素的下标
	for (int i = 1; i < pos; i++)
	{
		cursor = stalist[cursor].next;
	}
	int deleteIndex = stalist[cursor].next;
	stalist[cursor].next = stalist[deleteIndex].next;
	Free(stalist, deleteIndex);
}
void Insert(Staticlink stalist, int pos, int id)
{
	if (pos < 1 || pos > Getlength(stalist) + 1)
	{
		return;
	}
	int cursor = MAX_SIZE - 1;//记录newindex前缀元素的下标
	int newindex = Malloc(stalist);//把数据插入到哪个空节点找到
	if (newindex)
	{
		stalist[newindex].id = id;

		for (int i = 1; i < pos; i++)
		{
			cursor = stalist[cursor].next;//找到newindex的前缀元素
		}
		stalist[newindex].next = stalist[cursor].next;
		stalist[cursor].next = newindex;
	}
}

//int main()
//{
//	Staticlink sta;
//	Init(sta);
//	Insert(sta, 1, 1);
//	Insert(sta, 2, 2);
//	Insert(sta, 2, 3);
//	Show(sta);
//	cout << "——————————————————————————————————-" << endl;
//	Delete(sta, 2);
//	Show(sta);
//}