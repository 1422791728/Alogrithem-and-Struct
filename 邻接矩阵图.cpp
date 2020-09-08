#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <queue>
#define MAX_VERTEX 100
using namespace std;
typedef enum {
	DG,//����ͼ
	UDG,//����ͼ
	DN,//����ͼ
	UDN,//����ͼ
}GraphKind;
class MatrixGraph
{
public:
	GraphKind kind;//ͼ������
	string verTexs[MAX_VERTEX];//���㼯��
	int arcs[MAX_VERTEX][MAX_VERTEX];//�ڽӾ���
	int verTexcount;//�������
	int arcTexcount;//�ߵĸ���
};
int GetIndex(MatrixGraph* G, string& name) //�жϸö����Ƿ����
{
	int index = 0;
	for (; index < G->verTexcount; index++)
	{
		if (name.compare(G->verTexs[index]) == 0)
		{
			break;
		}
	}
	return index == G->verTexcount ? -1 : index;
}











//����ͼ
bool CreatUDG(MatrixGraph* G)
{
	G->kind = UDG;
	cout << "�����붥�����" << endl;
	cin >> G->verTexcount;
	cout << "������ߵĸ���" << endl;
	cin >> G->arcTexcount;
	cout << "�������������Ϣ" << endl;
	for (int i = 0; i < G->verTexcount; i++)
	{
		cout << "��" << i + 1 << "������";
		cin >> G->verTexs[i];
	}
	for (int i = 0; i < G->verTexcount; i++)
	{
		for (int j = 0; j < G->verTexcount; j++)
		{
			G->arcs[i][j] = 0;
		}
	}
	cout << "�����붥����ڽӵ㣬�����ڽӾ���" << endl;
	for (int i = 0; i < G->arcTexcount; i++)
	{
		string temp1;
		string temp2;
		cout << "���붥��(��β)" << endl;
		cin >> temp1;
		cout << "�����ڽӵ�(��ͷ)" << endl;
		cin >> temp2;
		int x = GetIndex(G, temp1);
		int y = GetIndex(G, temp2);
		if (x == -1 || y == -1)
		{
			return false;
		}
		G->arcs[x][y] = 1;
		G->arcs[y][x] = 1;
	}
	return true;
}










//������
bool CreatDN(MatrixGraph* G)
{
	G->kind = DN;
	cout << "�����붥�����" << endl;
	cin >> G->verTexcount;
	cout << "������ߵĸ���" << endl;
	cin >> G->arcTexcount;
	cout << "�������������Ϣ" << endl;
	for (int i = 0; i < G->verTexcount; i++)
	{
		cout << "��" << i + 1 << "������";
		cin >> G->verTexs[i];
	}
	for (int i = 0; i < G->verTexcount; i++)
	{
		for (int j = 0; j < G->verTexcount; j++)
		{
			G->arcs[i][j] = INT_MAX;
		}
	}
	cout << "�����붥����ڽӵ㣬�����ڽӾ���" << endl;
	for (int i = 0; i < G->arcTexcount; i++)
	{
		string temp1;
		string temp2;
		cout << "���붥��(��β)" << endl;
		cin >> temp1;
		cout << "�����ڽӵ�(��ͷ)" << endl;
		cin >> temp2;
		int x = GetIndex(G, temp1);
		int y = GetIndex(G, temp2);
		if (x == -1 || y == -1)
		{
			return false;
		}
		cout << "������Ȩֵ" << endl;
		cin >> G->arcs[x][y];
	}
	return true;
}




//����ͼ
bool CreatDG(MatrixGraph* G)
{
	G->kind = DG;
	cout << "�����붥�����" << endl;
	cin >> G->verTexcount;
	cout << "������ߵĸ���" << endl;
	cin >> G->arcTexcount;
	cout << "�������������Ϣ" << endl;
	for (int i = 0; i < G->verTexcount; i++)
	{
		cout << "��" << i + 1 << "������";
		cin >> G->verTexs[i];
	}
	for (int i = 0; i < G->verTexcount; i++)
	{
		for (int j = 0; j < G->verTexcount; j++)
		{
			G->arcs[i][j] = 0;
		}
	}
	cout << "�����붥����ڽӵ㣬�����ڽӾ���" << endl;
	for (int i = 0; i < G->arcTexcount; i++)
	{
		string temp1;
		string temp2;
		cout << "���붥��(��β)" << endl;
		cin >> temp1;
		cout << "�����ڽӵ�(��ͷ)" << endl;
		cin >> temp2;
		int x = GetIndex(G, temp1);
		int y = GetIndex(G, temp2);
		if (x == -1 || y == -1)
		{
			return false;
		}
		G->arcs[x][y] = 1;
	}
	return true;
}



// D F S
bool visited[MAX_VERTEX];//����������¼����״̬

int First_AMG(MatrixGraph* G, string& ver)//��ȡver��ĵ�һ���ڽӵ��±�
{
	int i = GetIndex(G, ver);
	//if (i == -1)return -1;
	int defaultweight = G->kind <= 1 ? 0 : INT_MAX;//�����ڽӾ����Ĭ��ֵ��0/��
	for (int j = 0; j < G->verTexcount; j++)
	{
		if (G->arcs[i][j] != defaultweight)
		{
			return j;
		}
	}
	return -1;
}

int Second_AMG(MatrixGraph* G, string& ver1, string& ver2)//��ȡver1�����ver2����ڽӵ�
{
	int index1 = GetIndex(G, ver1);
	int index2 = GetIndex(G, ver2);//ver1���ڽӵ�ver2���ڽӾ����� ��ver1Ϊ����ver2���±�
	//if (index1 == -1 || index2 == -1)return -1;
	int defaultweight = G->kind <= 1 ? 0 : INT_MAX;//�����ڽӾ����Ĭ��ֵ��0/��
	for (int j = index2 + 1; j < G->verTexcount; j++)
	{
		if (G->arcs[index1][j] != defaultweight)
		{
			return j;
		}
	}
	return -1;
}
void DFS_AMG(MatrixGraph* G, int index)
{
	cout << G->verTexs[index] << "->";
	visited[index] = 1;
	for (int i = First_AMG(G, G->verTexs[index]); i != -1; i = Second_AMG(G, G->verTexs[index], G->verTexs[i]))
	{
		if (!visited[i])
		{
			DFS_AMG(G, i);
		}
	}
}

void DFS_Matrixgarph(MatrixGraph* G)
{
	for (int i = 0; i < G->verTexcount; i++) //��ʼ������
	{
		visited[i] = 0;
	}
	for (int i = 0; i < G->verTexcount; i++)
	{
		if (!visited[i])
		{
			DFS_AMG(G, i);//��ֹ����ͨͼ�����־�������ͼ������
		}
	}
}




// BFS
void BFS_AMG(MatrixGraph* G, int index)
{
	queue<string> que;
	visited[index] = 1;
	que.push(G->verTexs[index]);
	while (!que.empty())
	{
		string temp = que.front();
		cout << temp << "->";
		que.pop();
		for (int i = First_AMG(G, temp); i != -1; i = Second_AMG(G, temp, G->verTexs[i]))
		{
			if (!visited[i])
			{
				visited[i] = 1;
				que.push(G->verTexs[i]);
			}
		}
	}

}

void BFS_MatrixGraph(MatrixGraph* G)
{
	for (int i = 0; i < G->verTexcount; i++)
	{
		visited[i] = 0;
	}
	for (int i = 0; i < G->verTexcount; i++)
	{
		if (!visited[i])
		{
			BFS_AMG(G, i);
		}
	}
}

void ShowMatrixgraph()
{
	MatrixGraph G;
	bool status = CreatUDG(&G);
	//bool status = CreatDG(&G);
	//bool status = CreatDN(&G);
	if (status == false)
	{
		cout << "��ͼʧ��" << endl;
		return;
	}
	else
	{
		cout << "��ӡ�ڽӾ���" << endl;
		for (int i = 0; i < G.verTexcount; i++)
		{
			cout << "\t" << G.verTexs[i];
		}
		cout << endl;
		for (int i = 0; i < G.verTexcount; i++)
		{
			cout << G.verTexs[i];
			for (int j = 0; j < G.verTexcount; j++)
			{
				if (G.arcs[i][j] == 0)
				{
					cout << "\t0";
				}
				else
				{
					cout << "\t" << G.arcs[i][j];
				}
			}
			cout << endl;
		}
	}
	//DFS_Matrixgarph(&G);
	BFS_MatrixGraph(&G);
}

//
//int main()
//{
//	ShowMatrixgraph();
//}