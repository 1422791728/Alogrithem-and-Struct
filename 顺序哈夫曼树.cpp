#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#define MAX_SIZE 256 //һ��255���ַ�
#define ASCII_SIZE 128 //һ��128�� �ϰ汾��
using namespace std;
class HaffNode
{
public:
	char data;	//����ַ�
	int weight;//Ȩֵ
	HaffNode* leftChild;//����
	HaffNode* rightChild;//�Һ���
};
HaffNode node[MAX_SIZE];
HaffNode Right[MAX_SIZE / 2 + 1];//�����洢���滻������С���������еĽϴ���Ǹ�	Ҳ������Ϊ�Һ��ӵ��Ǹ�
HaffNode Left[MAX_SIZE / 2 + 1];////�����洢���滻������С���������еĽ�С���Ǹ�  Ҳ������Ϊ���ӵ��Ǹ�
//���ս���
void SortHaffmanNode(HaffNode* node, int length)//��������Ȩֵ���飬����Ԫ�ظ���
{
	for (int i = 0; i < length - 1; i++)
	{
		for (int j = 0; j < length - i - 1; j++)
		{
			if (node[j].weight < node[j + 1].weight)
			{
				HaffNode temp = node[j];
				node[j] = node[j + 1];
				node[j + 1] = temp;
			}
		}
	}
}
void CreateHaffmanTree(HaffNode* node, int length)//��������Ȩֵ���飬����Ԫ�ظ���
{
	if (length <= 1)
	{
		return;
	}
	SortHaffmanNode(node, length);
	HaffNode parent;
	Right[length] = node[length - 2];
	Left[length] = node[length - 1];
	parent.weight = Right[length].weight + Left[length].weight;
	parent.leftChild = &Left[length];
	parent.rightChild = &Right[length];
	node[length - 2] = parent;
	CreateHaffmanTree(node, length - 1);
}
char code[MAX_SIZE][MAX_SIZE / 2];//�����洢Ҷ�ڵ��Ӧ�Ĺ���������
// ��һ��Ϊ������飬�ڶ����Ǹ�Ҷ�ڵ��Ӧ�Ĺ��������룬��������tempCode�������±�
void Coding(HaffNode* node, char* tempCode, int index)
{
	if (!node) return;
	if (node->leftChild == NULL || node->rightChild == NULL)
	{
		tempCode[index] = '\0';
		strcpy_s(code[node->data - 0], tempCode);
		return;
	}
	tempCode[index] = '0';
	Coding(node->leftChild, tempCode, index + 1);
	tempCode[index] = '1';
	Coding(node->rightChild, tempCode, index + 1);
}
// flag�Ǹ��߽���ʱ�������߻�������
HaffNode* UnCoding(HaffNode* node, int flag)
{
	if (flag == 0)
	{
		return node->leftChild;
	}
	else if(flag == 1)
	{
		return node->rightChild;
	}
}
//int main()
//{
//	unsigned char savechar = 0;//������¼תΪ�����ƺ�ı���
//	unsigned char tempchar; //������¼��ѹ��ʱ��������������
//	ifstream ifs;//�򿪴�ѹ�����ļ�
//	ifs.open("input.txt", ios::in);//��ѹ�����ļ�
//	if (!ifs.is_open())
//	{
//		cout << "��ʧ��" << endl;
//		return 0;
//	}
//	int filelength = 0;//Intput������ֽ���
//	int asciicount[ASCII_SIZE] = { 0 };//��������ÿ���ַ�������Ȩֵ��
//	char readchar;
//	while ((readchar = ifs.get()) != EOF)
//	{
//		filelength++;
//		asciicount[readchar - 0]++;
//	}
//	int num = 0;//������
//	for (int i = 0; i < ASCII_SIZE; i++)
//	{
//		if (asciicount[i] != 0)
//		{
//			node[num].data = i;
//			node[num].weight = asciicount[i];
//			num++;
//		}
//	}
//	CreateHaffmanTree(node, num);
//	ifs.close();
//	/*FILE* OFS = fopen("ziped.txt", "wb");*/
//	ofstream ofs;//����Ƕ������ļ������洢�����������
//	ofs.open("ziped.txt", ios::out | ios::binary);
//	char tempCode[MAX_SIZE / 2];//������ʱ�洢���������� �ռ���������
//	Coding(node, tempCode, 0);
//	num = 0;//���������㣬������¼savachar���˶����Ƶĸ���
//	ifs.open("input.txt", ios::in);
//	//int zzzz = 0;
//	int ziplength = 0;//ѹ������ռ���ֽ�
//	while ((readchar = ifs.get()) != EOF)
//	{
//		/*if ((strlen(code[readchar - 0]) != 0))
//		{
//			cout << strlen(code[readchar - 0]) << "\t" << readchar<< endl;
//		}*/
//		for (int i = 0; i < strlen(code[readchar - 0]); i++)
//		{
//			/*cout << code[readchar - 0][i] << endl;*/
//			savechar |= code[readchar - 0][i] - '0';
//			num++;
//			//zzzz++;
//			if (num == 8)
//			{
//				ofs.write((const char*)&savechar, sizeof(savechar));
//				//fwrite(&savechar, sizeof(savechar), 1, OFS);
//				ziplength++;
//				num = 0;
//				savechar = 0;
//			}
//			else
//			{
//				savechar <<= 1;
//			}
//		};
//	}
//	if (num < 8)
//	{
//		savechar <<= (8 - num);
//		//fwrite(&savechar, sizeof(savechar), 1, OFS);
//		ofs.write((const char*)&savechar, sizeof(savechar));
//		ziplength++;
//		num = 0;
//		savechar = 0;
//	}
//	ofs.close();
//	//fclose(OFS);
//	ifs.close();
//	cout << "ѹ��ǰ�ֽ�Ϊ" << filelength << "ѹ�����ֽ�Ϊ" << ziplength << endl;
//	cout << "ѹ����Ϊ" << (double)ziplength / filelength * 100 << endl;
//	//cout << zzzz << endl;
//	ifstream ifs_zip;//�򿪶������ļ�
//	ifs_zip.open("ziped.txt", ios::in | ios::binary);
//	/*FILE* ISF_ = fopen("ziped.txt", "rb");*/
//	/*if (!ifs_zip.is_open())
//	{
//		cout << "��ʧ��" << endl;
//		return 0;
//	}*/
//	ofstream ofs_uncode;//��ѹ�����ļ�д��
//	ofs_uncode.open("result.txt", ios::out);
//	HaffNode* currnode = &node[0];
//	//FILE* OFS_UN = fopen("result.txt", "w");
//	while(ifs_zip.read(&readchar, sizeof(unsigned char))) /*(fread(&readchar, sizeof(unsigned char), 1, ISF_))*/
//	{
//
//		for (int i = 0; i < 8; i++)
//		{
//			if (filelength == num)
//			{
//				break;
//			}
//			tempchar = readchar & 128;
//			tempchar >>= 7;
//			//cout << (int)tempchar << endl;
//			readchar <<= 1;
//			currnode = UnCoding(currnode, tempchar - 0);
//			if (currnode->leftChild == NULL || currnode->rightChild == NULL)
//			{
//				ofs_uncode << currnode->data;
//				//fprintf(OFS_UN,"%c",currnode->data);
//				currnode = &node[0];
//				num++;
//			}
//		}
//
//	}
//	/*fclose(OFS_UN);
//	fclose(ISF_);*/
//	ifs_zip.close();
//	ofs_uncode.close();
//	cout << "��ѹ�����" << endl;
//}