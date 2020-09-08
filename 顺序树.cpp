#include <iostream>
#include <cmath>
#define MAX_SIZE 255
using namespace std;
class SeqTree {
public:
	char Data[MAX_SIZE];
	int last;
	SeqTree()
	{
		for (int i = 0; i < MAX_SIZE; i++)
		{
			Data[i] = '\0';
			last = 0;
		}
	}
};
void CreatTree(SeqTree& tree, int index)
{
	char ch;
	ch = getchar();
	getchar();
	fflush(stdin);
	if (ch == '^')
	{
		tree.Data[index] = '\0';
		return;
	}
	tree.Data[index] = ch;
	cout << ch << "�����ӽ��Ϊ" << endl;
	CreatTree(tree, 2 * index + 1);
	cout << ch << "���Һ��ӽ��Ϊ" << endl;
	CreatTree(tree, 2 * (index + 1));
}
int GetSeqTreeLength(SeqTree tree)//���Ⱦ��ǰ�����ȫ��������������м��пս��ҲҪ����
{
	int len;
	for (len = MAX_SIZE; len >= 1; len--)
	{
		if (tree.Data[len - 1] != '\0')
		{
			break;
		}
	}
	return len;
}
char GetSeqTreeRoot(SeqTree tree)
{
	return tree.Data[0];
}
int GetSeqTreeDepth(SeqTree tree)
{
	int len = GetSeqTreeLength(tree);
	int depth = 0;
	while ((int)pow(2, depth) - 1 < len)
	{
		depth++;
	}
	return depth;
}
//int main()
//{
//	SeqTree tree;
//	CreatTree(tree,0);
//	for (int i = 0; i < 16; i++)
//	{
//		cout << (int)tree.Data[i] << endl;
//	}
//	cout << GetSeqTreeLength(tree) << endl;
//	cout << GetSeqTreeDepth(tree)<<endl;
//}