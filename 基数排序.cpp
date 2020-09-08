#include <iostream>
#include <string>
#define MAX_SIZE 128
using namespace std;
//第二个为字符串中一个[]的最长的长度  length是string数组的长度
void BaseSort(string* s_array, int maxlength, int length)
{
	string* sortarray = new string[length];//先创立存储排列后的数组
	for (int k = maxlength - 1; k >= 0; k--)
	{
		int* count = new int[MAX_SIZE];//创立箱子
		for (int i = 0; i < MAX_SIZE; i++)
		{
			count[i] = 0;
		}
		for (int i = 0; i < length; i++)
		{
			int index = int(s_array[i][k]);//获取一个串中的最后一个元素
			count[index]++;//然后该箱子里的数量++；
		}
		for (int j = 1; j < MAX_SIZE; j++)
		{
			count[j] = count[j] + count[j - 1];//算一下该箱子前还有多少个元素包括该箱子的	为了下面赋值用
		}
		for (int i = length - 1; i >= 0; i--)//为了稳定排序从最后开始遍历
		{
			int index = int(s_array[i][k]);//获取最后一个元素
			int sortindex = count[index] - 1;//判断要把这个字符串插入在排列后的数组的那个位置
			sortarray[sortindex] = s_array[i];//然后把该元素的赋值到那里
			count[index]--;//还剩余元素的个数
		}

		for (int i = 0; i < 7; i++)
		{
			s_array[i] = sortarray[i];
		}
		for (int i = 0; i < 7; i++)
		{
			cout << sortarray[i] << endl;
		}
		system("pause");
	}
}
	
//int main()
//{
//
//	//string name[] = { "bda","cfd","qwe","yui","abc","rrr","uee","bdb" };
//
//	string name[]={"qd","abc","qwe","hhh","ab","cws","ope"};
//	for (int j = 0; j < 7; j++)
//	{
//		for (int i = name[j].length(); i < 3; i++)
//		{
//			name[j].append("0");
//		}
//	}
//	BaseSort(name, 3, 7);
//	for (int i = 0; i < 7; i++)
//	{
//		cout << name[i] << endl;
//	}
//	return 0;
//}