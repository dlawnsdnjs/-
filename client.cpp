#include <WinSock2.h>
#include <iostream>
#pragma comment (lib , "ws2_32.lib")
 
void showError(const char * msg)
{
            std ::cout << "에러 : " << msg << std ::endl;
            exit (-1);
}
 
int main()
{
    WSADATA data;
    ::WSAStartup( MAKEWORD(2, 2), &data);

    SOCKET client = socket (AF_INET , SOCK_STREAM, IPPROTO_TCP);

    if (client == INVALID_SOCKET )
        showError ("클라이언트 생성 실패" );

    sockaddr_in addr = { 0 };
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET ;
    addr.sin_addr. s_addr = inet_addr ("127.0.0.1" );
    addr.sin_port = htons(4578);
    SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(server == -1) std::cout << "socket error" << std::endl;

    if(bind(server,(struct sockaddr*)&addr, sizeof(addr)))
        std::cout << "bind error" << std::endl;

    if (connect( client, (sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR )
        showError ("연결 실패" );
    send(server, "hello", 6, 0);
    Sleep(5000);


    closesocket (client);
    WSACleanup();
    return 0;
}