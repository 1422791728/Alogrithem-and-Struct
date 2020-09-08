#include <iostream>
#include <string>
#include <queue>
#define MAX_VERTEX 100
using namespace std;
typedef enum
{
	DG,//����ͼ
	UDG,//����ͼ
	DN,//����ͼ
	UDN,//����ͼ
}GraphKind;
class ArcNode
{
public:
	int adjvex;//�����ڶ��������е��±�
	ArcNode* nextarc;
	int weight;//Ȩ��
};
class VexNode
{
public:
	ArcNode* firstArc;//����
	ArcNode* tailArc;//���
	string name;
};
class AdjListGraph
{
public:
	VexNode vexs[MAX_VERTEX];
	int ArcCount;//����
	int VexCount;//������
	GraphKind kind;
};
int GetIndex(AdjListGraph* G, string& name)
{
	int index = -1;
	for (int i = 0; i < G->VexCount; i++)
	{
		if (name.compare(G->vexs[i].name) == 0)
		{
			index = i;
			break;
		}
	}
	return index;
}



//����ͼ
bool CreatUDG(AdjListGraph* G)
{
	G->kind = UDG;
	cout << "�����붥�����" << endl;
	cin >> G->VexCount;
	cout << "������߸���" << endl;
	cin >> G->ArcCount;
	for (int i = 0; i < G->VexCount; i++)
	{
		cout << "�����붥����Ϣ" << endl;
		cin >> G->vexs[i].name;
		G->vexs[i].firstArc = NULL;
	}
	cout << "�����붥����Ϣ���ڽӵ���Ϣ�����ڽӱ�" << endl;
	for (int i = 0; i < G->ArcCount; i++)
	{
		string temp1;
		string temp2;
		cout << "�����붥����Ϣ" << endl;
		cin >> temp1;
		cout << "�������ڽӵ���Ϣ" << endl;
		cin >> temp2;
		int x = GetIndex(G, temp1);
		int y = GetIndex(G, temp2);
		if (x == -1 || y == -1) return false;
		ArcNode* arcnode = new ArcNode;
		arcnode->adjvex = y;
		arcnode->nextarc = G->vexs[x].firstArc;
		arcnode->weight = 1;
		G->vexs[x].firstArc = arcnode;
		arcnode = new ArcNode;
		arcnode->adjvex = x;
		arcnode->nextarc = G->vexs[y].firstArc;
		arcnode->weight = 1;
		G->vexs[y].firstArc = arcnode;
	}
	return true;
}




//����ͼ
bool CreatDG(AdjListGraph* G)
{
	G->kind = DG;
	cout << "�����붥�����" << endl;
	cin >> G->VexCount;
	cout << "������߸���" << endl;
	cin >> G->ArcCount;
	for (int i = 0; i < G->VexCount; i++)
	{
		cout << "�����붥����Ϣ" << endl;
		cin >> G->vexs[i].name;
		G->vexs[i].firstArc = NULL;
		G->vexs[i].tailArc = NULL;
	}
	cout << "�����붥����Ϣ���ڽӵ���Ϣ�����ڽӱ�" << endl;
	for (int i = 0; i < G->ArcCount; i++)
	{
		string temp1;
		string temp2;
		cout << "�����붥����Ϣ" << endl;
		cin >> temp1;
		cout << "�������ڽӵ���Ϣ" << endl;
		cin >> temp2;
		int x = GetIndex(G, temp1);
		int y = GetIndex(G, temp2);
		if (x == -1 || y == -1) return false;
		//�ڽӱ�
		ArcNode* arcnode = new ArcNode;
		arcnode->adjvex = y;
		arcnode->nextarc = G->vexs[x].firstArc;
		arcnode->weight = 1;
		G->vexs[x].firstArc = arcnode;
		arcnode = new ArcNode;
		arcnode->adjvex = x;
		arcnode->nextarc = G->vexs[y].tailArc;
		arcnode->weight = 1;
		G->vexs[y].tailArc = arcnode;
	}
	return true;
}








//������
bool CreatDN(AdjListGraph* G)
{
	G->kind = DN;
	cout << "�����붥�����" << endl;
	cin >> G->VexCount;
	cout << "������߸���" << endl;
	cin >> G->ArcCount;
	for (int i = 0; i < G->VexCount; i++)
	{
		cout << "�����붥����Ϣ" << endl;
		cin >> G->vexs[i].name;
		G->vexs[i].firstArc = NULL;
		G->vexs[i].tailArc = NULL;
	}
	cout << "�����붥����Ϣ���ڽӵ���Ϣ�����ڽӱ�" << endl;
	for (int i = 0; i < G->ArcCount; i++)
	{
		string temp1;
		string temp2;
		cout << "�����붥����Ϣ" << endl;
		cin >> temp1;
		cout << "�������ڽӵ���Ϣ" << endl;
		cin >> temp2;
		int value;
		cout << "������Ȩֵ" << endl;
		cin >> value;
		int x = GetIndex(G, temp1);
		int y = GetIndex(G, temp2);
		if (x == -1 || y == -1) return false;
		//�ڽӱ�
		ArcNode* arcnode = new ArcNode;
		arcnode->adjvex = y;
		arcnode->nextarc = G->vexs[x].firstArc;
		arcnode->weight = value;
		G->vexs[x].firstArc = arcnode;
		arcnode = new ArcNode;
		arcnode->adjvex = x;
		arcnode->nextarc = G->vexs[y].tailArc;
		arcnode->weight = value;
		G->vexs[y].tailArc = arcnode;
	}
	return true;
}






// DFS
int visited[MAX_VERTEX];
void DFS_ALG(AdjListGraph* G, int index)
{
	cout << G->vexs[index].name << "->";
	visited[index] = 1;
	ArcNode* arcnode = G->vexs[index].firstArc;
	while (arcnode)
	{
		if (!visited[arcnode->adjvex])
		{
			DFS_ALG(G, arcnode->adjvex);
		}
		arcnode = arcnode->nextarc;
	}
}
void DFS_AdjListGraph(AdjListGraph* G)
{
	for (int i = 0; i < G->VexCount; i++)
	{
		visited[i] = 0;
	}
	for (int i = 0; i < G->VexCount; i++)
	{
		if (!visited[i])
		{
			DFS_ALG(G, i);//��ֹ����ͨͼ�����־�������ͼ������
		}
	}
}


//BFS
void BFS_ALG(AdjListGraph* G, int index)
{
	queue<VexNode> que;
	visited[index] = 1;
	que.push(G->vexs[index]);
	while (!que.empty())
	{
		VexNode vex = que.front();
		cout << vex.name << "->";
		que.pop();
		int index_vex = GetIndex(G, vex.name);
		ArcNode* arcnode = G->vexs[index_vex].firstArc;
		if (index_vex == -1)return;
		while (arcnode)
		{
			if (!visited[arcnode->adjvex])
			{
				visited[arcnode->adjvex] = 1;
				que.push(G->vexs[arcnode->adjvex]);
			}
			arcnode = arcnode->nextarc;
		}
	}
}
void BFS_AdjListGraph(AdjListGraph* G)
{
	for (int i = 0; i < G->VexCount; i++)
	{
		visited[i] = 0;
	}
	for (int i = 0; i < G->VexCount; i++)
	{
		if (!visited[i])
		{
			BFS_ALG(G, i);
		}
	}
}
void ShowGraph()
{
	AdjListGraph G;
	//����ͼ
	int status = CreatUDG(&G);
	for (int i = 0; i < G.VexCount; i++)
	{
		VexNode vnode = G.vexs[i];
		cout << "����" << vnode.name;
		ArcNode * arcnode = vnode.firstArc;
		while (arcnode)
		{
			cout << "->" << G.vexs[arcnode->adjvex].name;
			arcnode = arcnode->nextarc;
		}
		cout << endl;
	}
	//����ͼ
	/*int status = CreatDG(&G);
	cout << "�ڽӱ�" << endl;
	for (int i = 0; i < G.VexCount; i++)
	{
		VexNode vnode = G.vexs[i];
		cout << "����" << vnode.name;
		ArcNode* arcnode = vnode.firstArc;
		while (arcnode)
		{
			cout << "->" << G.vexs[arcnode->adjvex].name;
			arcnode = arcnode->nextarc;
		}
		cout << endl;
	}
	cout << "���ڽӱ�" << endl;
	for (int i = 0; i < G.VexCount; i++)
	{
		VexNode vnode = G.vexs[i];
		cout << "����" << vnode.name;
		ArcNode* arcnode = vnode.tailArc;
		while (arcnode)
		{
			cout << "-<" << G.vexs[arcnode->adjvex].name;
			arcnode = arcnode->nextarc;
		}
		cout << endl;
	}*/
	//������
	/*int status = CreatDN(&G);
	cout << "�ڽӱ�" << endl;
	for (int i = 0; i < G.VexCount; i++)
	{
		VexNode vnode = G.vexs[i];
		cout << "����" << vnode.name;
		ArcNode* arcnode = vnode.firstArc;
		while (arcnode)
		{
			cout << "->" << "(" << arcnode->weight << ")" << G.vexs[arcnode->adjvex].name;
			arcnode = arcnode->nextarc;
		}
		cout << endl;
	}
	cout << "���ڽӱ�" << endl;
	for (int i = 0; i < G.VexCount; i++)
	{
		VexNode vnode = G.vexs[i];
		cout << "����" << vnode.name;
		ArcNode* arcnode = vnode.tailArc;
		while (arcnode)
		{
			cout << "-<" << "(" << arcnode->weight << ")" << G.vexs[arcnode->adjvex].name;
			arcnode = arcnode->nextarc;
		}
		cout << endl;
	}*/
	//DFS_AdjListGraph(&G);
	BFS_AdjListGraph(&G);
}
//int main()
//{
//	ShowGraph();
//}