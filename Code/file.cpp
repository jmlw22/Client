#include "main.h"
#include <direct.h>
#include <io.h>

//������д�뵽 FILE_NAME �ļ���
int WriteFile(const char* data)
{
	int ret = 0;
	//const char* filename;
	//�����ļ���ָ��
	FILE* fp = NULL;
	errno_t eResult;

	//��ȡϵͳ����ʱ��
	char date_buf[32] = { 0 };
	time_t now_time = time(NULL);
	struct tm* t = localtime(&now_time);
	//��time��Ҫ�Ķ�Ӧ��ʽת����time_buf��
	sprintf(date_buf, "%04d-%02d-%02d.log", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);


	printf("filename is : %s\n", date_buf);

	//stringstream str;
	//string fn;
	//str << FILE_NAME;
	//str << date_buf;

	fstream _file;
	_file.open(date_buf, ios::in);
	if (!_file)
	{
		cout << "no this file" << endl;
	}
	else
	{
		cout << "exist this file" << endl;
	}
	_file.close();


	//���ļ�:FILE_NAME,��׷�ӵ���ʽ��"a+"
	eResult = fopen_s(&fp, date_buf, "a+");
	if (0 != eResult)
	{
		printf("open %s file error!!\n", date_buf);
		exit(-1);
	}

	//д��data���ݵ�fp��
	fputs(data, fp);

	//�ر��ļ�
	fclose(fp);

	return ret;
}


int judgeFile(void)
{
	string dir = "./2020-06-22.log";
	
	if (access(dir.c_str(),0) == -1)
	{

		
		cout << "no this file" << endl;
		int flag = _mkdir(dir.c_str());
		if (0 == flag)
		{
			cout << "make file successful" << endl;
		}
		else
		{
			cout << "make file error" << endl;
		}
	}
	Sleep(3000);
	if(access(dir.c_str(),0) == 0)
	{
		cout << "exist this file" << endl;
		int flag = rmdir(dir.c_str());
		if (0 == flag)
		{
			cout << "delete file successful" << endl;
		}
		else
		{
			cout << "delete file error" << endl;
		}
	}

	return 0;
}

















/////Ŀ¼�Ƿ���ڵļ�飺
//bool  CheckFolderExist(const string &strPath)
//{
//	WIN32_FIND_DATA  wfd;
//	bool rValue = false;
//	HANDLE hFind = FindFirstFile(strPath.c_str(), &wfd);
//	if ((hFind != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
//	{
//		rValue = true;
//	}
//	FindClose(hFind);
//	return rValue;
//}
