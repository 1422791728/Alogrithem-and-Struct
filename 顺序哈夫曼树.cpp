#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#define MAX_SIZE 256 //一共255个字符
#define ASCII_SIZE 128 //一共128个 老版本的
using namespace std;
class HaffNode
{
public:
	char data;	//存的字符
	int weight;//权值
	HaffNode* leftChild;//左孩子
	HaffNode* rightChild;//右孩子
};
HaffNode node[MAX_SIZE];
HaffNode Right[MAX_SIZE / 2 + 1];//用来存储被替换掉的最小的两个数中的较大的那个	也就是作为右孩子的那个
HaffNode Left[MAX_SIZE / 2 + 1];////用来存储被替换掉的最小的两个数中的较小的那个  也就是作为左孩子的那个
//按照降序
void SortHaffmanNode(HaffNode* node, int length)//哈夫曼树权值数组，数组元素个数
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
void CreateHaffmanTree(HaffNode* node, int length)//哈夫曼树权值数组，数组元素个数
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
char code[MAX_SIZE][MAX_SIZE / 2];//用来存储叶节点对应的哈夫曼编码
// 第一个为结点数组，第二个是该叶节点对应的哈夫曼编码，第三个是tempCode的数组下标
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
// flag是告诉解码时候向左走还是向右
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
//	unsigned char savechar = 0;//用来记录转为二进制后的编码
//	unsigned char tempchar; //用来记录解压缩时候往左走往右走
//	ifstream ifs;//打开待压缩的文件
//	ifs.open("input.txt", ios::in);//待压缩的文件
//	if (!ifs.is_open())
//	{
//		cout << "打开失败" << endl;
//		return 0;
//	}
//	int filelength = 0;//Intput里面的字节数
//	int asciicount[ASCII_SIZE] = { 0 };//用来计算每个字符所带的权值的
//	char readchar;
//	while ((readchar = ifs.get()) != EOF)
//	{
//		filelength++;
//		asciicount[readchar - 0]++;
//	}
//	int num = 0;//结点个数
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
//	ofstream ofs;//这个是二进制文件用来存储哈夫曼编码的
//	ofs.open("ziped.txt", ios::out | ios::binary);
//	char tempCode[MAX_SIZE / 2];//用来临时存储哈夫曼编码 空间是随便给的
//	Coding(node, tempCode, 0);
//	num = 0;//计数器归零，用来记录savachar存了二进制的个数
//	ifs.open("input.txt", ios::in);
//	//int zzzz = 0;
//	int ziplength = 0;//压缩后所占的字节
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
//	cout << "压缩前字节为" << filelength << "压缩后字节为" << ziplength << endl;
//	cout << "压缩率为" << (double)ziplength / filelength * 100 << endl;
//	//cout << zzzz << endl;
//	ifstream ifs_zip;//打开二进制文件
//	ifs_zip.open("ziped.txt", ios::in | ios::binary);
//	/*FILE* ISF_ = fopen("ziped.txt", "rb");*/
//	/*if (!ifs_zip.is_open())
//	{
//		cout << "打开失败" << endl;
//		return 0;
//	}*/
//	ofstream ofs_uncode;//解压缩的文件写入
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
//	cout << "解压缩完成" << endl;
//}