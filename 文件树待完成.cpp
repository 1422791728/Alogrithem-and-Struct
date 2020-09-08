#include <iostream>
#include <dirent.h> //��ȡ�ļ�Ŀ¼
#include <sys/stat.h> //��ȡ�ļ���Ϣ��
#include <cstring>
using namespace std;
void Print(const char* dir, int depth)
{
	DIR* dirPtr = NULL; //Ŀ¼ָ��
	if ((dirPtr = opendir(dir)) == NULL)
	{
		cout << "�޷��򿪸�Ŀ¼:" << dir << endl;
		return;
	}
	struct dirent* dirContent = NULL; //Ŀ¼����
	while ((dirContent = readdir(dirPtr)) != NULL)
	{
		if (strcmp(dirContent->d_name, ".") == 0 || strcmp(dirContent->d_name, "..") == 0)
		{
			continue;
		}
		char fullname[1024];//�ļ���Ŀ¼��ȫ��
		sprintf_s(fullname, "%s\\%s", dir, dirContent->d_name);
		cout << fullname << endl;
		struct stat statInfo;//��ǰ�ļ���Ŀ¼����Ϣ
		if (stat(fullname, &statInfo) == -1)
		{
			cout << "�޷���ȡ" << fullname << "�ļ���ϸ��Ϣ" << endl;
		}
		if ((statInfo.st_mode & S_IFMT) == S_IFDIR)
		{
			cout << "��Ŀ¼" << endl;
			Print(fullname, ++depth);
		}
		else if ((statInfo.st_mode & S_IFMT) == S_IFREG)
		{
			cout << "��һ���ļ�����ռ�ռ�" << statInfo.st_size << endl;
		}
	}

}
//int main()
//{
//	Print("D:\\oneheart", 0);
//	return 0;
//}