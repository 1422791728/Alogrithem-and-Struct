#include <iostream>
#include <dirent.h> //获取文件目录
#include <sys/stat.h> //获取文件信息的
#include <cstring>
using namespace std;
void Print(const char* dir, int depth)
{
	DIR* dirPtr = NULL; //目录指针
	if ((dirPtr = opendir(dir)) == NULL)
	{
		cout << "无法打开该目录:" << dir << endl;
		return;
	}
	struct dirent* dirContent = NULL; //目录内容
	while ((dirContent = readdir(dirPtr)) != NULL)
	{
		if (strcmp(dirContent->d_name, ".") == 0 || strcmp(dirContent->d_name, "..") == 0)
		{
			continue;
		}
		char fullname[1024];//文件或目录的全名
		sprintf_s(fullname, "%s\\%s", dir, dirContent->d_name);
		cout << fullname << endl;
		struct stat statInfo;//当前文件或目录的信息
		if (stat(fullname, &statInfo) == -1)
		{
			cout << "无法获取" << fullname << "文件详细信息" << endl;
		}
		if ((statInfo.st_mode & S_IFMT) == S_IFDIR)
		{
			cout << "是目录" << endl;
			Print(fullname, ++depth);
		}
		else if ((statInfo.st_mode & S_IFMT) == S_IFREG)
		{
			cout << "是一般文件，所占空间" << statInfo.st_size << endl;
		}
	}

}
//int main()
//{
//	Print("D:\\oneheart", 0);
//	return 0;
//}