#include <iostream>
#include<iomanip>
#include <vector>
#include <string>
using namespace std;
#define Max 255
class ElementType
{
public:
	int id;
	string name;
};
class SquenList
{
public:
	ElementType datas[Max];
	int length;
	SquenList()
	{
		length = 0;
	}
	void InsertElement(ElementType elem, int index)
	{
		if (length + 1 > Max)
		{
			cout << "Ԫ���������ܲ���" << endl;
			return;
		}
		if (index < 0 || index > length)
		{
			cout << "������˳���ṹ" << endl;
			return;
		}
		for (int i = length - 1; i >= index; i--)
		{
			datas[i + 1] = datas[i];
		}
		datas[index] = elem;
		//memcpy(&datas[index],&elem,sizeof(elem));
		this->length++;
	}
	void InitList(ElementType* elem, int length)
	{
		this->length = 0;
		if (this->length > Max)
		{
			cout << "8��Խ����" << endl;
			return;
		}
		for (int i = 0; i < length; i++)
		{
			InsertElement(elem[i], i);
		}
	}
	void Show()
	{
		for (int i = 0; i < this->length; i++)
		{
			cout << datas[i].id << endl;
		}
	}
	ElementType* DeleteElement(int index)
	{
		if (index < 0 || index > length - 1)
		{
			cout << "���±�û��Ԫ��" << endl;
			return NULL;
		}
		ElementType* ele = new ElementType();
		*ele = *FightElement(index);
		for (int i = index; i < length - 1; i++)
		{
			datas[i] = datas[i + 1];
		}
		length--;
		return ele;
	}
	ElementType* FightElement(int index)
	{
		if (index < 0 || index > length - 1)
		{
			cout << "���±�û��Ԫ��" << endl;
			return NULL;
		}
		return &datas[index];
	}
	bool Empty()
	{
		return Size() == 0 ? true : false;
	}
	int Size()
	{
		return length;
	}
	void Clear()
	{
		length = 0;
	}
};
class SquenList_test :public SquenList
{
public:
	void InsertElement(ElementType elem, int index)
	{
		if (length + 1 > Max)
		{
			cout << "Ԫ���������ܲ���" << endl;
			return;
		}
		for (int i = length - 1; i >= index; i--)
		{
			datas[i + 1] = datas[i];
		}
		datas[index] = elem;
		//memcpy(&datas[index], &elem, sizeof(elem));
		this->length++;
	}
	void InitList(ElementType* elem, int length)
	{
		this->length = 0;
		for (int i = 0; i < length; i++)
		{
			InsertElement(elem[i], i + 1);
		}
	}
	void Show()
	{
		for (int i = 1; i <= this->length; i++)
		{
			cout << datas[i].id << endl;
		}
	}
	int SearchSeqList(int key)//ƽ���
	{
		for (int i = 1; i <= length; i++)
		{
			if (datas[i].id == key)
			{
				return i;
			}
		}
		return 0;
	}
	int SearchSeqList2(int key) //VIP��˳�����
	{
		datas[0].id = key;
		int i;
		for (i = length; datas[i].id != key; i--);
		return i;
	}
	int SearchSeqList_Binary(int key)//���ַ�
	{
		int low = 1;
		int high = length;
		while (low <= high)
		{
			int mid = (low + high) / 2;
			if (key == datas[mid].id)
			{
				return mid;
			}
			else if (key < datas[mid].id)
			{
				high = mid - 1;
			}
			else
			{
				low = mid + 1;
			}
		}
		return 0;
	}
	int SearchSeqList_BinaryRecursion(int key, int low, int high)//�ݹ����
	{
		if (low > high) return 0;
		int mid = (high + low) / 2;
		if (datas[mid].id == key)
		{
			return mid;
		}
		else if (key < datas[mid].id)
		{
			return SearchSeqList_BinaryRecursion(key, low, mid - 1);
		}
		else
		{
			return SearchSeqList_BinaryRecursion(key, mid + 1, high);
		}
	}
};
//int main()
//{
//	ElementType elem[] = {
//		{1,"̫���Ͼ�"},
//		{2,"̫���Ͼ�"},
//		{3,"̫���Ͼ�"},
//		{4,"����ũҩ"}
//	};
//	SquenList li;
//	SquenList_test list;
//	list.InitList(elem, 4);
//	cout << list.SearchSeqList2(0) << endl;
//}

//��ʱ��֪��Ϊʲôֻ�������Ŀ����
//���԰Ѵ��븴�Ƶ������Ŀ����Ͳ������ˣ���ʱ��֪��Ϊʲô



	
