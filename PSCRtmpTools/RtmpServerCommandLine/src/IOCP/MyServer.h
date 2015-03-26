/********************************************************************
	����ʱ�䣺	2014/08/05  14:34:36
	�ļ����� 	MyServer.h
	���ߣ�		лС��

	���ܣ�		1. ���ڷ������׽�������
	2.

	˵����	    1.
	2.
*********************************************************************/

#ifndef __MYSERVER_H_
#define __MYSERVER_H_
#include <vector>
#include <string>
#include <winsock2.h>   
#pragma comment( lib, "ws2_32.lib" )   

#ifndef _MFC_VER
#define TRACE(ver) printf(ver); 
#endif

#define MYIOCP_BUFFER_MAX_SIZE  4096

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

class CMyServer
{
public:
	CMyServer(void);
	CMyServer(int port){ Listen(port,true); };
	~CMyServer(void);

	static DWORD __stdcall AcceptThread(LPVOID Param);
	static DWORD __stdcall ReadThread(LPVOID Param);
public:
	bool					m_acceptThread;
	bool					m_readThread;
	CriticalSection			m_criticalSection;	//	 �ٽ���
	SOCKET					m_sSocket;
	SOCKET					m_ClientSocket;//���ڱ������ӵ��׽��֣���Ҫ���ڷ�����Ϣ
	std::vector<std::string> m_verData;
	int						 m_port;
	bool					m_bInit;//�Ƿ��ʼ��
	DWORD					m_athreadID;
	DWORD					m_readthreadID;
	HANDLE					g_haThread;     //   �����߳̾��
	HANDLE					g_hrThread;     //   �����߳̾��
	bool Listen(int port,bool isMySelf);//������ʼ port ��С�˿ں�
	bool Send(SOCKET socket, const char *buf, int len);
	void SendAll(const char *buf, int len);
	void DeleteIocp();//����ر��¼�
	std::string GetStrPort(std::string strHead);
public:
	virtual void OnAccept(SOCKET socket);
	virtual void OnRead(void * p, char *buf, int len){ TRACE("��ȡ���ݽӿ�\n"); };
	virtual void OnSend(void * p, char *buf, int len){ TRACE("д�����ݽӿ�\n"); };
	virtual void OnClose(void * p){ m_ClientSocket = NULL; TRACE("�ر�socket\n"); };
};

#endif
