#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
#define BLACK 0
#define WHITE 1
#define BOARD_SIZE 15
//棋子
class ChessMan {
public:
	int x;
	int y;
	int type;
};
class StackNode
{
public:
	ChessMan data;
	StackNode* next;
};
class LinkStack
{
public:
	StackNode* top;
	int length;
};
const char* ChessBoard[BOARD_SIZE][BOARD_SIZE];
void InitChessBoard()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			ChessBoard[i][j] = "十";
		}
	}
}
void PrintChessBoard()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			cout << ChessBoard[i][j];
		}
		cout << endl;
	}
}
void InitStack(LinkStack* link)
{
	link->top = NULL;
	link->length = 0;
}
void PushChess(LinkStack* link, ChessMan& chess)
{
	StackNode* newnode = new StackNode;
	newnode->data = chess;
	newnode->next = link->top;
	link->top = newnode;
	link->length++;
}
void PopChess(LinkStack* link, ChessMan& chess)
{
	if (!link->top)
	{
		cout << "空栈" << endl;
		return;
	}
	StackNode* popnode = link->top;
	chess = link->top->data;
	link->top = link->top->next;
	delete popnode;
	link->length--;

}
//int main()
//{
//	ChessMan chess[] = {
//		{6,7,BLACK},
//		{7,6,WHITE},
//		{8,7,BLACK},
//		{7,8,WHITE}
//	};
//	LinkStack* link = new LinkStack;
//	InitStack(link);
//	InitChessBoard();
//	PrintChessBoard();
//	system("pause");
//	system("cls");
//	cout << "插入后" << endl;
//	for (int i = 0; i < 4; i++)
//	{
//		PushChess(link, chess[i]);
//		if (chess[i].type == BLACK)
//		{
//			ChessBoard[chess[i].y - 1][chess[i].x - 1] = "●";
//		}
//		else
//		{
//			ChessBoard[chess[i].y - 1][chess[i].x - 1] = "○";
//		}
//	}
//	PrintChessBoard();
//	system("pause");
//	system("cls");
//	cout << "悔棋" << endl;
//	while (link->top)
//	{
//		system("pause");
//		system("cls");
//		ChessMan tempchess;
//		PopChess(link, tempchess);
//		ChessBoard[tempchess.y - 1][tempchess.x - 1] = "十";
//		PrintChessBoard();
//	}
//}
