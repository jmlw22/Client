#include "main.h"

int main(int argc, char* argv[])
{
    //�����ṹ��������
    SF st;

    //��ʼ��WSA windows�Դ���socket
    WORD sockVersion = MAKEWORD(2, 2);
    WSADATA data;
    if (WSAStartup(sockVersion, &data) != 0)
    {
        printf("WSAStartup error!!\n");
        return 0;
    }

    while (true)
    {
        
        //����ipΪipaddr_gy�Ĵ���������ȡ���ݣ����͸�����������ΪsendData6
        st = sensorFun(ipaddr_gy,sendData5);
        //�Ѵ��������ص�����д�뵽log�ļ���
        datatoFile(st.id, st.status, st.electricity);
        //���Ӳ��������ݸ���̨������
        serverFun(ipaddr_server, st.id, st.status, st.electricity);
        //��ʱ����
        Sleep(100);

        //����ipΪipaddr_gy�Ĵ���������ȡ���ݣ����͸�����������ΪsendData6
        st = sensorFun(ipaddr_gy, sendData7);
        //�Ѵ��������ص�����д�뵽log�ļ���
        datatoFile(st.id, st.status, st.electricity);
        //���Ӳ��������ݸ���̨������
        serverFun(ipaddr_server, st.id, st.status, st.electricity);
        //��ʱ����
        Sleep(100);
        //judgeFile();
        //Sleep(5000);

        //����ipΪipaddr_gy�Ĵ���������ȡ���ݣ����͸�����������ΪsendData6
        st = sensorFun(ipaddr_gy, sendData8);
        //�Ѵ��������ص�����д�뵽log�ļ���
        datatoFile(st.id, st.status, st.electricity);
        //���Ӳ��������ݸ���̨������
        serverFun(ipaddr_server, st.id, st.status, st.electricity);
        //��ʱ����
        Sleep(100);

        //����ipΪipaddr_gy�Ĵ���������ȡ���ݣ����͸�����������ΪsendData6
        st = sensorFun(ipaddr_gy, sendData9);
        //�Ѵ��������ص�����д�뵽log�ļ���
        datatoFile(st.id, st.status, st.electricity);
        //���Ӳ��������ݸ���̨������
        serverFun(ipaddr_server, st.id, st.status, st.electricity);
        //��ʱ����
        Sleep(3000); 
        system("cls");
    }

	system("pause");
	return 0;
}


//��������ȡ����
SF sensorFun(const char *sensor_ip,const char *txdata)
{

    int status = 0;
    double electricity;
    int len = sizeof(sendData8);
    SF sensor;
    SOCKET sclient;


    //���Ӵ������������� 
    sclient = linktosensor(sensor_ip);
    if (sclient == 0)
    {
        sensor.status = -1;
        sensor.electricity = 999.999;
        
    }
    else
    {
        //�������ݵ��������������ص���ֵ�Ĵ�С  double sendtosensor(SOCKET sclient, const char *data, int len )
        electricity = sendtosensor(sclient, txdata, len);

        //status ״̬��1Ϊ������2Ϊ�ػ�
        if (electricity > COM_VALUE || electricity < 0)
        {
            status = sensor.on;
            //cout << "status = " << status << "  ===��Current device startup" << endl;
        }
        else
        {
            status = sensor.off;
            //cout << "status = " << status << "  ===��Current device shutdown" << endl;
        }  

        sensor.status = status;
        sensor.electricity = electricity;
    }

    //cout << "electricity = " << electricity << endl;
    //printf("electricity = %lf\n", sensor.electricity);

    sensor.id = txdata[0];

    return sensor;
}

//�Ѵ��������ص�����д�뵽log�ļ���
int datatoFile(int equipment_id, int status, double electricity)
{
    const char* dat;
    string dt;

    //���ݸ�ʽ����
    //writeFileJson(int equipment_id, int status, double electricity);
    dt = writeFileJson(equipment_id, status, electricity);
    //cout << "dt = " << dt;
    dat = dt.c_str();
    //cout << "dat = " << dat << endl;
    //printf("%s\n", dat);
    WriteFile(dat);

    return 0;
}

//�Ѵ��������ص����ݷ��͸���̨
int serverFun(const char *server_ip, int equipment_id, int status, double electricity)
{
    int tx = 0;
    int rx_len = 128;
    const char *dat;
    SOCKET ssclient;
    string dt;

    //���Ӻ�̨������
    ssclient = linktoserver(server_ip);
    dt = writeFileJson(equipment_id, status, electricity);
    cout << dt << endl << endl;
    dat = dt.c_str();
 
    //�������ݵ�������
    //tx = sendtoserver(SOCKET scl,int equipment_id, int status, double electricity);; 
    tx = sendtoserver(ssclient, dat, rx_len, status, electricity);

    return 0;
}

