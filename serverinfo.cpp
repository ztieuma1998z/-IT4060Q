#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32")

typedef struct {
    char name[30];
    int logic_drive;
    int sectors;
    int bytes;
    int freec;
    int totalc;
}INFO;

int main(int argc, char* argv[])
{
    // Kiem tra so luong tham so truyen vao co hop le khong
    if (argc != 2) {
        printf("So luong tham so truyen vao khong hop le");
        exit(1);
    }
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons((unsigned short)strtoul(argv[1], NULL, 0));

    bind(listener, (SOCKADDR*)&addr, sizeof(addr));
    listen(listener, 5);

    printf("Dang cho ket noi\n");
    SOCKET client = accept(listener, NULL, NULL);
    printf("Chap nhan ket noi: %d\n", client);

    INFO info;
    recv(client, (char*)&info, sizeof(info), 0);

    printf("Ten thiet bi la: %s\n", info.name);
    printf("So sectors la: %d\n", info.sectors);
    printf("So bytes la: %d\n", info.bytes);
    printf("Con lai trong C la: %d\n", info.freec);
    printf("Tong so trong C la: %d\n", info.totalc);

    closesocket(client);
    closesocket(listener);
    WSACleanup();
}