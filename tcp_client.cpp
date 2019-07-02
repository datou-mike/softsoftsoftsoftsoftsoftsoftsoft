/*
wsastartup()-socket()-connect()-send()/recv()-closesocket()-wsaclenup()
*/
#include<stdio.h>
#include<winsock2.h>
#pragma comment(lib,"ws2_32")
#include<stdlib.h>
#include<time.h>
#include<iostream>
using namespace std;


void recvMg(SOCKET CListent1)
{
	char szmsg1[MAXBYTE] = { 0 };
	while (1)
	{
		recv(CListent1, szmsg1, MAXBYTE, 0);
		printf("sercer msg: %s \r\n", szmsg1);
		memset(szmsg1, 0, strlen(szmsg1));
		Sleep(500);
	}

}


void sendMg(SOCKET CListent2)
{
	char Rszmsg[MAXBYTE] = { 0 };
	while (1)
	{
		cin >> Rszmsg;
		//lstrcpy(Rszmsg, "world\r\n");
		send(CListent2, Rszmsg, strlen(Rszmsg) + sizeof(char), 0);
		memset(Rszmsg, 0, strlen(Rszmsg));
		//system("pause");
		Sleep(500);
	}
}

int main()
{
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2,2),&wsadata);

	SOCKET CListent = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = htons(1234);


	connect(CListent, (SOCKADDR *)&serveraddr,sizeof(serveraddr));
	//recvMg(CListent);
	sendMg(CListent);
	HANDLE Thread3, Thread4;
	//sendMg(CListent);
	//Thread3 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)recvMg, (LPVOID)CListent, 0, NULL);
	//Thread4 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)sendMg, (LPVOID)CListent, 0, NULL);

	WSACleanup();
	
	return 0;
}