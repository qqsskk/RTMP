/********************************************************************
	����ʱ�䣺	2014/08/05  14:34:36
	�ļ����� 	MyIocp.h
	���ߣ�		лС��

	���ܣ�		1. ���ڷ������׽�������
	2.

	˵����	    1.
	2.
*********************************************************************/

#ifndef MYIOCP_H_
#define MYIOCP_H_

#include <map>
#include <vector>
#include <string>
#include <winsock2.h>   
#pragma comment( lib, "ws2_32.lib" )   

#define MYIOCP_BUFFER_MAX_SIZE  4096
const int OP_READ = 0;
const int OP_WRITE = 1;
const int OP_ACCEPT = 2;

class CriticalSection//�ٽ���
{
public:
	CriticalSection(){InitializeCriticalSection(&m_CritiSect);};//��ʼ���ٽ���
	~CriticalSection(){DeleteCriticalSection(&m_CritiSect);};//ɾ���ٽ���
	void Enter(){EnterCriticalSection(&m_CritiSect);};//�����ٽ���
	void Leave(){LeaveCriticalSection(&m_CritiSect);};//�뿪�ٽ���
private:
	CRITICAL_SECTION m_CritiSect;//�����ٽ�������
};

class Lock//�Զ�����
{
public:
	explicit Lock(CriticalSection * PCritSect){//��������ʽת��
		m_pCritical=PCritSect;
		m_pCritical->Enter();
	}
	~Lock(){m_pCritical->Leave();}
private:
	CriticalSection * m_pCritical;//�Զ����ٽ���
};

/*
	 OVERLAPPEDPLUS �ṹ�����˼·
	 OVERLAPPED ��һ���̶������ڴ���������Ϣ�¼�����ֵ�Ľṹ�����
	 ����ɶ˿ں��ص�I/Oģ�������ڷ�����Ϣ�¼��Ľ��
	 ��Ϊ�ڴ���������Ϣ��ʱ�򣬷��͵���һ������ֵ�Ľṹ��ָ�룬ֻҪ�ṹ��
	 ��ǰ�沿������ϵͳ��Ҫ����ϵͳ�����ɹ���ʱ��Ҳ�ͻ������ṹ��ָ��
	 ���ظ��û�������ֻҪ��ϵͳ����Ľṹ�������չһЩ�Լ��Ķ������Ϳ���
	 �����ɵ�ȷ������Ϣ��˭�������ġ�
	 ����������ɶ˿�����Ƶ�ʱ��Ҳ����������������������������ֻ�Ƿ���
	 һЩ��ϵͳ�����йص����ݣ��û���Ҫ��ŵ���������Ͳ��ڴ��
	 ����洢��ϵͳ��ص������У�
	 socket
	 OpCode ������Ϣ�Ĳ������ͣ�����ɶ˿ڵĲ������棬������Ϣ֪ͨϵͳ��
	 ������/д���ݣ�����Ҫ����������Ϣ�ṹ���ȥ�ģ��������ϵͳҪͬʱ
	 ���ж�д�����Ļ�������Ҫ��һ�����������ֲ����ˣ�

	 WSABUF   wbuf;                  //   ��д�������ṹ�����
	 DWORD    dwBytes, dwFlags;		//   һЩ�ڶ�дʱ�õ��ı�־�Ա���
	 char buf[4096];                //   �Լ��Ļ�����
	 �����4��������ŵ���һЩ����Ϣ��ص����ݣ�����һЩ�������õ��ģ�
	 ��Щ�������ǹ̶��ģ�����������Ҫ�ο�һ����ɶ˿���غ����Ĳ����ӿ�
	 */
struct OVERLAPPEDPLUS
{
	OVERLAPPED    ol;
	SOCKET        s;
	int		OpCode;
	WSABUF   wbuf;
	DWORD    dwBytes, dwFlags;
	char buf[MYIOCP_BUFFER_MAX_SIZE];
};

class CMyIOCP
{
protected:
	HANDLE					g_hwThread;     //   �����߳̾��
	DWORD					m_wthreadID;
	HANDLE					g_haThread;     //   �����߳̾��
	DWORD					m_athreadID;
	CriticalSection			m_criticalSection;	//	 �ٽ���
public:
	bool					m_workThread;
	bool					m_acceptThread;
	HANDLE					m_hIocp;             //   ��ɶ˿ڵľ��
	SOCKET					m_sSocket;
	std::map<SOCKET,SOCKET>	m_mapSocket;//���ڱ������ӵ��׽��֣���Ҫ���ڷ�����Ϣ
	std::vector<std::string> m_verData;
public:
	CMyIOCP(void);
	CMyIOCP(int port){Listen(port);};
	~CMyIOCP(void);
	virtual void OnRead(void * p, char *buf, int len){ TRACE("��ȡ���ݽӿ�"); };
	virtual void OnSend(void * p, char *buf, int len){ TRACE("д�����ݽӿ�"); };
	virtual void OnAccept(SOCKET socket);
	virtual void OnClose(void * p){TRACE("�ر�socket");}; 

	void DeleteMapSocket(SOCKET socket);
	void DeleteAccepted();
	void DeleteListener();
public:
	bool SetIoCompletionPort(SOCKET socket, void *p, char *buf = NULL, int len = 0);
	//   ��һ��socket��һ���Զ���Ľṹ���������ɶ˿ڣ��൱�ڰ�socket��һ���ṹ��������а󶨣���  
	//   ��������������3�������¼���ʱ�򣬸ýṹ��������ٴ��ظ�����   
	//   �����Ϳ������ֵ�ǰ�����¼����Ǹ�socket������ 
	bool Init(void);
	bool Listen(int port);
	bool Send(SOCKET socket,const char *buf, int len);
	void SendAll(const char *buf, int len);
	static DWORD __stdcall WorkThread(LPVOID Param);
	static DWORD __stdcall AcceptThread(LPVOID Param);
	void DeleteIocp();//����ر��¼�
};

#endif
