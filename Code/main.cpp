#include "main.h"

int main(int argc, char* argv[])
{
    //创建结构体存放数据
    SF st;

    //初始化WSA windows自带的socket
    WORD sockVersion = MAKEWORD(2, 2);
    WSADATA data;
    if (WSAStartup(sockVersion, &data) != 0)
    {
        printf("WSAStartup error!!\n");
        return 0;
    }

    while (true)
    {
        
        //连接ip为ipaddr_gy的传感器并获取数据，发送给传感器数据为sendData6
        st = sensorFun(ipaddr_gy,sendData5);
        //把传感器返回的数据写入到log文件中
        datatoFile(st.id, st.status, st.electricity);
        //连接并发送数据给后台服务器
        serverFun(ipaddr_server, st.id, st.status, st.electricity);
        //延时两秒
        Sleep(100);

        //连接ip为ipaddr_gy的传感器并获取数据，发送给传感器数据为sendData6
        st = sensorFun(ipaddr_gy, sendData7);
        //把传感器返回的数据写入到log文件中
        datatoFile(st.id, st.status, st.electricity);
        //连接并发送数据给后台服务器
        serverFun(ipaddr_server, st.id, st.status, st.electricity);
        //延时两秒
        Sleep(100);
        //judgeFile();
        //Sleep(5000);

        //连接ip为ipaddr_gy的传感器并获取数据，发送给传感器数据为sendData6
        st = sensorFun(ipaddr_gy, sendData8);
        //把传感器返回的数据写入到log文件中
        datatoFile(st.id, st.status, st.electricity);
        //连接并发送数据给后台服务器
        serverFun(ipaddr_server, st.id, st.status, st.electricity);
        //延时两秒
        Sleep(100);

        //连接ip为ipaddr_gy的传感器并获取数据，发送给传感器数据为sendData6
        st = sensorFun(ipaddr_gy, sendData9);
        //把传感器返回的数据写入到log文件中
        datatoFile(st.id, st.status, st.electricity);
        //连接并发送数据给后台服务器
        serverFun(ipaddr_server, st.id, st.status, st.electricity);
        //延时三秒
        Sleep(3000); 
        system("cls");
    }

	system("pause");
	return 0;
}


//传感器获取数据
SF sensorFun(const char *sensor_ip,const char *txdata)
{

    int status = 0;
    double electricity;
    int len = sizeof(sendData8);
    SF sensor;
    SOCKET sclient;


    //连接传感器请求数据 
    sclient = linktosensor(sensor_ip);
    if (sclient == 0)
    {
        sensor.status = -1;
        sensor.electricity = 999.999;
        
    }
    else
    {
        //发送数据到传感器，并返回电流值的大小  double sendtosensor(SOCKET sclient, const char *data, int len )
        electricity = sendtosensor(sclient, txdata, len);

        //status 状态，1为开机，2为关机
        if (electricity > COM_VALUE || electricity < 0)
        {
            status = sensor.on;
            //cout << "status = " << status << "  ===》Current device startup" << endl;
        }
        else
        {
            status = sensor.off;
            //cout << "status = " << status << "  ===》Current device shutdown" << endl;
        }  

        sensor.status = status;
        sensor.electricity = electricity;
    }

    //cout << "electricity = " << electricity << endl;
    //printf("electricity = %lf\n", sensor.electricity);

    sensor.id = txdata[0];

    return sensor;
}

//把传感器返回的数据写入到log文件中
int datatoFile(int equipment_id, int status, double electricity)
{
    const char* dat;
    string dt;

    //数据格式处理
    //writeFileJson(int equipment_id, int status, double electricity);
    dt = writeFileJson(equipment_id, status, electricity);
    //cout << "dt = " << dt;
    dat = dt.c_str();
    //cout << "dat = " << dat << endl;
    //printf("%s\n", dat);
    WriteFile(dat);

    return 0;
}

//把传感器返回的数据发送给后台
int serverFun(const char *server_ip, int equipment_id, int status, double electricity)
{
    int tx = 0;
    int rx_len = 128;
    const char *dat;
    SOCKET ssclient;
    string dt;

    //连接后台服务器
    ssclient = linktoserver(server_ip);
    dt = writeFileJson(equipment_id, status, electricity);
    cout << dt << endl << endl;
    dat = dt.c_str();
 
    //发送数据到服务器
    //tx = sendtoserver(SOCKET scl,int equipment_id, int status, double electricity);; 
    tx = sendtoserver(ssclient, dat, rx_len, status, electricity);

    return 0;
}

