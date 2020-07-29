#include "main.h"

int main(int argc, char const *argv[])
{

	SF st;
	system("mkdir  ./log/");

	while(1)
	{

		#ifdef SPT
        //创建结构体存放数据
        SF st;
        //连接ip为ipaddr_gy的传感器并获取数据，发送给传感器数据为sendData8
        st = sensorFun(ipaddr8, ipaddr_server, sendData8);
        //连接并发送数据给后台服务器
        serverFun(ipaddr_server, st.id, st.status, st.electricity);
        //把传感器返回的数据写入到log文件中
        datatoFile(st.id, st.status, st.electricity);
        //延时两秒
        usleep(500);;


        //连接ip为ipaddr_gy的传感器并获取数据，发送给传感器数据为sendData*
        st = sensorFun(ipaddr12, ipaddr_server, sendData12);
        //连接并发送数据给后台服务器
        //serverFun(ipaddr_server, st.id, st.status, st.electricity);
        //把传感器返回的数据写入到log文件中
        datatoFile(st.id, st.status, st.electricity);
        //延时两秒
        usleep(500);

        //连接ip为ipaddr_gy的传感器并获取数据，发送给传感器数据为sendData*
        st = sensorFun(ipaddr29, ipaddr_server, sendData29);
        //连接并发送数据给后台服务器
        serverFun(ipaddr_server, st.id, st.status, st.electricity);
        //把传感器返回的数据写入到log文件中
        datatoFile(st.id, st.status, st.electricity);
        //延时两秒
        usleep(500);

        //连接ip为ipaddr_gy的传感器并获取数据，发送给传感器数据为sendData*
        st = sensorFun(ipaddr31, ipaddr_server, sendData31);
        //连接并发送数据给后台服务器
        serverFun(ipaddr_server, st.id, st.status, st.electricity);
        //把传感器返回的数据写入到log文件中
        datatoFile(st.id, st.status, st.electricity);
        //延时三秒
        usleep(500);

        //连接ip为ipaddr_spt的传感器并获取数据，发送给传感器数据为sendData*
        st = sensorFun(ipaddr32, ipaddr_server, sendData32);
        //连接并发送数据给后台服务器
        serverFun(ipaddr_server, st.id, st.status, st.electricity);
        //把传感器返回的数据写入到log文件中
        datatoFile(st.id, st.status, st.electricity);
        //延时两秒
        usleep(500);

        //连接ip为ipaddr_spt的传感器并获取数据，发送给传感器数据为sendData*
        st = sensorFun(ipaddr30, ipaddr_server, sendData30);
        //连接并发送数据给后台服务器
        serverFun(ipaddr_server, st.id, st.status, st.electricity);
        //把传感器返回的数据写入到log文件中
        datatoFile(st.id, st.status, st.electricity);
        //延时两秒
        usleep(500);

        //连接ip为ipaddr_spt的传感器并获取数据，发送给传感器数据为sendData*
        st = sensorFun(ipaddr23, ipaddr_server, sendData23);
        //连接并发送数据给后台服务器
        serverFun(ipaddr_server, st.id, st.status, st.electricity);
        //把传感器返回的数据写入到log文件中
        datatoFile(st.id, st.status, st.electricity);
        //延时两秒
        usleep(500);

        //连接ip为ipaddr_spt的传感器并获取数据，发送给传感器数据为sendData*
        st = sensorFun(ipaddr33, ipaddr_server, sendData33);
        //连接并发送数据给后台服务器
        serverFun(ipaddr_server, st.id, st.status, st.electricity);
        //把传感器返回的数据写入到log文件中
        datatoFile(st.id, st.status, st.electricity);
        //延时两秒
        usleep(500);

        //连接ip为ipaddr_spt的传感器并获取数据，发送给传感器数据为sendData*
        st = sensorFun(ipaddr20, ipaddr_server, sendData20);
        //连接并发送数据给后台服务器
        serverFun(ipaddr_server, st.id, st.status, st.electricity);
        //把传感器返回的数据写入到log文件中
        datatoFile(st.id, st.status, st.electricity);
        //延时两秒
        usleep(500);

        //连接ip为ipaddr_spt的传感器并获取数据，发送给传感器数据为sendData*
        st = sensorFun(ipaddr11, ipaddr_server, sendData11);
        //连接并发送数据给后台服务器
        serverFun(ipaddr_server, st.id, st.status, st.electricity);
        //把传感器返回的数据写入到log文件中
        datatoFile(st.id, st.status, st.electricity);
        //延时两秒
        sleep(4);
        system("clear");

        #else
		
		//连接ip为ipaddr_gy的传感器并获取数据，发送给传感器数据为sendData*
		st = sensorFun(ipaddr_gy,ipaddr_server,sendData5);
		//连接并发送数据给后台服务器
        serverFun(ipaddr_server, st.id, st.status, st.electricity);
        //把传感器返回的数据写入到log文件中
		datatoFile(st.id, st.status, st.electricity);
		//延时两秒
		sleep(2);

		//连接ip为ipaddr_gy的传感器并获取数据，发送给传感器数据为sendData*
		st = sensorFun(ipaddr_gy,ipaddr_server,sendData7);
		//连接并发送数据给后台服务器
        serverFun(ipaddr_server, st.id, st.status, st.electricity);
		//把传感器返回的数据写入到log文件中
		datatoFile(st.id, st.status, st.electricity);
		//延时两秒
		sleep(2);

		//连接ip为ipaddr_gy的传感器并获取数据，发送给传感器数据为sendData*
		st = sensorFun(ipaddr_gy,ipaddr_server,sendData8);
		//连接并发送数据给后台服务器
        serverFun(ipaddr_server, st.id, st.status, st.electricity);
		//把传感器返回的数据写入到log文件中
		datatoFile(st.id, st.status, st.electricity);
		//延时两秒
		sleep(2);


		//连接ip为ipaddr_gy的传感器并获取数据，发送给传感器数据为sendData*
		st = sensorFun(ipaddr_gy,ipaddr_server,sendData9);
		//连接并发送数据给后台服务器
        serverFun(ipaddr_server, st.id, st.status, st.electricity);
		//把传感器返回的数据写入到log文件中
		datatoFile(st.id, st.status, st.electricity);
		//延时两秒
		sleep(4);

		system("clear");
		#endif
		
	}

	

	return 0;
}


//传感器获取数据
SF sensorFun(const char *sensor_ip,const char *server_ip, const char *txdata)
{
	int status = 0;
    int ret = 0;
    double electricity;
    int len = sizeof(sendData8);
    SF sensor;
    MT sclient;

    //连接传感器请求数据 
    sclient = linktosensor(sensor_ip);
    if (sclient.key == -1)
    {
        sensor.status = -1;
        sensor.electricity = 999.999;
        close(sclient.sensorclient);
    }
    else
    {
        //发送数据到传感器，并返回电流值的大小  double sendtosensor(SOCKET sclient, const char *data, int len )
        sensor = sendtosensor(sclient.sensorclient, txdata, len);

        //正常状况
         electricity = sensor.electricity;
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
        
        //传感器出故障
        if (-3 == sensor.key)
        {
            status = -3;
            electricity = 777.777;
            sensor.key = 0;
        }

	       //检测是否能够与后台server 进行连接
       int ss = linkserver(server_ip);
       //cout << "linkserver ss = " << ss << endl;
       if (-1 == ss)
       {
           electricity = 888.888;
           status = -2; 
       }
       // close(ss);

        sensor.status = status;
        sensor.electricity = electricity;

    }

    sensor.id = txdata[0];
    //cout << "electricity = " << electricity << endl;
    //printf("electricity = %lf\n", sensor.electricity);

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
    cout  << "write   file  data  is " << dt ;
    //dt += "\n";//数据末端加入\n换行符

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
    int ret = 0;
    int rx_len = 128;
    const char *dat;
 
    //SF serversf ;
    int ssclient;
    string dt(128,0);

    //连接后台服务器
    ssclient = linktoserver(server_ip);

    //printf("serverFun status = %d\n", status);
    dt = writeFileJson(equipment_id, status, electricity);

    //cout << "dt.size = " << dt.size() << endl;
    //dt += "\n";//数据末端加入\n换行符
    //cout << "dt.size = " << dt.size() << endl;
    //cout << dt << endl ;
    dat = dt.c_str();
    
    //cout << "send to server data is "  << dat ;
    //发送数据到服务器
    //tx = sendtoserver(SOCKET scl,int equipment_id, int status, double electricity);; 
    tx = sendtoserver(ssclient, dat, rx_len, status, electricity);

    return ret;
}

