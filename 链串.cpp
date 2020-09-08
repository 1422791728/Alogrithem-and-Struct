#include <iostream>
#include <string>
using namespace std;
#define BLOCK_SIZE 2
class Block {
public:
	char ch[BLOCK_SIZE];
	Block* next;
	Block()
	{
		next = NULL;
	}
};
class LString {
public:
	Block* head;//指向头块
	Block* tail;//指向尾块
	int length;//串的当前长度
	LString()
	{
		head = NULL;
		tail = NULL;
		length = 0;
	}
};
bool StrAssign_L(LString* lstr, const char* ch)//生成一个ch的链串
{
	if (!ch)
	{
		return false;
	}
	int len = strlen(ch);
	// + 1是要存一个\0
	int block_count = (len + 1) / BLOCK_SIZE;//block_count为整的块数（这些块里面存满了）
	int surplus_count = (len + 1) % BLOCK_SIZE;// surplus_count为整的块数之外多余的字符
	if (surplus_count > 0) block_count++;//如果j大于零则需要多一个块
	//创建新的块
	for (int k = 1; k <= block_count; k++)
	{
		Block* block = new Block;
		if (!block)
		{
			exit(-1);//内存溢出
		}
		block->next = NULL;//讲这个块的指针置为空
		if (k == 1)
		{
			lstr->head = block;
			lstr->tail = block;
		}
		else
		{
			lstr->tail->next = block;//则把他现在的尾块的next指向该块
			lstr->tail = block;//链串的尾指针更改;
		}
		int temp = 0;//写在这里的原因往下读代码就懂了
		for (int count = 0; count < BLOCK_SIZE && count + (k - 1) * BLOCK_SIZE < len; count++)
		{
			block->ch[count] = ch[count + (k - 1) * BLOCK_SIZE];
			temp = count + 1;
		}
		if (block_count == k)
		{
			temp = temp % BLOCK_SIZE;
			while (temp < BLOCK_SIZE)//最后一个块
			{
				if (temp == 0)
				{
					Block* newblock = new Block;
					lstr->tail->next = newblock;
					lstr->tail = newblock;
				}

				lstr->tail->ch[temp] = '\0';
				temp++;
			}
			lstr->length = len;
		}
	}
	return true;
}
//把srcStr的串中的值赋值给destStr
bool StrCopy_L(LString* destStr, LString* srcStr)
{
	for (Block* block = srcStr->head; block != NULL; block = block->next)
	{
		Block* newblock = new Block;
		if (!newblock)
		{
			exit(-1);
		}
		newblock->next = NULL;//讲这个块的指针置为空
		if (block == srcStr->head) //如果是第一个块
		{
			destStr->head = newblock;
			destStr->tail = newblock;
		}
		else
		{
			destStr->tail->next = newblock;
			destStr->tail = newblock;
		}
		for (int i = 0; i < BLOCK_SIZE; i++)
		{
			newblock->ch[i] = block->ch[i];
		}
	}
	destStr->length = srcStr->length;
	return true;
}
int StrLength_L(LString* lstr)
{
	return lstr->length;
}
int StrCompare_L(LString* str1, LString* str2)//比较两个字符串
{
	Block* str1_H = str1->head;
	Block* str2_H = str2->head;
	while (str1_H && str2_H)
	{
		for (int i = 0; i < BLOCK_SIZE && str1_H->ch[i] != '\0' && str2_H->ch[i] != '\0'; i++)
		{
			if (str1_H->ch[i] != str2_H->ch[i])
			{
				return str1_H->ch[i] - str2_H->ch[i];
			}
		}
		//如果退出循环了可能有两种可能 1 有一个到'\0',2 就是都到了该块的最大值
		//第一种情况的话说明之前的元素都相等 则长度长的大  小的那个往后移一个块则会退出while循环 
		//第二种情况就直接往后移一个块
		str1_H = str1_H->next;
		str2_H = str2_H->next;
	}
	return str1->length - str2->length;
}
void Concat_H(LString* destStr, LString* str1, LString* str2)
{
	Block* destStr_H = destStr->head;
	Block* str1_H = str1->head;
	Block* str2_H = str2->head;
	int i = 0;//链串destStr_H块中的字符数组的下标
	int j = 0;//链串str1_H块中的字符数组的下标
	int k = 0;//链串str2_H块中的字符数组的下标
	while (str1_H || str2_H)
	{
		//创建新的块并添加到destStr中
		if (!destStr_H)//判断这个块是否存在
		{
			destStr_H = new Block;
			if (!destStr_H)
			{
				exit(-1);
			}
			destStr_H->next = NULL;
			if (!destStr->head)//判断是否头指针链接了没有链接 进行链接
			{
				destStr->head = destStr->tail = destStr_H;
			}
			else
			{
				destStr->tail->next = destStr_H;
				destStr->tail = destStr_H;
			}
		}
		if (str1_H)
		{
			while (str1_H && str1_H->ch[j] != '\0')
			{
				destStr_H->ch[i] = str1_H->ch[j];
				i = (i + 1) % BLOCK_SIZE;
				j = (j + 1) % BLOCK_SIZE;
				if (!j || !(str1_H->ch[j]))
				{
					str1_H = str1_H->next;
				}
				if (!i)
				{
					destStr_H = destStr_H->next;
					break;
				}
			}
			if (str1_H && !str1_H->ch[0])
			{
				str1_H = str1_H->next;
			}
		}
		else
		{
			while (str2_H && str2_H->ch[k])
			{
				destStr_H->ch[i] = str2_H->ch[k];
				i = (i + 1) % BLOCK_SIZE;
				k = (k + 1) % BLOCK_SIZE;
				if (!k || str2_H->ch[k] == NULL)
				{
					str2_H = str2_H->next;
				}
				if (!i)
				{
					destStr_H = destStr_H->next;
					break;
				}
			}
			if (str2_H && str2_H->ch[0] == '\0')
			{
				str2_H = str2_H->next;
			}
		}
	}
	destStr->length = str1->length + str2->length;
	int count = (destStr->length) % BLOCK_SIZE;
	while (count < BLOCK_SIZE)
	{
		if (count == 0)
		{
			Block* newblock = new Block;
			destStr->tail->next = newblock;
			destStr->tail = newblock;
		}

		destStr->tail->ch[count] = '\0';
		count++;
	}
}
bool IsEmpty_L(LString* str)
{
	if (!str->head || !str->tail || !str->length)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//从 pos位置处截取len长度的子串到destStr
bool SubString_H(LString* destStr, LString* str, int pos, int len)
{
	if (IsEmpty_L(str))
	{
		return false;
	}
	if (pos < 0 || pos + len - 1 > str->length || len < 0)
	{
		return false;
	}
	//查找pos位置在哪个区块
	Block* str_H = str->head;
	int count;//区块的个数
	for (count = 1; pos > count* BLOCK_SIZE; count++)
	{
		str_H = str_H->next;
	}
	Block* newblock = destStr->head;
	int i = 0;//i记录从pos位置开始的字符个数
	int j = 0;//j遍历destStr
	int k = (pos % BLOCK_SIZE) - 1;//k遍历str
	while (i < len)
	{
		if (!newblock)//是否有空余的块给你用
		{
			newblock = new Block;
			if (!newblock)
			{
				exit(-2);
			}
			newblock->next = NULL;
			if (!destStr->head)
			{
				destStr->head = newblock;
				destStr->tail = newblock;
			}
			else
			{
				destStr->tail->next = newblock;
				destStr->tail = newblock;
			}
		}
		while (i < len)
		{
			newblock->ch[j] = str_H->ch[k];
			j = (j + 1) % BLOCK_SIZE;
			k = (k + 1) % BLOCK_SIZE;
			i++;
			if (k == 0)
			{
				str_H = str_H->next;
			}
			if (j == 0)
			{
				newblock = newblock->next;
				break;
			}
		}
	}
	destStr->length = len;
	count = (destStr->length) % BLOCK_SIZE;
	while (count < BLOCK_SIZE)
	{
		if (count == 0)
		{
			Block* newblock = new Block;
			destStr->tail->next = newblock;
			destStr->tail = newblock;
		}

		destStr->tail->ch[count] = '\0';
		count++;
	}


	return true;
}
//从pos位置开始遍历查找child在parent的位置
int Index_L(LString* parent, LString* child, int pos)
{
	if (pos < 0)
	{
		return 0;
	}
	int i = pos;
	while (i + child->length - 1 <= parent->length)
	{
		LString* substr = new LString;
		SubString_H(substr, parent, i, child->length);
		if (StrCompare_L(substr, child) != 0)
		{
			i++;
		}
		else
		{
			return i;
		}
	}
	return 0;
}
void Show_H(LString* str)
{
	if (!str->head || !str->tail || !str->length)
	{
		return;
	}
	Block* block = str->head;
	while (block != NULL)
	{
		if (block->ch)
		{
			for (int i = 0; block->ch[i] != '\0' && i < BLOCK_SIZE; i++)
			{
				cout << block->ch[i];
			}
		}
		block = block->next;
	}
	cout << endl;
}
bool ClearStr_L(LString* str)
{
	Block* block = str->head;
	while (block)
	{
		Block* next = block->next;
		delete block;
		block = next;
	}
	str->head = NULL;
	str->tail = NULL;
	str->length = 0;
	return true;
}
bool StrDelete_L(LString* str, int pos, int len)
{
	if (pos < 1 || pos + len - 1 > str->length || len < 0)
	{
		return false;
	}
	if (pos == 1 && len == str->length)
	{
		ClearStr_L(str);
	}
	int first = pos;//初始位置
	int last = pos + len - 1;//最后的位置
	Block* firstblock = str->head;//找从哪一个块开始的
	Block* lastblock = NULL;//从哪个块结束
	int count;//块的个数
	for (count = 1; first > count* BLOCK_SIZE; count++)
	{
		firstblock = firstblock->next;
	}
	for (lastblock = firstblock; last > count* BLOCK_SIZE; count++)
	{
		lastblock = lastblock->next;
	}
	int i = (first - 1) % BLOCK_SIZE;//起始下标
	int j = (last - 1) % BLOCK_SIZE;//结束下标 
	j = (j + 1) % BLOCK_SIZE;//往后移一个
	if (j == 0)
	{
		lastblock = lastblock->next;
	}
	while (lastblock && lastblock->ch[j])
	{
		firstblock->ch[i] = lastblock->ch[j];
		i = (i + 1) % BLOCK_SIZE;
		j = (j + 1) % BLOCK_SIZE;
		if (!i)
		{
			firstblock = firstblock->next;
		}
		if (!j)
		{
			lastblock = lastblock->next;
		}
	}
	str->length -= len;
	//把tail重新指向新的尾块
	str->tail = str->head;
	for (count = 1; str->length > count* BLOCK_SIZE; count++)
	{
		str->tail = str->tail->next;
	}
	count = str->length % BLOCK_SIZE;
	while (count < BLOCK_SIZE)
	{
		if (count == 0)
		{
			str->tail = str->tail->next;
		}
		str->tail->ch[count] = '\0';
		count++;
	}
	Block* block = str->tail->next;
	while (block)
	{
		str->tail->next = block->next;
		delete block;
		block = str->tail->next;
	}

}
bool StrInsert_L(LString* str, int pos, LString* insertStr)
{
	if (pos<0 || pos > str->length + 1)
	{
		return false;
	}
	Block* str1_L = str->head;
	Block* insert_L = insertStr->head;
	Block* str2_L = NULL;
	LString* tempStr = new LString;
	Block* temp_L = tempStr->head;
	int i, j, k;
	i = j = k = 0;//i是temp_L的下标 j是str1_L的下标  k是insert_L的下标
	int count = 1;//已经遍历的所有的字符个数
	while (str1_L || str2_L || insert_L)
	{
		if (!temp_L)
		{
			temp_L = new Block;
			if (!temp_L)
			{
				exit(-1);
			}
			if (!tempStr->head)
			{
				tempStr->head = temp_L;
				tempStr->tail = temp_L;
			}
			else
			{
				tempStr->tail->next = temp_L;
				tempStr->tail = temp_L;
			}
		}
		if (str1_L)
		{
			while (str1_L && count < pos)
			{
				temp_L->ch[i] = str1_L->ch[j];
				i = (i + 1) % BLOCK_SIZE;
				j = (j + 1) % BLOCK_SIZE;
				count++;
				if (!j || !(str1_L->ch[j]))
				{
					str1_L = str1_L->next;
				}
				if (!i)
				{
					temp_L = temp_L->next;
					break;
				}
			}
			if (count == pos)
			{
				str2_L = str1_L;
				str1_L = NULL;
			}
		}
		else if (insert_L)
		{
			while (insert_L && insert_L->ch[k])
			{
				temp_L->ch[i] = insert_L->ch[k];
				i = (i + 1) % BLOCK_SIZE;
				k = (k + 1) % BLOCK_SIZE;
				count++;
				if (!k || !insert_L->ch[k])
				{
					insert_L = insert_L->next;
				}
				if (!i)
				{
					temp_L = temp_L->next;
					break;
				}
			}
			if (insert_L && !insert_L->ch[0])
			{
				insert_L = insert_L->next;
			}
		}
		else
		{
			while (str2_L && str2_L->ch[j])
			{
				temp_L->ch[i] = str2_L->ch[j];
				i = (i + 1) % BLOCK_SIZE;
				j = (j + 1) % BLOCK_SIZE;
				count++;
				if (!j || !(str2_L->ch[j]))
				{
					str2_L = str2_L->next;
				}
				if (!i)
				{
					temp_L = temp_L->next;
					break;
				}
			}
			if (str2_L && !str2_L->ch[0])
			{
				str2_L = str2_L->next;
			}
		}
	}
	tempStr->length = str->length + insertStr->length;
	count = tempStr->length % BLOCK_SIZE;
	while (count < BLOCK_SIZE)
	{
		if (count == 0)
		{
			Block* newblock = new Block;
			tempStr->tail->next = newblock;
			tempStr->tail = newblock;
		}

		tempStr->tail->ch[count] = '\0';
		count++;
	}
	ClearStr_L(str);
	str->head = tempStr->head;
	str->tail = tempStr->tail;
	str->length = tempStr->length;
	delete tempStr;
	return true;
}
bool Replace_L(LString* str, LString oldstr, LString newstr)
{
	int pos = Index_L(str, &oldstr, 1);
	while (pos)
	{
		StrDelete_L(str, pos, oldstr.length);
		StrInsert_L(str, pos, &newstr);
		pos += newstr.length;
		pos = Index_L(str, &oldstr, pos);
	}
	return true;
}
//int main()
//{
//	cout << "链串" << endl;
//	LString* str1 = new LString;
//	LString* str2 = new LString;
//	LString* str3 = new LString;
//	LString* str4 = new LString;
//	StrAssign_L(str1, "ab");
//	StrAssign_L(str2, "c");
//	Concat_H(str3, str1, str2);
//	Show_H(str3);
//	SubString_H(str4, str3, 1, 2);
//	Show_H(str4);
//	StrDelete_L(str4, 1, 1);
//	Show_H(str4);
//	StrInsert_L(str1, 2, str2);
//	Show_H(str1);
//	return 0;
//}