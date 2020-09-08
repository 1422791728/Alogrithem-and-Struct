#include <iostream>
using namespace std;
//���������õݹ�ʵ��
void QuickSort(int* s_array, int left, int right)
{
	//���±���������±���˵���ݹ����
	if (left > right)
	{
		return;
	}
	int i = left;
	int j = right - 1;
	while (i <= j)
	{
		if (s_array[i] > s_array[right])
		{
			int temp = s_array[i];
			s_array[i] = s_array[j];
			s_array[j] = temp;
			j--;
		}
		else
		{
			i++;
		}
	}
	int temp = s_array[i];
	s_array[i] = s_array[right];
	s_array[right] = temp;
	QuickSort(s_array,left,i - 1);
	QuickSort(s_array, i + 1, right);
}
void Show(int* num, int length)
{
	for (int i = 0; i < length; i++)
	{
		cout << num[i] << endl;
	}
}
//int main()
//{
//	int num[] = { 5,2,1,0,3,3};
//	QuickSort(num, 0, 5);
//	Show(num,6);
//	return 0;
//}