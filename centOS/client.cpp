#include "main.h"


MT linktosensor (const char *ipaddr)
{
	int ret = 0;
	MT sclient;

	//设置超时时间
	struct timeval timeout = {3,0};

	struct sockaddr_in seraddr;
	memset(&seraddr, 0, sizeof(seraddr));

	//端口设置
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(IP_PORT); //监听端口
    seraddr.sin_addr.s_addr = inet_addr(ipaddr);
    //inet_pton(AF_INET, ipaddr, (void*)&seraddr.sin_addr.S_un.S_addr);

    //创建套接字
 	sclient.sensorclient = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);//IPPROTO_TCP
	if (-1 == sclient.sensorclient  )
    {
        printf("invalid linktosensor socket error!\n");
        exit(-1);
    }  

    //设置非阻塞模式
    unsigned long st = 1;
    // int sv = ioctl(sclient.sensorclient, F_GETFL, (unsigned long *)&st);//Windows为：ioctlsocket; linux :fcntl
    // cout << "sv = " << sv << endl;
    int flags = fcntl(sclient.sensorclient, F_GETFL, 0);
    fcntl(sclient.sensorclient, flags|O_NONBLOCK);


    int confd = connect(sclient.sensorclient, (sockaddr*)&seraddr, sizeof(seraddr));
    //cout << "confd = " << confd << endl; //不论是否能连接得上，非阻塞的confd返回值都是 -1

    fd_set r;
    FD_ZERO(&r);
    FD_SET(sclient.sensorclient, &r);
    ret = select(sclient.sensorclient+1, NULL, &r, NULL, &timeout);//非阻塞通过ret 返回值来判断是否能够连接得上 ，连接上ret=1，连接不上 ret=0
    //cout << "linktosensor ret = " << ret << endl;
    if (ret <= 0)
    {

        sclient.key = -1;
        printf("connect %s error !\n", ipaddr);
        close(sclient.sensorclient);
        return sclient;
    }
    else
    {
        printf("connect %s success \n",ipaddr);
    }


    //设置为阻塞状态
    usleep(100);
    st = 0;
    ret = ioctl(sclient.sensorclient, FIONBIO, (unsigned long*)&st);

	//cout << "linktosensor sclient = " << sclient.sensorclient << endl;

	return sclient;
}


//把数据发送到传感器。参数SOCKET sclient：所连接的端口，const char *data：发送的数据，len：发送数据的长度
SF sendtosensor(int sclient, const char *data, int len )
{
    //int nNetTimeout = 2000ms;
    SF mystatustime;
    int ret;


    //数据发送
    //send(sclient, data, len, MSG_DONTROUTE);
    struct timeval timeout = {3, 0};//超时时间，单位为微妙
    if (::setsockopt(sclient,SOL_SOCKET,SO_SNDTIMEO,(char *)&timeout,sizeof(timeout))== -1)
    {
        cout << "sendtosensor timeout" << endl;       
    }

    //cout << "start send" << endl;
    ret = send(sclient, data, len, 0); //MSG_DONWAIT
    //cout << "send ret = " << ret << endl;

    //数据接收
    char recData[1024] = {0};
    //timeout = {3.5, 0};//超时时间，单位为微妙
    int rt = setsockopt(sclient, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
    //cout << " recieved rt = "  << rt << endl;
    if (rt == -1)
    {
        //cout << " recieved timeout" << endl;
        printf("recieved timeout\n");    
    }

    //cout << "sizeof(recData) = " << sizeof(recData) << endl;
    ret = recv(sclient, recData, sizeof(recData), 0);//MSG_DONWAIT
    //cout << "recv ret = " << ret << endl;

    if (ret == -1)//由于连接方在一段时间后没有正确的答复或连接的主机没有反应，连接尝试失败。
    {
        mystatustime.key = -3;
    }

    //cout << "回传的数据长度：" << ret << endl;
    unsigned char rxdt[64] = { 0 };
    if (ret > 0)
    {
        // recData[ret] = 0x00;
         printf("The data received is :\n");
        for (size_t i = 0; i < ret; i++)
        {
           // printf("%02X  ", recData[i]);
            rxdt[i] = recData[i];
        }
        //printf("\n"); 
        //printf("=========================:\n");
        int len = ret;

        for (size_t i = 0; i < len; i++)
        {
            printf("%02X  ", rxdt[i]);
        }
        printf("\n");
    }
    
    mystatustime.electricity = (double)(((rxdt[5] << 8) | rxdt[6]) / 100.0000);//电流值大小，接收到的电流值大小处理
    //mystatustime.voltage = (double)(((rxdt[7] << 8) | rxdt[8]) / 100.0000); //电压大小
	//mystatustime.power = (double)((rxdt[9] << 8) | rxdt[10]); 	//功率大小
    //printf("The current magnitude is:%4f \n", mystatustime.electricity);


    close(sclient);

    return mystatustime;
}



//连接到后台服务器
int linktoserver(const char* ipaddr_server)
{
    int scl;
    int ret = 0;

	//设置超时时间
	struct timeval timeout = {3,0};
	struct sockaddr_in seraddr;
	memset(&seraddr, 0, sizeof(seraddr));

	//端口设置
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(6688); //监听端口
    seraddr.sin_addr.s_addr = inet_addr(ipaddr_server);
    //inet_pton(AF_INET, ipaddr_server, (void*)&seraddr.sin_addr.S_un.S_addr);

    //创建套接字
 	scl = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);//IPPROTO_TCP
	if (-1 == scl  )
    {
        printf("invalid linktosensor socket error!\n");
        exit(-1);
    }  

    //设置非阻塞模式
    unsigned long st = 1;
    // int sv = ioctl(scl, F_GETFL, (unsigned long *)&st);//Windows为：ioctlsocket; linux :fcntl
    // cout << "sv = " << sv << endl;
    int flags = fcntl(scl, F_GETFL, 0);
    fcntl(scl, flags | O_NONBLOCK);

   //链接服务器
    int confd = connect(scl, (sockaddr*)&seraddr, sizeof(seraddr));
    //cout << "linktoserver confd = " << confd << endl; 

    fd_set r;
    FD_ZERO(&r);
    FD_SET(scl, &r);
    ret = select(scl+1, NULL, &r, NULL, &timeout);
    //cout << "linktoserver ret = " << ret << endl; 
    if (ret <= 0)
    {

        //sclient.key = -1;
        printf("connect %s error !\n", ipaddr_server);
        close(scl);
        return confd;
    }
    else
    {
		printf("connect %s success!\n",ipaddr_server);
    }

    //设置为阻塞状态
    usleep(100);
    st = 0;
    ret = ioctl(scl, FIONBIO, (unsigned long*)&st);

    return scl;
}



//把数据发送到后台服务器
int sendtoserver(int scl,const char *data,int rx_len, int status, double electricity)
{
    int tx, ret = 0;
    int len = strlen(data);
    struct timeval timeout = {3, 0};//超时时间，单位为妙
    if (::setsockopt(scl, SOL_SOCKET, SO_SNDTIMEO,(char *)&timeout, sizeof(timeout))== -1)
    {
        cout << "sendtoserver timeout" << endl;       
    }
    
    //cout << "strlen(data) = " << strlen(data) << endl;//发送的数据长度查看
    //数据发送，参数scl：所发送的连接端，data：发送的数据，256：所发送数据的长度
    cout << "send to server data is " << data;
    tx = send(scl, data, len, 0);  
    //cout << "sendtoserver ret = " << tx  << endl;

 
    close(scl);
    return ret;
}


//连接后台
int linkserver(const char* ipaddr_server)
{
    int scl;
    int ret = 0;

	//设置超时时间
	struct timeval timeout = {3,0};
	struct sockaddr_in seraddr;
	memset(&seraddr, 0, sizeof(seraddr));

	//端口设置
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(6688); //监听端口
    seraddr.sin_addr.s_addr = inet_addr(ipaddr_server);
    //inet_pton(AF_INET, ipaddr_server, (void*)&seraddr.sin_addr.S_un.S_addr);

    //创建套接字
 	scl = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);//IPPROTO_TCP
	if (-1 == scl  )
    {
        printf("invalid linktosensor socket error!\n");
        exit(-1);
    }  

    //设置非阻塞模式
    unsigned long st = 1;
    int flags = fcntl(scl, F_GETFL, 0);
    fcntl(scl, flags|O_NONBLOCK);

   //链接服务器
    int confd = connect(scl, (sockaddr*)&seraddr, sizeof(seraddr));
    //cout << "linktoserver confd = " << confd << endl; 

    fd_set r;
    FD_ZERO(&r);
    FD_SET(scl, &r);
    ret = select(scl+1, NULL, &r, NULL, &timeout);
    //cout << "linkserver ret = " << ret << endl; 
    if (ret <= 0)
    {

        //sclient.key = -1;
        //printf("connect %s error !\n", ipaddr_server);
        close(scl);
        return confd;
    }
    else
    {
		//printf("connect %s success!\n",ipaddr_server);
    }


    close(scl);

    return ret;
}

