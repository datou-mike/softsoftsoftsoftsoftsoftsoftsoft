#include <windows.h>

#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	HANDLE hRead = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hWrite = GetStdHandle(STD_OUTPUT_HANDLE);

	char s[] = "Hello, I am child process\n";
	DWORD dwWrite;

	if (!WriteFile(hWrite, s, strlen(s) + 1, &dwWrite, NULL))
	{
		cout << "Write to pipe failed!" << endl;
		return -1;
	}

	char buf[100];
	DWORD dwRead;
	if (!ReadFile(hRead, buf, 100, &dwRead, NULL))
	{
		cout << "Read from pipe failed!" << endl;
		return -1;
	}

	return 0;
}