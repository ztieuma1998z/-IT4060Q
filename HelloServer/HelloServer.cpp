#include "stdafx.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma warning(disable:4996)
#include "winsock2.h"

int main(int argc, char** argv)
{
	// define socket
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// define server's address
	SOCKADDR_IN addr;
	// get argument from command line
	if (argc > 1) {
		addr.sin_family = AF_INET;
		printf("Connecting server on IP: %s port: %d \n", (char*)argv[1], atoi((char*)argv[2]));
		addr.sin_addr.s_addr = inet_addr((char*)argv[1]);
		addr.sin_port = htons(atoi((char*)argv[2]));
	}
	else {
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		addr.sin_port = htons(8000);
	}

	bind(listener, (SOCKADDR *)&addr, sizeof(addr));
	listen(listener, 5);

	printf("Waiting for connection...\n");
	SOCKET client = accept(listener, NULL, NULL);

	printf("Found connecttion...\n");
	// read file and send hello
	FILE *f;
	if (argc >= 4)
		f = fopen((char*) argv[3], "rb");
	else 
		f = fopen("C:\\Users\\ASUS\\source\\repos\\-IT4060Q\\HelloServer\\chao.txt", "rb");
	char buf[256];
	int ret;
	while (1)
	{
		ret = fread(buf, 1, sizeof(buf), f);
		if (ret > 0)
			send(client, buf, ret, 0);
		else
			break;
	}
	fclose(f);

	while (1)
	{
		ret = recv(client, buf, sizeof(buf), 0);
		if (ret <= 0)
			break;
		buf[ret] = 0;
		printf("%s\n", buf);
		FILE *fp;
		if(argc >= 5)
			fp = fopen((char*)argv[4], "ab");
		else 
			fp = fopen("c:\\Users\\USER\\source\\repos\\HelloClient\\HelloServer\\client.txt", "ab");
		fwrite(buf, 1, sizeof(char)*ret, fp);
		fclose(fp);
	}

	closesocket(client);

	closesocket(listener);
	WSACleanup();
    return 0;
}

