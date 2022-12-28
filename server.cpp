#include <stdio.h>
#include <iostream>
#include <winsock2.h>
// #include <pthread.h>
#include <windows.h>
#include <process.h>
#include <stdlib.h>
#include <string>
#include <cstring>

#pragma comment(lib, "ws2_32.lib")


#define BUF_SIZE 100
#define MAX_CLNT 256

unsigned __stdcall handle_clnt(void* arg);
void send_msg(char* msg, int len);
void error_handling(char* msg);
void server_state(char* port);
int clnt_cnt = 0;
SOCKET clnt_socks[MAX_CLNT];
// pthread_mutex_t mutx;

#define PORT 4578
#define PACKET_SIZE 1024

int main(int argc, char* argv[]){
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2), &wsaData);

    SOCKET serv_sock, clnt_sock;

    SOCKADDR_IN serv_addr;
    SOCKADDR_IN clnt_addr;
    int clnt_addr_size;
    HANDLE hThread;
    DWORD wr;
    unsigned threadID;
    // pthread_t t_id;

    server_state((char*)"4578");
    // server_state(argv[1]);
    // if(argc != 2){
    //     std::cout << "Hello" << std::endl;
    //     std::cout << "Usage: " << argv[0] << "<port>" << std::endl;
    //     exit(1);
    // }

    // pthread_mutex_init(&mutx, NULL);
    serv_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(serv_sock == -1) 
        error_handling((char*)"socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);

    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))== -1) 
        error_handling((char*)"bind() error");

    if(listen(serv_sock,5)==-1)
        error_handling((char*)"Listen() error");

    while(1){
        clnt_addr_size = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_addr, &clnt_addr_size);
        if(clnt_sock == -1)
            error_handling((char*)"accept() error");
        
        // pthread_mutex_lock(&mutx);
        clnt_socks[clnt_cnt++] = clnt_sock;

        hThread = (HANDLE)_beginthreadex(NULL, 0,handle_clnt, (void*) &clnt_sock, 0, &threadID);
        if(HTREDUCE == 0){
            error_handling((char*)"_beginthreadex() error");
        }
        if((wr=WaitForSingleObject(hThread, INFINITE))==WAIT_FAILED){
            error_handling((char*)"thread wait error");
        }
        // pthread_mutex_unlock(&mutx);

        // pthread_create(&t_id, NULL, handle_clnt,(void*) &clnt_sock);

        // pthread_detach(t_id);
        std::cout << "Connected client IP: " << inet_ntoa(clnt_addr.sin_addr);
        // std::cout << "(" << timeLog->tm_year+1900 << "-" 
        // << timeLog->tm_mon + 1 << "-" << timeLog->tm_mday << "-" 
        // << timeLog->tm_hour << "-" << timeLog->tm_min << ")" <<  std::endl;
        std::cout << "chatter (" << clnt_cnt << "/" << MAX_CLNT << ")\n";
    }
    closesocket(serv_sock);
    WSACleanup();

    return 0;

    // SOCKET hListen;
    // hListen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    // SOCKADDR_IN tListenAddr = {};
    // tListenAddr.sin_family = AF_INET;
    // tListenAddr.sin_port - htons(PORT);
    // tListenAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // bind(hListen, (SOCKADDR*)&tListenAddr, sizeof(tListenAddr));
    // listen(hListen, SOMAXCONN);

    // SOCKADDR_IN tClntAddr = {};
    // int iClntSize = sizeof(tClntAddr);
    // SOCKET hClient = accept(hListen, (SOCKADDR*)&tClntAddr, &iClntSize);

    // char cBuffer[PACKET_SIZE] = {};
    // recv(hClient,cBuffer, PACKET_SIZE, 0);
    // printf("Recv Msg: %s\n", cBuffer);

    // char cMsg[] = "Server Send";
    // send(hClient, cMsg, strlen(cMsg), 0);

    // closesocket(hClient);
    // closesocket(hListen);

    // return 0;
}


void server_state(char* port)
{
    using std::cout;
    using std::endl;
    using std::string;
    cout << "Server Port : " << port << endl;
    cout << "Server State : " << clnt_cnt << " / " << MAX_CLNT << endl;
    cout << endl;
}


unsigned __stdcall handle_clnt(void* arg)
{        
    int clnt_sock=*((int*)arg);
    int str_len=0,i;
    char msg[BUF_SIZE];

    while((str_len=recv(clnt_sock, msg, sizeof(msg),0))!=0)
        send_msg(msg, str_len);

    // pthread_mutex_lock(&mutx);
    for(i=0; i<clnt_cnt; i++) //remove disconnected client
    {
        if(clnt_sock==clnt_socks[i])
        {
            while(i++<clnt_cnt-1)
                clnt_socks[i]=clnt_socks[i+1];
            break;
        }
    }
    clnt_cnt--;
    // pthread_mutex_unlock(&mutx);
    closesocket(clnt_sock);
    return 0;
}

void send_msg(char *msg, int len) // send to all
{
        int i;
        // pthread_mutex_lock(&mutx);
        for(i=0; i<clnt_cnt; i++)
                send(clnt_socks[i], msg, len, 0);
        // pthread_mutex_unlock(&mutx);
}
void error_handling(char* msg)
{
        fputs(msg, stderr);
        fputc('\n', stderr);
        exit(1);
}
