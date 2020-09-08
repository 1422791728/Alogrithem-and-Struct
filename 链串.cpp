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
	Block* head;//ָ��ͷ��
	Block* tail;//ָ��β��
	int length;//���ĵ�ǰ����
	LString()
	{
		head = NULL;
		tail = NULL;
		length = 0;
	}
};
bool StrAssign_L(LString* lstr, const char* ch)//����һ��ch������
{
	if (!ch)
	{
		return false;
	}
	int len = strlen(ch);
	// + 1��Ҫ��һ��\0
	int block_count = (len + 1) / BLOCK_SIZE;//block_countΪ���Ŀ�������Щ����������ˣ�
	int surplus_count = (len + 1) % BLOCK_SIZE;// surplus_countΪ���Ŀ���֮�������ַ�
	if (surplus_count > 0) block_count++;//���j����������Ҫ��һ����
	//�����µĿ�
	for (int k = 1; k <= block_count; k++)
	{
		Block* block = new Block;
		if (!block)
		{
			exit(-1);//�ڴ����
		}
		block->next = NULL;//��������ָ����Ϊ��
		if (k == 1)
		{
			lstr->head = block;
			lstr->tail = block;
		}
		else
		{
			lstr->tail->next = block;//��������ڵ�β���nextָ��ÿ�
			lstr->tail = block;//������βָ�����;
		}
		int temp = 0;//д�������ԭ�����¶�����Ͷ���
		for (int count = 0; count < BLOCK_SIZE && count + (k - 1) * BLOCK_SIZE < len; count++)
		{
			block->ch[count] = ch[count + (k - 1) * BLOCK_SIZE];
			temp = count + 1;
		}
		if (block_count == k)
		{
			temp = temp % BLOCK_SIZE;
			while (temp < BLOCK_SIZE)//���һ����
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
//��srcStr�Ĵ��е�ֵ��ֵ��destStr
bool StrCopy_L(LString* destStr, LString* srcStr)
{
	for (Block* block = srcStr->head; block != NULL; block = block->next)
	{
		Block* newblock = new Block;
		if (!newblock)
		{
			exit(-1);
		}
		newblock->next = NULL;//��������ָ����Ϊ��
		if (block == srcStr->head) //����ǵ�һ����
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
int StrCompare_L(LString* str1, LString* str2)//�Ƚ������ַ���
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
		//����˳�ѭ���˿��������ֿ��� 1 ��һ����'\0',2 ���Ƕ����˸ÿ�����ֵ
		//��һ������Ļ�˵��֮ǰ��Ԫ�ض���� �򳤶ȳ��Ĵ�  С���Ǹ�������һ��������˳�whileѭ�� 
		//�ڶ��������ֱ��������һ����
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
	int i = 0;//����destStr_H���е��ַ�������±�
	int j = 0;//����str1_H���е��ַ�������±�
	int k = 0;//����str2_H���е��ַ�������±�
	while (str1_H || str2_H)
	{
		//�����µĿ鲢��ӵ�destStr��
		if (!destStr_H)//�ж�������Ƿ����
		{
			destStr_H = new Block;
			if (!destStr_H)
			{
				exit(-1);
			}
			destStr_H->next = NULL;
			if (!destStr->head)//�ж��Ƿ�ͷָ��������û������ ��������
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
//�� posλ�ô���ȡlen���ȵ��Ӵ���destStr
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
	//����posλ�����ĸ�����
	Block* str_H = str->head;
	int count;//����ĸ���
	for (count = 1; pos > count* BLOCK_SIZE; count++)
	{
		str_H = str_H->next;
	}
	Block* newblock = destStr->head;
	int i = 0;//i��¼��posλ�ÿ�ʼ���ַ�����
	int j = 0;//j����destStr
	int k = (pos % BLOCK_SIZE) - 1;//k����str
	while (i < len)
	{
		if (!newblock)//�Ƿ��п���Ŀ������
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
//��posλ�ÿ�ʼ��������child��parent��λ��
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
	int first = pos;//��ʼλ��
	int last = pos + len - 1;//����λ��
	Block* firstblock = str->head;//�Ҵ���һ���鿪ʼ��
	Block* lastblock = NULL;//���ĸ������
	int count;//��ĸ���
	for (count = 1; first > count* BLOCK_SIZE; count++)
	{
		firstblock = firstblock->next;
	}
	for (lastblock = firstblock; last > count* BLOCK_SIZE; count++)
	{
		lastblock = lastblock->next;
	}
	int i = (first - 1) % BLOCK_SIZE;//��ʼ�±�
	int j = (last - 1) % BLOCK_SIZE;//�����±� 
	j = (j + 1) % BLOCK_SIZE;//������һ��
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
	//��tail����ָ���µ�β��
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
	i = j = k = 0;//i��temp_L���±� j��str1_L���±�  k��insert_L���±�
	int count = 1;//�Ѿ����������е��ַ�����
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
//	cout << "����" << endl;
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