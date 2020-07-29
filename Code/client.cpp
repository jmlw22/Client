#include "main.h"

//连接传感器，参数ipaddr为传感器所对应的IP地址
SOCKET linktosensor(const char *ipaddr)
{
    int ret = 0;
    SOCKET sclient;
    sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //客户端套接字
    if (sclient == INVALID_SOCKET)
    {
        printf("invalid socket!\n");
        return -1;
    }

    sockaddr_in serAddr;
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(IP_PORT); //监听端口
    inet_pton(AF_INET, ipaddr, (void*)&serAddr.sin_addr.S_un.S_addr);
    if (connect(sclient, (sockaddr*)&serAddr, sizeof(serAddr)) == SOCKET_ERROR) //与指定IP地址和端口的服务端连接
    {
        printf("connect %s error !", ipaddr);
        closesocket(sclient);
        return 0;
    }
    else
    {
        std::cout << "connect "<< ipaddr << " success !" << endl;
    }

	return sclient;
}

//把数据发送到传感器。参数SOCKET sclient：所连接的端口，const char *data：发送的数据，len：发送数据的长度
double sendtosensor(SOCKET sclient, const char *data, int len )
{
    int ret ; 
    //double current = 1.001;
    //数据发送
    send(sclient, data, len, 0); 

    //数据接收
    char recData[255];
    ret = recv(sclient, recData, sizeof(recData), 0);
    //cout << "回传的数据长度：" << ret << endl;
    if (ret > 0)
    {
        // recData[ret] = 0x00;
         printf("The data received is :");
        for (size_t i = 0; i < ret; i++)
        {
            printf("%02X  ", recData[i]);
        }
        printf("\n");
    }
    double current = (double)(((recData[5] << 8) | recData[6]) / 1000.0000);
    //printf("\nThe current magnitude is:%4f \n", current);

    closesocket(sclient);

    return current;
}

//连接到后台服务器
SOCKET linktoserver(const char* ipaddr_server)
{
    SOCKET scl;
    sockaddr_in Addr;
    int ret = 0;

    //链接服务器
    scl = socket(AF_INET, SOCK_STREAM, 0); //客户端套接字IPPROTO_TCP
    if (scl == INVALID_SOCKET)
    {
        printf("invalid socket!");
        return 0;
    }

    Addr.sin_family = AF_INET;
    Addr.sin_port = htons(6688); //监听端口
    inet_pton(AF_INET, ipaddr_server, (void*)&Addr.sin_addr.S_un.S_addr);
    if (connect(scl, (sockaddr*)&Addr, sizeof(Addr)) == SOCKET_ERROR) //与指定IP地址和端口的服务端连接
    {
        printf("connect %s error !\n", ipaddr_server);
        closesocket(scl);
        return 0;
    }
    else
    {
        printf("connect %s success!\n", ipaddr_server);
    }

    return scl;
}

//把数据发送到后台服务器
int sendtoserver(SOCKET scl,const char *data,int rx_len, int status, double electricity)
{
    
    int tx, ret = 0;
    //数据发送，参数scl：所发送的连接端，data：发送的数据，256：所发送数据的长度
    tx = send(scl, data, 256, 0);  

    closesocket(scl);
    return ret;
}


