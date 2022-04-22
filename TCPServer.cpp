#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32")
int main(int argc, char* argv[])
{
    // Kiem tra so luong tham so truyen vao co hop le khong
    if (argc != 4) {
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

    //Nếu thành công đọc file chao.txt    
    char greeting[256];
    int ret;
    FILE* fout = fopen(argv[2], "r");
    while (1)
    {
        // send greeting to client
        ret = fread(&greeting,1, sizeof(greeting), fout);
        if (ret <= 0)
            break;

        if (ret < sizeof(greeting))
            greeting[ret] = 0;
        send(client, greeting, ret, 0);
    }
    fclose(fout);


    // Ghi du lieu nhan dc vao file client.txt
    char buf[256];
    int input;
    FILE* fin = fopen(argv[3], "a+");
    while (1) {
        input = recv(client, buf, sizeof(buf), 0);
        if (input <= 0)
            break; 

        if (input < sizeof(buf))
            buf[input] = 0;
        fwrite(buf, 1, input, fin);
        fwrite("\n", 1, 1, fin);
        printf("Received: %s \n", buf);
    }
    fclose(fin);

    system("pause");
    closesocket(client);
    closesocket(listener);
    WSACleanup();
}