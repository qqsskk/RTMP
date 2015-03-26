#include "stdafx.h"
#include "MyIni.h"
#include "MyTools.h"
//#include "MyTools.h"
/*
//��ȡ�Լ�ģ����
HMODULE GetSelfModuleHandle()
{
	MEMORY_BASIC_INFORMATION mbi;
	return ((::VirtualQuery(GetSelfModuleHandle, &mbi, sizeof(mbi)) != 0) ? (HMODULE) mbi.AllocationBase : NULL);
}

CString GetSelfModulePath()
{
	char ctr[MAX_PATH+1] = {0};
	HMODULE hModule = GetSelfModuleHandle();
	GetModuleFileName(hModule,ctr,MAX_PATH);
	CString str;
	str.Format("%s",ctr);
	str = str.Left(str.ReverseFind('\\'));
	return str;
}
*/
std::string CMyIni::GetStringConfig( const char * tag )
{
	CString ConfigFile = MyTools::GetSelfModulePath() + "\\data\\Config.ini";
	WIN32_FIND_DATA FindFileData;

	if(FindFirstFile(ConfigFile,&FindFileData) == INVALID_HANDLE_VALUE )//�ļ��Ƿ����
	{
		MessageBox(NULL,"�Ҳ��������ļ�","error",MB_OK);
		exit(0);
	}

	char buf[256]={0};
	memset(buf,0,256);
	GetPrivateProfileString("SETUP",tag,"",buf,256,ConfigFile);//�õ����´�������
	return std::string(buf);
}

void CMyIni::SetStringConfig( const char * tag,std::string str )
{
	CString ConfigFile = MyTools::GetSelfModulePath() + "\\data\\Config.ini";
	WIN32_FIND_DATA FindFileData;

	WritePrivateProfileString("SETUP",tag,str.c_str(),ConfigFile);//��������
}

int CMyIni::GetIntConfig( const char * tag )
{
	CString ConfigFile = MyTools::GetSelfModulePath() + "\\data\\Config.ini";
	WIN32_FIND_DATA FindFileData;

	if(FindFirstFile(ConfigFile,&FindFileData) == INVALID_HANDLE_VALUE )//�ļ��Ƿ����
	{
		MessageBox(NULL,"�Ҳ��������ļ�","error",MB_OK);
		exit(0);
	}

	char buf[256]={0};
	memset(buf,0,256);
	return GetPrivateProfileInt("SETUP",tag,0,ConfigFile);//�õ����´�������
}

void CMyIni::SetIntConfig( const char * tag,int n )
{
	CString ConfigFile = MyTools::GetSelfModulePath() + "\\data\\Config.ini";
	//WIN32_FIND_DATA FindFileData;

	char str[70];
	memset(str,0,70);
	//_i64toa(v,str,69);
	sprintf_s(str,"%d",n);

	WritePrivateProfileString("SETUP",tag,str,ConfigFile);//��������
}
