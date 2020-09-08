#include <iostream>
#include <string>
using namespace std;
class HString {
public:
	char* ch;
	int length;
	HString()
	{
		length = 0;
		ch = NULL;
	}
	~HString()
	{
		delete[] ch;
	}
};
bool IsEmpty_H(HString* str)
{
	if (!str->ch || str->length == 0)
	{
		return true;
	}
	return false;

}
bool StrAssian_H(HString* str, const char* ch)
{
	int len = strlen(ch);
	if (!ch)
	{
		return false;
	}
	str->ch = new char[len + 1];
	if (!str->ch)
	{
		cout << "内存溢出" << endl;
		exit(-1);
	}
	for (int i = 0; i < len + 1; i++)
	{
		str->ch[i] = ch[i];
	}
	str->length = len;
	return true;
}
void ShowHString(HString* str)
{
	if (IsEmpty_H(str))
	{
		cout << "字符串为空" << endl;
		return;
	}
	cout << str->ch << endl;
}
//把srcStr的值赋值给destStr
bool Strcopy_H(HString* destStr, HString* srcStr)
{
	if (IsEmpty_H(srcStr))
	{
		return false;
	}
	destStr->ch = new char[srcStr->length + 1];
	if (!destStr->ch)
	{
		cout << "内存溢出" << endl;
		exit(-1);
	}
	for (int i = 0; i < srcStr->length + 1; i++)
	{
		destStr->ch[i] = srcStr->ch[i];
		//destStr[i].ch = srcStr[i].ch; //这行是错误代码
	}
	destStr->length = srcStr->length;
	return true;
}
int StrCompare_H(HString* str1, HString* str2)
{
	for (int i = 0; i < str1->length && i < str2->length; i++)
	{
		if (str1->ch[i] != str2->ch[i])
		{
			return str1->ch[i] - str2->ch[i];
		}
	}
	return str1->length - str2->length;
}
bool ConCat_H(HString* destStr, HString* str1, HString* str2)
{
	destStr->length = str1->length + str2->length;
	destStr->ch = new char[destStr->length + 1];
	if (!destStr->ch)
	{
		exit(-1);
	}
	for (int i = 0; i < str1->length + 1; i++)
	{
		destStr->ch[i] = str1->ch[i];
	}
	for (int i = 0; i < str2->length + 1; i++)
	{
		destStr->ch[i + str1->length] = str2->ch[i];
	}
	return true;
}
bool SubString_H(HString* destStr, HString* str, int pos, int len)
{
	if (IsEmpty_H(str))
	{
		return false;
	}
	if (pos < 1 || pos + len - 1 > str->length || len < 0)
	{
		return false;
	}
	destStr->ch = new char[len + 1];
	if (!destStr->ch)
	{
		exit(-1);
	}
	for (int i = 0; i < len; i++)
	{
		destStr->ch[i] = str->ch[pos - 1 + i];
	}
	destStr->ch[len] = '\0';
	destStr->length = len;
	return true;
}
int Index_H(HString* parent, HString* child, int pos)
{
	if (pos < 0)
		return 0;
	HString* subStr = new HString;
	int i = pos;
	while (i + child->length - 1 <= parent->length)
	{
		SubString_H(subStr, parent, i, child->length);
		if (StrCompare_H(subStr, child) != 0)
		{
			i++;
		}
		else
		{
			return i;
		}
	}
	delete subStr;
	return 0;
}
bool StrDelete_H(HString* str, int pos, int len)
{
	if (IsEmpty_H(str))
	{
		exit(-1);
	}
	if (pos < 0 || pos + len - 1 > str->length || len < 0)
	{
		return false;
	}
	for (int i = pos - 1; i + len < str->length + 1; i++)
	{
		str->ch[i] = str->ch[i + len];
	}
	str->length -= len;
	char* temp = new char[str->length + 1];
	strcpy_s(temp, str->length + 1, str->ch);
	/*for (int i = 0; i < str->length + 1; i++)
	{
		temp[i] = str->ch[i];
	}*/
	delete[] str->ch;
	str->ch = temp;
	//str->ch = (char*)realloc(str->ch, str->length  + 1);
	return true;
}
bool StrInsert_H(HString* str, int pos, HString* insertStr)
{
	if (pos < 0 || pos > str->length + 1)
	{
		return false;
	}
	if (IsEmpty_H(str))
	{
		exit(-1);
	}
	/*char* temp = new char[str->length  + insertStr ->length + 1];
	for (int i = 0; i < str->length + 1; i++)
	{
		temp[i] = str->ch[i];
	}
	delete[] str->ch;
	str->ch = temp;*/
	str->ch = (char*)realloc(str->ch, str->length + insertStr->length + 1);
	for (int i = str->length; i >= pos - 1; i--)
	{
		str->ch[i + insertStr->length] = str->ch[i];
	}
	for (int i = 0; i < insertStr->length; i++)
	{
		str->ch[i + pos - 1] = insertStr->ch[i];
	}
	str->length += insertStr->length;
	return true;
}
bool Replace_H(HString* str, HString* oldStr, HString* newStr)
{
	if (IsEmpty_H(str))
	{
		return false;
	}
	int pos = Index_H(str, oldStr, 1);
	if (pos == 0)
	{
		return false;
	}
	while (pos != 0)
	{
		StrDelete_H(str, pos, oldStr->length);
		StrInsert_H(str, pos, newStr);
		pos += newStr->length;
		pos = Index_H(str, oldStr, pos);
	}
	return true;
}
//int main()
//{
//	HString* str1 = new HString;
//	HString* str2 = new HString;
//	HString* str3 = new HString;
//	HString* str4 = new HString;
//	HString* str5 = new HString;
//	StrAssian_H(str1, "abcd");
//	Strcopy_H(str2, str1);
//	ConCat_H(str3, str2, str1);
//	SubString_H(str4, str3, 2, 3);
//	StrDelete_H(str3, 2, 3);
//	StrInsert_H(str3, 2, str1);
//	Replace_H(str3, str1, str4);
//	ShowHString(str3);
//	/*void* ptr1 = str1->ch;
//	void* ptr2 = str2->ch;
//	cout << ptr1 << endl;
//	cout << ptr2 << endl;*/
//	delete str2;
//	delete str3;
//	delete str1;
//	delete str4;
//	delete str5;
//	return 0;
//}
int BFIndex_H(HString* parent, HString* child, int pos)
{
	int i = pos;
	int j = 1;
	while (i <= parent->length && j <= child->length)
	{
		if (parent->ch[i - 1] == child->ch[j - 1])
		{
			i++;
			j++;
		}
		else
		{
			i = i - j + 2;
			j = 1;
		}
	}
	if (j > child->length)
	{
		return i - child->length;
	}
	else 
	{
		return 0;
	}
}
void Get_Next(HString* str,int * next)
{
	int i = 0;
	int j = -1;
	next[0] = -1;
	while (i < str->length)
	{
		if (j == -1 || str->ch[i] == str->ch[j])
		{
			i++;
			j++;
			next[i] = j;
		}
		else
		{
			j = next[j];
		}
	}
}
int KMPCompare_H(HString* parent, HString* child, int pos)
{
	int next[255];
	Get_Next(child,next);
	int i = pos - 1;
	int j = 0;
	while (i < parent->length && j < child->length)
	{
		if (j == -1 || parent->ch[i] == child->ch[j])
		{
			i++;
			j++;
		}
		else
		{
			j = next[j];
		}
	}
	if (j == child->length)
	{
		return i + 1 - j;
	}
	return 0;
}
//int main()
//{
//	HString* str1 = new HString;
//	HString* str2 = new HString;
//	StrAssian_H(str1, "abcd bca ad");
//	StrAssian_H(str2, "bcd");
//	int pos1 = BFIndex_H(str1, str2, 1);
//	int pos2 = KMPCompare_H(str1, str2, 1);
//	cout << pos1 << endl;
//	cout << pos2 << endl;
//}


//病毒测试
//存在为真
bool CheckVirus(HString &parent, HString &child)
{
	char *tempVirus = new char[child.length * 2 + 1];
	for (int i = 0; i < child.length * 2; i++)
	{
		tempVirus[i] = child.ch[i % child.length];
	}
	tempVirus[child.length * 2] = '\0';
	for (int i = 0; i < child.length; i++)
	{
		char* temp = new char[child.length + 1];
		for (int j = i; j < child.length + i; j++)
		{
			temp[j - i] = tempVirus[j];
		}
		temp[child.length] = '\0';
		HString temp_H;
		StrAssian_H(&temp_H, temp);
		if (KMPCompare_H(&parent, &temp_H, 1) != 0)
		{
			return true;
		}
	}
	return 0;
}
//int main()
//{
//	HString parent;
//	StrAssian_H(&parent, "aaabbba");
//	HString child;
//	StrAssian_H(&child, "baa");
//	if (CheckVirus(parent, child))
//	{
//		cout << "存在" << endl;
//	}
//	else
//	{
//		cout << "不存在" << endl;
//	}
//	return 0;
//}