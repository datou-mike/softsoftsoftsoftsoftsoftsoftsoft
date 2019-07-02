/*
wasstartup()-socket()-bind()-listen()-accept()-send()/recv()-closesocket()-wacclenup()
*/
#include<stdio.h>
#include<winsock2.h>
#include<time.h>
#include<stdlib.h>
#include <windows.h>
#include<iostream>
using namespace std;
#pragma comment (lib, "ws2_32")

void sendMg(SOCKET sclent1)
{
	char szmsg[MAXBYTE] = { 0 };

	while (1){
		cin >> szmsg;
		cout << szmsg;
		//lstrcpy(szmsg, "hello\r\n");
		send(sclent1, szmsg, strlen(szmsg) + sizeof(char), 0);
		memset(szmsg, 0, strlen(szmsg));
		Sleep(1000);
		//system("pasue");
	}
}

void recMg(SOCKET sclent2)
{
	char Rszmsg[MAXBYTE] = { 0 };
	while (1)
	{
		recv(sclent2, Rszmsg, MAXBYTE, 0);
		printf("clent msg: %s\r\n", Rszmsg);
		Sleep(500);
	}
	memset(Rszmsg, 0, strlen(Rszmsg));

}

/*
int main()
{
	WSADATA wsadata;//struct WSAData
	WSAStartup(MAKEWORD(2, 2), &wsadata);
	//create socket
	SOCKET Listent = socket(PF_INET,SOCK_STREAM, IPPROTO_TCP);

	struct sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = htons(1234);

	bind(Listent, (SOCKADDR *)&serveraddr, sizeof(serveraddr));

	listen(Listent,SOMAXCONN);

	sockaddr_in clientaddr;
	int nsize = sizeof(clientaddr);

	SOCKET sclent = accept(Listent, (SOCKADDR *)&clientaddr, &nsize);

	printf("clientIP=%s:%d\r\n", inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));

	HANDLE Thread1, Thread2;
	//sendMg(sclent);

	//Thread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)sendMg, (LPVOID)sclent, 0, NULL);
	
	/*
	char szmsg[MAXBYTE] = { 0 };
	while (1){
		lstrcpy(szmsg, "hello\r\n");
		send(sclent, szmsg, strlen(szmsg) + sizeof(char), 0);
		memset(szmsg, 0, strlen(szmsg));
		printf(szmsg);
		Sleep(1000);
	}
	*/
	
	//receive
	//char Rszmsg[MAXBYTE] = { 0 };
	//recv(sclent, Rszmsg, MAXBYTE, 0);
	//printf("clent msg: %s\r\n", Rszmsg);

	//pthread.pthread_t tids[2];
	//recMg(sclent);	

	//Thread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)recMg, (LPVOID)sclent, 0, NULL);
	//WSACleanup();
	//system("pause");
	//return 0;
//}

