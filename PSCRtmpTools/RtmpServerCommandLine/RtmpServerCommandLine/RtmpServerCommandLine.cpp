// RtmpServerCommandLine.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "..\src\MyDescript.h"


int _tmain(int argc, _TCHAR* argv[])
{
	HWND hwnd = ::FindWindow("ConsoleWindowClass", 0);
	if (hwnd) ::SendMessage(hwnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
	while (true)
	{
		CmyDescript myDescript(1234, false);
		myDescript.StartRun();
	}


	return 0;
}

