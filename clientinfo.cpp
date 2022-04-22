#include <stdio.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <windows.h>

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

    //name
    char name[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(name) / sizeof(name[0]);
    GetComputerNameA(name, &size);
    //logicaldrives
    char szLogicalDrives[MAX_PATH] = {};
    DWORD dwResult = GetLogicalDriveStringsA(MAX_PATH, szLogicalDrives);
    //disk_size
    unsigned long Sectors,Bytes, Freec, Totalc;
    GetDiskFreeSpaceA("C:\\", &Sectors, &Bytes, &Freec, &Totalc);


    INFO info;
    strcpy(info.name,name);
    info.sectors = Sectors;
    info.bytes = Bytes;
    info.freec = Freec;
    info.totalc = Totalc;

    send(client, (char*)&info, sizeof(info), 0);


    closesocket(client);
    WSACleanup();
}