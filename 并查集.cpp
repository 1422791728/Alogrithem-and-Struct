#include <iostream>
using namespace std;
//���鼯˳���ʵ��
class Gather
{
public:
	int pre[1000];//���е����˾
	int UnionSearch(int root)//���Ҹý��ĳ����ڵ�
	{
		int son;
		int temp;
		son = root;
		while (root != pre[root])//�������ŵ�
		{
			root = pre[root];
		}
		//·��ѹ�����Ч
		//�Ѹ�һ��·�����ѹ����2��
		while (root != son)
		{
			temp = pre[son];
			pre[son] = root;
			son = temp;
		}
		return root;
	}
	void Join(int root1, int root2)//����
	{
		int x = UnionSearch(root1);
		int y = UnionSearch(root2);
		if (x != y)
		{
			pre[x] = y;
		}
	}
	Gather(int num)
	{
		for (int i = 0; i < num; i++)
		{
			pre[i] = i;
		}
	}
};


int main()
{
	int num;
	cin >> num;
	Gather un(num);
	un.Join(2, 3);
	cout << un.UnionSearch(2) << "       " << un.UnionSearch(3);
	return 0;
}