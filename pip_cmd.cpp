#include<stdio.h>
#include<windows.h>
#include<iostream>
using namespace std;

//int pipCmd()
int main()
{
	//定义四个句柄
	HANDLE hRead1, hWrite1, hRead2, hWrite2;
	SECURITY_ATTRIBUTES sat;
	STARTUPINFO startupinfo;
	PROCESS_INFORMATION pinfo;
	byte buffer[1024];
	DWORD byteRead, byteWrite;
	string sString;
	string m_host = "pip_client_console.exe";//?????rename????
	sat.nLength = sizeof(SECURITY_ATTRIBUTES);
	sat.bInheritHandle = TRUE;
	sat.lpSecurityDescriptor = NULL;

	//create pip，
	
	if (!CreatePipe(&hRead1, &hWrite1, &sat, NULL))
	{
		return 1;
	}
	//创建管道，
	if (!CreatePipe(&hRead2, &hWrite2, &sat, NULL))
	{
		return 1;
	}

	startupinfo.cb = sizeof(STARTUPINFO);
	//用getstartupinfo获取当前进程的参数
	GetStartupInfo(&startupinfo);
	startupinfo.hStdInput = hRead2;
	startupinfo.hStdError = hWrite1;
	startupinfo.hStdOutput = hWrite1;
	startupinfo.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	startupinfo.wShowWindow = SW_HIDE;
	//createprocess，创建一个新进程，执行指定可执行文件，
	//第二个参数是NULL 结尾的字符串，
	if (!CreateProcess(NULL, (char*)m_host.c_str(), NULL, NULL, 
		TRUE, NULL, NULL, NULL, &startupinfo, &pinfo))
	{
		return 1;
	}
	RtlZeroMemory(buffer,1024);
	//wirte hwrite1 and read hread1
	if (ReadFile(hRead1, buffer, 1024, &byteRead, NULL))
	{
		cout << buffer;
	}
	string commandStr = "ipconfig\r\n";
	while (WriteFile(hWrite2, (LPCVOID)commandStr.c_str(), 
		commandStr.length() + 1, &byteWrite, NULL))
	{
		Sleep(1000);
		cout << "wirte" << byteWrite << endl;	
	}
	CloseHandle(hRead1);
	CloseHandle(hRead2);
	CloseHandle(hWrite1);
	CloseHandle(hWrite2);
	return 0;
}




void ShowError(char *pszText)
{
	char szErr[MAX_PATH] = { 0 };
	::wsprintf(szErr, "%s Error[%d]\n", pszText, ::GetLastError());
	::MessageBox(NULL, szErr, "ERROR", MB_OK);
}

// cmd and back
BOOL PipeCmd(char *pszCmd, char *pszResultBuffer, DWORD dwResultBufferSize)
{
	HANDLE hReadPipe = NULL;
	HANDLE hWritePipe = NULL;
	SECURITY_ATTRIBUTES securityAttributes = { 0 };
	BOOL bRet = FALSE;
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };


	securityAttributes.bInheritHandle = TRUE;
	securityAttributes.nLength = sizeof(securityAttributes);
	securityAttributes.lpSecurityDescriptor = NULL;

	
	bRet = ::CreatePipe(&hReadPipe, &hWritePipe, &securityAttributes, 0);
	if (FALSE == bRet)
	{
		ShowError("CreatePipe");
		return FALSE;
	}

	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	si.wShowWindow = SW_HIDE;
	si.hStdError = hWritePipe;
	si.hStdOutput = hWritePipe;

	bRet = ::CreateProcess(NULL, pszCmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
	if (FALSE == bRet)
	{
		ShowError("CreateProcess");
	}

	::WaitForSingleObject(pi.hThread, INFINITE);
	::WaitForSingleObject(pi.hProcess, INFINITE);

	::RtlZeroMemory(pszResultBuffer, dwResultBufferSize);
	::ReadFile(hReadPipe, pszResultBuffer, dwResultBufferSize, NULL, NULL);

	::CloseHandle(pi.hThread);
	::CloseHandle(pi.hProcess);
	::CloseHandle(hWritePipe);
	::CloseHandle(hReadPipe);

	return TRUE;
}

int main()
{
	char szCmd[] = "ipconfig";
	char szResultBuffer[512] = { 0 };
	DWORD dwResultBufferSize = 512;

	if (FALSE == PipeCmd(szCmd, szResultBuffer, dwResultBufferSize))
	{
		printf("pipe cmd error.\n");
	}
	else
	{
		printf("CMD:\n%s\n", szResultBuffer);
	}

	system("pause");
	return 0;
}
