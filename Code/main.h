#pragma once
#include <string>
#include <iostream>
#include <cstring>
#include <WS2tcpip.h>
#include <winsock.h>
#include <time.h>
#include <stdio.h>
#include <fstream>
#include "json.h"

using namespace std;
//���ؿ��ļ�
#pragma comment(lib, "ws2_32.lib") 
#pragma comment(lib, "json_vc71_libmtd.lib")
#pragma warning(disable:4996)

//����ֵ�ıȽ�����ֵ��С
#define  COM_VALUE  0.05000
//�洢client�����ص��ļ����͸�ʽ��׺
#define	 FILE_NAME	"2020-06-22.log "

#ifdef SPT
//������IP��ַ
const char ipaddr8[] = "192.168.10.232";         //5#3##8
const char ipaddr11[] = "192.168.10.238";        //4#4##11
const char ipaddr12[] = "192.168.10.231";        //5#3##12
const char ipaddr20[] = "192.168.10.239";        //4#3##20
const char ipaddr23[] = "192.168.10.233";        //5#7##23
const char ipaddr29[] = "192.168.10.240";		 //5#3##29
const char ipaddr30[] = "192.168.10.237";       //5#7##30
const char ipaddr31[] = "192.168.10.235";       //5#6##31
const char ipaddr32[] = "192.168.10.236";       //5#7##32
const char ipaddr33[] = "192.168.10.234";       //4#2##33

#define IP_ADDR_8      "192.168.10.232"         //5#3##8
#define IP_ADDR_11     "192.168.10.238"        //4#4##11
#define IP_ADDR_12     "192.168.10.231"        //5#3##12
#define IP_ADDR_20     "192.168.10.239"        //4#3##20
#define IP_ADDR_23     "192.168.10.233"        //5#7##23
#define IP_ADDR_29     "192.168.10.240"        //5#3##29
#define IP_ADDR_30     "192.168.10.237"        //5#7##30
#define IP_ADDR_31     "192.168.10.235"        //5#6##31
#define IP_ADDR_32     "192.168.10.236"        //5#7##32
#define IP_ADDR_33     "192.168.10.234"        //4#2##33

//���͸�������������
const char sendData8[] = { 0x08,0x03,0x00,0x48,0x00,0x0A,0x45,0x42 };//���������� 08 03 00 48 00 0A 45 42
const char sendData11[] = { 0x0B,0x03,0x00,0x48,0x00,0x0A,0x45,0x71 };//0B 03 00 48 00 0A 45 71
const char sendData12[] = { 0x0C,0x03,0x00,0x48,0x00,0x0A,0x44,0xC6 };//0C 03 00 48 00 0A 44 C6
const char sendData20[] = { 0x14,0x03,0x00,0x48,0x00,0x0A,0x47,0x1E };//14 03 00 48 00 0A 47 1E
const char sendData23[] = { 0x17,0x03,0x00,0x48,0x00,0x0A,0x47,0x2D };//17 03 00 48 00 0A 47 2D
const char sendData29[] = { 0x1D,0x03,0x00,0x48,0x00,0x0A,0x47,0x87 };//1D 03 00 48 00 0A 47 87
const char sendData30[] = { 0x1E,0x03,0x00,0x48,0x00,0x0A,0x47,0xB4 };//1E 03 00 48 00 0A 47 B4
const char sendData31[] = { 0x1F,0x03,0x00,0x48,0x00,0x0A,0x46,0x65 };//1F 03 00 48 00 0A 46 65
const char sendData32[] = { 0x20,0x03,0x00,0x48,0x00,0x0A,0x43,0x6A };//20 03 00 48 00 0A 43 6A
const char sendData33[] = { 0x21,0x03,0x00,0x48,0x00,0x0A,0x42,0xBB };//21 03 00 48 00 0A 42 BB

#define IP_PORT         9999


#else
#define IP_ADDR_GY    "172.10.7.222"
#define IP_ADDR     "172.10.6.8"
//��������IP�˿�
#define IP_PORT         23

//��̨��������IP��ַ
const char ipaddr_server[] = "172.10.5.25";
//������������IP��ַ
const char ipaddr_gy[] = "172.10.7.222";
//ftp�ķ�������ַ
const char ipaddr_ftp[] = "172.10.5.12";

//���͵�������������
const char sendData2[] = { 0x02,0x03,0x00,0x00,0x00,0x02,0xC4,0x38 };//�¶ȴ�����
const char sendData3[] = { 0x03,0x03,0x00,0x00,0x00,0x02,0xC5,0xE9 };//�¶ȴ�����
const char sendData4[] = { 0x04,0x03,0x00,0x48,0x00,0x0A,0x45,0x8E };//����������
const char sendData5[] = { 0x05,0x03,0x00,0x48,0x00,0x0A,0x44,0x5F };//����������
const char sendData6[] = { 0x06,0x03,0x00,0x48,0x00,0x0A,0x44,0x6C };//
const char sendData7[] = { 0x07,0x03,0x00,0x48,0x00,0x0A,0x45,0xBD };//
const char sendData8[] = { 0x08,0x03,0x00,0x48,0x00,0x0A,0x45,0x42 };
const char sendData9[] = { 0x09,0x03,0x00,0x48,0x00,0x0A,0x44,0x93 };
const char sendData10[] = { 0x0A,0x03,0x00,0x48,0x00,0x0A,0x44,0xA0 };//UCHAR


#endif // SPT


//������������ֵ
typedef struct sensorinfo{
	int id;//��������id��ַ��
	int status;//״ֵ̬
	double electricity;//�������ĵ���ֵ��С
	//״̬�仯ֵ���쳣 abnormal������ on���ػ� off
	enum MyStatus
	{
		abnormal = -1,
		on = 1, 
		off,  
		other = 3
	};

}SF;

////�洢Ϊjson��ʽ�ַ�����
string writeFileJson(int equipment_id, int status, double electricity);
//���Ӵ�����
SOCKET linktosensor(const char *ipaddr);
//�������ݸ�������
double sendtosensor(SOCKET sclient, const char* data, int len);
//���Ӻ�̨������
SOCKET linktoserver(const char *ipaddr_server);
//�������ݸ���̨������
int sendtoserver(SOCKET scl, const char *data, int rx, int status, double electricity);

////��������ȡ����
SF sensorFun(const char* sensor_ip, const char* txdata);
//������д�뵽 FILE_NAME �ļ���
int WriteFile(const char* data);
//�Ѵ��������ص�����д�뵽log�ļ���
int datatoFile(int equipment_id, int status, double electricity);
//���Ӳ��������ݸ���̨������
int serverFun(const char* server_ip, int equipment_id, int status, double electricity);

int judgeFile(void);
