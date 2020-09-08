#include <iostream>
#include <string>
#define MAX_SIZE 128
using namespace std;
//�ڶ���Ϊ�ַ�����һ��[]����ĳ���  length��string����ĳ���
void BaseSort(string* s_array, int maxlength, int length)
{
	string* sortarray = new string[length];//�ȴ����洢���к������
	for (int k = maxlength - 1; k >= 0; k--)
	{
		int* count = new int[MAX_SIZE];//��������
		for (int i = 0; i < MAX_SIZE; i++)
		{
			count[i] = 0;
		}
		for (int i = 0; i < length; i++)
		{
			int index = int(s_array[i][k]);//��ȡһ�����е����һ��Ԫ��
			count[index]++;//Ȼ��������������++��
		}
		for (int j = 1; j < MAX_SIZE; j++)
		{
			count[j] = count[j] + count[j - 1];//��һ�¸�����ǰ���ж��ٸ�Ԫ�ذ��������ӵ�	Ϊ�����渳ֵ��
		}
		for (int i = length - 1; i >= 0; i--)//Ϊ���ȶ���������ʼ����
		{
			int index = int(s_array[i][k]);//��ȡ���һ��Ԫ��
			int sortindex = count[index] - 1;//�ж�Ҫ������ַ������������к��������Ǹ�λ��
			sortarray[sortindex] = s_array[i];//Ȼ��Ѹ�Ԫ�صĸ�ֵ������
			count[index]--;//��ʣ��Ԫ�صĸ���
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