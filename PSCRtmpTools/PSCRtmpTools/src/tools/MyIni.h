/********************************************************************
	����ʱ�䣺	2014/04/13 10: 01: 43
	�ļ�����		FileInfo.h
	���ߣ�		лС��
	
	���ܣ�		1. ���������ļ���
				2.
				
	˵����	    1. 
				2. 
*********************************************************************/
#ifndef MYINI_H_
#define MYINI_H_
#include <string>

class CMyIni
{
public:
	static std::string GetStringConfig(const char * tag);
	static void SetStringConfig(const char * tag,std::string str);

	static int GetIntConfig(const char * tag);
	static void SetIntConfig(const char * tag,int n);

};

#endif