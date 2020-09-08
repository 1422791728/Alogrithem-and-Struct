#include <iostream>
using namespace std;
//并查集顺序表实现
class Gather
{
public:
	int pre[1000];//所有点的上司
	int UnionSearch(int root)//查找该结点的初根节点
	{
		int son;
		int temp;
		son = root;
		while (root != pre[root])//查找掌门的
		{
			root = pre[root];
		}
		//路径压缩提高效
		//把该一条路的深度压缩到2层
		while (root != son)
		{
			temp = pre[son];
			pre[son] = root;
			son = temp;
		}
		return root;
	}
	void Join(int root1, int root2)//并集
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