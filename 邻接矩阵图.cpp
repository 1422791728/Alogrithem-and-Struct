#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <queue>
#define MAX_VERTEX 100
using namespace std;
typedef enum {
	DG,//有向图
	UDG,//无向图
	DN,//有向图
	UDN,//无向图
}GraphKind;
class MatrixGraph
{
public:
	GraphKind kind;//图的类型
	string verTexs[MAX_VERTEX];//顶点集合
	int arcs[MAX_VERTEX][MAX_VERTEX];//邻接矩阵
	int verTexcount;//顶点个数
	int arcTexcount;//边的个数
};
int GetIndex(MatrixGraph* G, string& name) //判断该顶点是否存在
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











//无向图
bool CreatUDG(MatrixGraph* G)
{
	G->kind = UDG;
	cout << "请输入顶点个数" << endl;
	cin >> G->verTexcount;
	cout << "请输入边的个数" << endl;
	cin >> G->arcTexcount;
	cout << "请输入各顶点信息" << endl;
	for (int i = 0; i < G->verTexcount; i++)
	{
		cout << "第" << i + 1 << "个顶点";
		cin >> G->verTexs[i];
	}
	for (int i = 0; i < G->verTexcount; i++)
	{
		for (int j = 0; j < G->verTexcount; j++)
		{
			G->arcs[i][j] = 0;
		}
	}
	cout << "请输入顶点和邻接点，构成邻接矩阵" << endl;
	for (int i = 0; i < G->arcTexcount; i++)
	{
		string temp1;
		string temp2;
		cout << "输入顶点(弧尾)" << endl;
		cin >> temp1;
		cout << "输入邻接点(弧头)" << endl;
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










//有向网
bool CreatDN(MatrixGraph* G)
{
	G->kind = DN;
	cout << "请输入顶点个数" << endl;
	cin >> G->verTexcount;
	cout << "请输入边的个数" << endl;
	cin >> G->arcTexcount;
	cout << "请输入各顶点信息" << endl;
	for (int i = 0; i < G->verTexcount; i++)
	{
		cout << "第" << i + 1 << "个顶点";
		cin >> G->verTexs[i];
	}
	for (int i = 0; i < G->verTexcount; i++)
	{
		for (int j = 0; j < G->verTexcount; j++)
		{
			G->arcs[i][j] = INT_MAX;
		}
	}
	cout << "请输入顶点和邻接点，构成邻接矩阵" << endl;
	for (int i = 0; i < G->arcTexcount; i++)
	{
		string temp1;
		string temp2;
		cout << "输入顶点(弧尾)" << endl;
		cin >> temp1;
		cout << "输入邻接点(弧头)" << endl;
		cin >> temp2;
		int x = GetIndex(G, temp1);
		int y = GetIndex(G, temp2);
		if (x == -1 || y == -1)
		{
			return false;
		}
		cout << "请输入权值" << endl;
		cin >> G->arcs[x][y];
	}
	return true;
}




//有向图
bool CreatDG(MatrixGraph* G)
{
	G->kind = DG;
	cout << "请输入顶点个数" << endl;
	cin >> G->verTexcount;
	cout << "请输入边的个数" << endl;
	cin >> G->arcTexcount;
	cout << "请输入各顶点信息" << endl;
	for (int i = 0; i < G->verTexcount; i++)
	{
		cout << "第" << i + 1 << "个顶点";
		cin >> G->verTexs[i];
	}
	for (int i = 0; i < G->verTexcount; i++)
	{
		for (int j = 0; j < G->verTexcount; j++)
		{
			G->arcs[i][j] = 0;
		}
	}
	cout << "请输入顶点和邻接点，构成邻接矩阵" << endl;
	for (int i = 0; i < G->arcTexcount; i++)
	{
		string temp1;
		string temp2;
		cout << "输入顶点(弧尾)" << endl;
		cin >> temp1;
		cout << "输入邻接点(弧头)" << endl;
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
bool visited[MAX_VERTEX];//用数组来记录访问状态

int First_AMG(MatrixGraph* G, string& ver)//获取ver点的第一个邻接点下标
{
	int i = GetIndex(G, ver);
	//if (i == -1)return -1;
	int defaultweight = G->kind <= 1 ? 0 : INT_MAX;//看看邻接矩阵的默认值是0/∞
	for (int j = 0; j < G->verTexcount; j++)
	{
		if (G->arcs[i][j] != defaultweight)
		{
			return j;
		}
	}
	return -1;
}

int Second_AMG(MatrixGraph* G, string& ver1, string& ver2)//获取ver1顶点的ver2后的邻接点
{
	int index1 = GetIndex(G, ver1);
	int index2 = GetIndex(G, ver2);//ver1的邻接点ver2在邻接矩阵中 以ver1为行中ver2的下标
	//if (index1 == -1 || index2 == -1)return -1;
	int defaultweight = G->kind <= 1 ? 0 : INT_MAX;//看看邻接矩阵的默认值是0/∞
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
	for (int i = 0; i < G->verTexcount; i++) //初始化数组
	{
		visited[i] = 0;
	}
	for (int i = 0; i < G->verTexcount; i++)
	{
		if (!visited[i])
		{
			DFS_AMG(G, i);//防止非联通图的那种就是两个图都遍历
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
		cout << "创图失败" << endl;
		return;
	}
	else
	{
		cout << "打印邻接矩阵" << endl;
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