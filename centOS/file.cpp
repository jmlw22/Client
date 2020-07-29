#include "main.h"
#include <fstream>
/*
 *@获取系统本地时间
 *@path
 */

//把数据写入到 FILE_NAME 文件中
int WriteFile(const char *data)
{
	int ret = 0;

	//获取系统本地时间
	char date_buf[32] = { 0 };
	char datatime[16] = {0};
	time_t now_time = time(NULL);
	struct tm* t = localtime(&now_time);

	//把time需要的对应格式转化到time_buf中
	sprintf(date_buf, "./log/%04d-%02d-%02d.log", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
	//存储的log文件名
	printf("filename is : %s\n\n", date_buf);

/*	if (00 == t->tm_sec || 01 == t->tm_sec || 02 == t->tm_sec)
	{	
		
		fstream fd ;
		fd.open(date_buf,ios::in);
		if (!fd)
		{
			cout  << date_buf << "don't exit this file!" << endl;
			system("mkdir ./log");

		}
		else
		{
			cout << date_buf << "exit this file !" << endl;
			fd.close();
		}
		printf("filename is : %s\n\n\n", date_buf);
	}
*/
	//打开 date_buf 文件，以追加内容的形式
	ofstream OutFile(date_buf,ofstream::app);
	//把data数据存储到 OutFile打开的文件中
	OutFile << data ;
	//关闭打开的文件
	OutFile.close();


	return ret;
}

