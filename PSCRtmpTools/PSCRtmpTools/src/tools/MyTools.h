/********************************************************************
	����ʱ�䣺	2014/04/13 10: 01: 43
	�ļ�����		FileInfo.h
	���ߣ�		лС��
	
	���ܣ�		1. ������
				2.
				
	˵����	    1. 
				2. 
*********************************************************************/
#ifndef MYTOOLS_H_
#define MYTOOLS_H_
#include <boost\algorithm\string.hpp>
#include <vector>

#define   FOLDER_NAME  "TXT"

//ȫ�ֺ��� ��ʼ�� ����
class MyTools
{
public:
	/*
	  ��ȡ�Լ�ģ��·��
	*/
	static CString GetSelfModulePath();
public:
  /*
  fname:��ǰ��ִ��·�����ļ�����dataĿ¼���ļ���
  prints��Ҫ��ӡ��ֵ��һ��Ԫ�أ�std::string������Ҫ��ӡ��һ������
  isClear:�Ƿ��������
  strFl: ����ļ���
  */ 
  static void PrintToFile(std::string fname,std::vector<std::string> & prints,bool isClear=true, std::string strF = FOLDER_NAME);//��ӡ���

  /*
  fname: ��ǰ��ִ��·�����ļ�����dataĿ¼���ļ���
  reads�������洢��λ�ã�һ���ļ����ݴ浽һ��boost::string��
  strFl: ����ļ���
  */
  static bool ReadFromFile(std::string fname,std::vector<std::string> & reads, std::string strF = FOLDER_NAME);//��������

  //ȡ�ò����ַ���
  static std::string FindFirstStr(std::string & strSrc,int n,bool isBlank = false);//isBlank �Ƿ����ո�
  static std::string FindLastStr(std::string & strSrc,int n,bool isBlank = false);

  /*
   ��ȡĿ¼�������ļ�����
   dir��Ŀ¼
   filenames���ļ��б�
   ���Ƿ������Ŀ¼
   isImage:�Ƿ�ֻ����ͼƬ�ļ�
  */

  static int Get_filenames(const std::string& dir, std::vector<std::string>& filenames,bool isSubDir = true ,bool isImage = false); 

  //ɾ��һ���ļ�
  static bool DeleteFile(const std::string & strPath);

  static bool FileIsExist(const std::string & strPath);//�ж��ļ��Ƿ����

  static void CreatFile(const std::string & strPath);

};

//�ڴ��� ����

#define MEMORY_CHICK \
	int tmpFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);\
	tmpFlag |= _CRTDBG_LEAK_CHECK_DF;\
	_CrtSetDbgFlag(tmpFlag);
#endif

