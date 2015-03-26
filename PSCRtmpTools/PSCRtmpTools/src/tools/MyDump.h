
#ifndef __MYDUMP_H_
#define __MYDUMP_H_
#include  <dbghelp.h> 
#include <winnt.h>
//#include <boost/format.hpp>

#pragma comment(lib,  "dbghelp.lib")


//�����쳣����ص�����
//SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);
//�����Ч 			
//����  �������Լ����쳣�������󣬵���DisableSetUnhandledExceptionFilter ��ֹCRT ���ü��ɡ�

//�쳣�������
//EXCEPTION_EXECUTE_HANDLER equ 1 ��ʾ���Ѿ��������쳣,�������ŵؽ����� 
//EXCEPTION_CONTINUE_SEARCH equ 0 ��ʾ�Ҳ�����,����������,����windows����Ĭ�ϵĴ��������ʾһ�������,������ 
//EXCEPTION_CONTINUE_EXECUTION equ -1 ��ʾ�����Ѿ����޸�,����쳣����������ִ�� 
long   __stdcall   MyUnhandledExceptionFilter(_EXCEPTION_POINTERS*   ExceptionInfo)
{
	MessageBoxA(NULL, "����������쳣���뽫exeͬĿ¼��error.dmp�ļ�������лС����лл", "��ʾ", MB_OK);

	std::string str = "error.dmp";

	HANDLE   hFile = CreateFile(str.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		MINIDUMP_EXCEPTION_INFORMATION   ExInfo;

		ExInfo.ThreadId = ::GetCurrentThreadId();
		ExInfo.ExceptionPointers = ExceptionInfo;
		ExInfo.ClientPointers = NULL;

		//   write   the   dump
		BOOL   bOK = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, &ExInfo, NULL, NULL);
		CloseHandle(hFile);
	}  

	//theApp.PostThreadMessage(WM_QUIT, 0, 0);
	return EXCEPTION_EXECUTE_HANDLER;
}

void DisableSetUnhandledExceptionFilter()
{
	void *addr = (void*)GetProcAddress(LoadLibrary(_T("kernel32.dll")),
		"SetUnhandledExceptionFilter");
	if (addr)
	{
		unsigned char code[16];
		int size = 0;
		code[size++] = 0x33;
		code[size++] = 0xC0;
		code[size++] = 0xC2;
		code[size++] = 0x04;
		code[size++] = 0x00;

		DWORD dwOldFlag, dwTempFlag;
		VirtualProtect(addr, size, PAGE_READWRITE, &dwOldFlag);
		WriteProcessMemory(GetCurrentProcess(), addr, code, size, NULL);
		VirtualProtect(addr, size, dwOldFlag, &dwTempFlag);
	}
}

#endif
