#include <WinSock2.h>
#include <iostream>
#include <thread>
#pragma comment (lib , "ws2_32.lib")

SOCKET client;
 
void showError(const char * msg)
{
            std ::cout << "errr : " << msg << std ::endl;
            exit (-1);
}

void proc_recv() {
    while(1){
        char buff[100] = "";
        char a;
        recv(client,buff,100,0);
        std::cout << "receved message : " << buff << std::endl;
    }
}

int main()
{
    WSADATA data;
    ::WSAStartup( MAKEWORD(2, 2), &data);

    client = socket (AF_INET , SOCK_STREAM, IPPROTO_TCP);

    if (client == INVALID_SOCKET )
        showError ("client" );

    sockaddr_in addr = { 0 };
    memset(&addr, 0, sizeof(addr));
    char tmp[15];
    std::cout << "ip please : ";
    std::cin >> tmp;
    const char * ip = tmp;
    addr.sin_family = AF_INET;
    addr.sin_addr. s_addr =inet_addr(ip);
    std::cout <<"connecting to "<< ip << std::endl;
    addr.sin_port = htons(4578);
    if (connect(client, (sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR )
        showError ("connect" );
    
    char msg[100] = "";
    strcat(msg, "hello");
    if(send(client, msg, 6, 0) == SOCKET_ERROR)
        std::cout << "send error" << std::endl;
    
    std::thread t1(proc_recv);

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
    t1.join();
    closesocket (client);
    
    WSACleanup();
    return 0;
}