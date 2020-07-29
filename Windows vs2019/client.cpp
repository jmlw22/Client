#include "main.h"

//连接传感器，参数ipaddr为传感器所对应的IP地址
MT linktosensor(const char *ipaddr)
{
    int ret = 0; 
    MT sclient;

    //设置超时时间
    struct timeval timeout = { 3,0 };
    //timeout.tv_sec = 10;
    //timeout.tv_usec = 0;

    sockaddr_in serAddr;
    memset(&serAddr, 0, sizeof(serAddr));

    sclient.sensorclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //客户端套接字
    if (sclient.sensorclient == INVALID_SOCKET)
    {
        printf("invalid linktosensor socket!\n");
        exit(-1);
    }

    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(IP_PORT); //监听端口
    serAddr.sin_addr.s_addr = inet_addr(ipaddr);
    inet_pton(AF_INET, ipaddr, (void*)&serAddr.sin_addr.S_un.S_addr);
    
    unsigned long st = 1;
    int sv = ioctlsocket(sclient.sensorclient, FIONBIO, (unsigned long *)&st);//设置为非阻塞SOCKET
    //cout << "sv = " << sv << endl;

    int confd = connect(sclient.sensorclient, (sockaddr*)&serAddr, sizeof(serAddr));
    //cout << "confd = " << confd << endl;
    //if (confd == SOCKET_ERROR) //与指定IP地址和端口的服务端连接
    //{
    //      //::closesocket(sclient);
    //     //return sclient;
    //     //printf("connect %s error !\n", ipaddr);
    //    //closesocket(sclient);
    //    return sclient;
    //}

    fd_set r;
    FD_ZERO(&r);
    FD_SET(sclient.sensorclient, &r);
    ret = select(0, 0, &r, 0, &timeout);
    if (ret <= 0)
    {

        sclient.key = -1;
        printf("connect %s error !\n", ipaddr);
        closesocket(sclient.sensorclient);
        return sclient;
    }
    else
    {
        std::cout << "connect "<< ipaddr << " success !" << endl;
    }

    //设置为阻塞状态
    Sleep(20);
    st = 0;
    ret = ioctlsocket(sclient.sensorclient, FIONBIO, (unsigned long*)&st);

	return sclient;
}

//把数据发送到传感器。参数SOCKET sclient：所连接的端口，const char *data：发送的数据，len：发送数据的长度
SF sendtosensor(SOCKET sclient, const char *data, int len )
{
    //int nNetTimeout = 2000ms;
    SF mystatustime;
    int ret;

    //数据发送
    //send(sclient, data, len, MSG_DONTROUTE);
    int timeout = 3000;//超时时间，单位为微妙
    if (::setsockopt(sclient,SOL_SOCKET,SO_SNDTIMEO,(char *)&timeout,sizeof(timeout))==SOCKET_ERROR)
    {
        cout << "sendtosensor timeout" << endl;       
    }

    
    ret = send(sclient, data, len, 0); 
    //cout << "send ret = " << ret << endl;

    //数据接收
    char recData[1024] = {0};
    timeout = 3000;//超时时间，单位为微妙
    int to = setsockopt(sclient, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
    if (to == SOCKET_ERROR)
    {
        //cout << " recieved timeout" << endl;
        printf("recieved timeout\n");    
    }

    //cout << "sizeof(recData) = " << sizeof(recData) << endl;
    ret = recv(sclient, recData, sizeof(recData), 0);
    //cout << "recv ret = " << ret << endl;

    DWORD dwerro = WSAGetLastError();
    //cout << "dwerro = " << dwerro << endl;
    if (dwerro == 10060)//由于连接方在一段时间后没有正确的答复或连接的主机没有反应，连接尝试失败。
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
    mystatustime.electricity = (double)(((rxdt[5] << 8) | rxdt[6]) / 100.0000);
    //printf("\nThe current magnitude is:%4f \n", current);



    closesocket(sclient);

    return mystatustime;
}

//连接到后台服务器
SOCKET linktoserver(const char* ipaddr_server)
{
    SOCKET scl;
    struct sockaddr_in Addr;
    int ret = 0;
    memset(&Addr, 0, sizeof(Addr));
    socklen_t addrlen = sizeof(sockaddr);

    //连接服务器
    scl = socket(AF_INET, SOCK_STREAM, 0); //客户端套接字IPPROTO_TCP
    if (scl == INVALID_SOCKET)
    {
        printf("invalid %s socket!\n", ipaddr_server);
        closesocket(scl);
        return 0;
    }

    //设置为非阻塞状态
    unsigned long st = 1;
    ret = ioctlsocket(scl, FIONBIO, (unsigned long*)&st);

    fd_set r;
    FD_ZERO(&r);
    FD_SET(scl, &r);
    //设置超时时间
    struct timeval timeout = { 3,0 };

    Addr.sin_family = AF_INET;
    Addr.sin_port = htons(6688); //监听端口
    inet_pton(AF_INET, ipaddr_server, (void*)&Addr.sin_addr.S_un.S_addr);
    ret = connect(scl, (sockaddr*)&Addr, sizeof(Addr));//与指定IP地址和端口的服务端连接   SOCKET_ERROR
    //cout << "linktoserver ret = " << ret << endl;
    //DWORD dwerro = WSAGetLastError();
    //cout << "linktoserver dwerro = " << dwerro << endl;
    ret = select(0, 0, &r, 0, &timeout);
    if (ret <= 0)
    {
        printf("connect %s error !\n", ipaddr_server);
        //设置为阻塞状态
        Sleep(20);
        st = 0;
        ret = ioctlsocket(scl, FIONBIO, (unsigned long*)&st);
        //closesocket(scl);
        return 0;
    }
    else
    {
        std::cout << "connect " << ipaddr_server << " success !" << endl;
    }

    //设置为阻塞状态
    Sleep(20);
    st = 0;
    ret = ioctlsocket(scl, FIONBIO, (unsigned long*)&st);


    return scl;
}

//把数据发送到后台服务器
int sendtoserver(SOCKET scl,const char *data,int rx_len, int status, double electricity)
{
    int tx, ret = 0;
    int timeout = 3000;//超时时间，单位为微妙
    if (::setsockopt(scl, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, sizeof(timeout)) == SOCKET_ERROR)
    {
        cout << "sendtoserver send timeout" << endl;
    }
    
    //cout << "strlen(data) = " << strlen(data) << endl;//发送的数据长度查看
    //数据发送，参数scl：所发送的连接端，data：发送的数据，256：所发送数据的长度
    cout << "send to server data is " << data;
    tx = send(scl, data, 256, 0);  

 
    closesocket(scl);
    return ret;
}

//连接到后台服务器
DWORD linkserver(const char* ipaddr_server)
{
    SOCKET scl;
    sockaddr_in Addr;
    int ret = 0;
    memset(&Addr, 0, sizeof(Addr));

    //链接服务器
    scl = socket(AF_INET, SOCK_STREAM, 0); //客户端套接字IPPROTO_TCP
    if (scl == INVALID_SOCKET)
    {
        printf("invalid %s socket!\n", ipaddr_server);
        return 0;
    }
    //设置为非阻塞状态
    unsigned long st = 1;
    ret = ioctlsocket(scl, FIONBIO, (unsigned long*)&st);

    Addr.sin_family = AF_INET;
    Addr.sin_port = htons(6688); //监听端口
    inet_pton(AF_INET, ipaddr_server, (void*)&Addr.sin_addr.S_un.S_addr);
    ret = connect(scl, (sockaddr*)&Addr, sizeof(Addr));//与指定IP地址和端口的服务端连接
    //cout << "linkserver ret = " << ret << endl;

    fd_set r;
    FD_ZERO(&r);
    FD_SET(scl, &r);
    //设置超时时间
    struct timeval timeout = { 3,0 };

    DWORD dwerro = WSAGetLastError();
    //cout << "linkserver dwerro = " << dwerro << endl;

    ret = select(0, 0, &r, 0, &timeout);
    if (ret <= 0)
    {
        //printf("linkserver connect %s error !\n", ipaddr_server);
        //设置为阻塞状态
        Sleep(20);
        st = 0;
        ret = ioctlsocket(scl, FIONBIO, (unsigned long*)&st);
        closesocket(scl);
        return dwerro;
    }
    //else
    //{
    //    std::cout << "connect " << ipaddr_server << " success !" << endl;
    //}

    //设置为阻塞状态
    Sleep(20);
    st = 0;
    ret = ioctlsocket(scl, FIONBIO, (unsigned long*)&st);
    closesocket(scl);

    return 0;
}
