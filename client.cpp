#include <WinSock2.h>
#include <iostream>
#pragma comment (lib , "ws2_32.lib")
 
void showError(const char * msg)
{
            std ::cout << "error : " << msg << std ::endl;
            exit (-1);
}
 
int main()
{
    WSADATA data;
    ::WSAStartup( MAKEWORD(2, 2), &data);

    SOCKET client = socket (AF_INET , SOCK_STREAM, IPPROTO_TCP);

    if (client == INVALID_SOCKET )
        showError ("client" );

    sockaddr_in addr = { 0 };
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr. s_addr =inet_addr("127.0.0.1");
    addr.sin_port = htons(4578);
    if (connect(client, (sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR )
        showError ("connect" );
    char msg[100] = "";
    strcat(msg, "hello");
    if(send(client, msg, 6, 0) == SOCKET_ERROR)
        std::cout << "send error" << std::endl;
    int i = 1;
    while(i == 1){
        std::cin >> msg;
        if(strcmp(msg ,"q")==0 ){
            std::cout << "nooo" << std::endl;
            break;
        }
        
        if(send(client, msg, 6, 0) == SOCKET_ERROR){
            std::cout << "send error" << std::endl;
            break;
        }
    }
    std::cout << "end" << std::endl;

    closesocket (client);
    WSACleanup();
    return 0;
}