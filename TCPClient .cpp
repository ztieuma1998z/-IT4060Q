#include <stdio.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>

#pragma comment(lib, "ws2_32")

int main(int argc, char* argv[])
{
    // Kiem tra so luong tham so truyen vao co hop le khong
    if (argc != 3) {
        printf("So luong tham so truyen vao khong hop le");
        exit(1);
    }
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

   
   
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]); 
    addr.sin_port = htons((unsigned short)strtoul(argv[2], NULL, 0));

    system("pause");

    int ret = connect(client, (SOCKADDR*)&addr, sizeof(addr));
    if (ret == SOCKET_ERROR)
    {
        ret = WSAGetLastError();
        printf("Connect failed: %d\n", ret);
        return 1;
    }
    ////Nhan loi chao tu server
    char serverReply[256];
    char buf[256];

     //receive data from server
     ret = recv(client, serverReply, sizeof(serverReply), 0);

      // Them ky tu ket thuc xau va in ra man hinh
     if (ret < sizeof(serverReply))
       serverReply[ret] = 0;
       printf("Received: %s\n", serverReply);


    //send message to server
     while (1) {
       printf("Nhap vao tin nhan ban muon gui\n");
       gets_s(buf, sizeof(buf));

       send(client, buf, strlen(buf), 0);

       if (strcmp(buf, "exit") == 0)
           break;
       }
   
    closesocket(client);
    WSACleanup();
}