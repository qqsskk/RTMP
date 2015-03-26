#include "StdAfx.h"
#include "MyServer.h"

DWORD __stdcall CMyServer::AcceptThread(LPVOID Param)
{
	CMyServer * pthis = (CMyServer *)Param;
	while (pthis->m_acceptThread)
	{
		SOCKET client;
		if ((client = accept(pthis->m_sSocket, NULL, NULL)) != INVALID_SOCKET)
		{
			pthis->OnAccept(client);    //   ���� OnAccept()֪ͨӦ�ó������¿ͻ������� 
		}  
		else
			break;
	}

	pthis->m_acceptThread = false;
	return 1;
}

DWORD __stdcall CMyServer::ReadThread(LPVOID Param)
{
	CMyServer * pthis = (CMyServer *)Param;
	while (pthis->m_readThread)
	{
		char recvBuf[MYIOCP_BUFFER_MAX_SIZE];
		memset(recvBuf, 0, MYIOCP_BUFFER_MAX_SIZE*sizeof(char));
		int n = recv(pthis->m_ClientSocket, recvBuf, MYIOCP_BUFFER_MAX_SIZE - 1, 0);
		if (n <= 0)//�Ѿ��ر�
		{
			Lock lock(&pthis->m_criticalSection);//��ȡ�ٽ���
			pthis->OnClose(NULL);
			break;
		}
		else
		{
			Lock lock(&pthis->m_criticalSection);//��ȡ�ٽ���
			pthis->OnRead(NULL, recvBuf, MYIOCP_BUFFER_MAX_SIZE);
		}
			
	}

	pthis->m_acceptThread = false;
	return 1;
}

CMyServer::CMyServer(void)
{
	m_sSocket = INVALID_SOCKET;
	m_verData.clear();
	m_port = -1;
	m_bInit = false;
	m_acceptThread = false;
	m_readThread = false;
	m_ClientSocket = INVALID_SOCKET;
}

CMyServer::~CMyServer(void)
{
	DeleteIocp();
}

void CMyServer::OnAccept(SOCKET socket)
{
	Lock lock(&m_criticalSection);//��ȡ�ٽ���
	m_ClientSocket = socket;
	if (m_verData.size() > 0)
	{
		for (int i = 0; i < m_verData.size(); i++)//������ǰ����
			Send(socket, m_verData.at(i).c_str(), m_verData.at(i).length());
	}

	m_readThread = true;
	g_hrThread = CreateThread(NULL, 0, ReadThread, (LPVOID)this, 0, &m_readthreadID);    //   ���������̣߳��������տͻ��˵�����
}

bool CMyServer::Listen(int port, bool isMySelf)
{
	if (m_bInit)
		return false;

	m_acceptThread = true;
	m_port = -1;
	//��һ��������socket�⺯��
	//**********************************************************
	WSADATA wsaData;
	int err;

	err = WSAStartup(MAKEWORD(1, 1), &wsaData);

	if (err != 0) {
		return 0;
	}

	if (LOBYTE(wsaData.wVersion) != 1 ||
		HIBYTE(wsaData.wVersion) != 1) {
		WSACleanup();
		return 0;
	}
	//**********************************************************

	//�ڶ��������׽���
	m_sSocket = socket(AF_INET, SOCK_STREAM, 0);

	//�����������׽���

	//��ȡ��ַ�ṹ
	SOCKADDR_IN addrSrv;

	if (isMySelf)
		addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//��������
	else
		addrSrv.sin_addr.S_un.S_addr =  htonl(INADDR_ANY); //���е�ַ
	//��IP��ַָ��ΪINADDR_ANY�������׽������κη�������ػ�����IP��ַ���ͻ��������
	//htonl()���������޷��ų�������ת���������ֽ�˳��

	addrSrv.sin_family = AF_INET;
	//sin_family ��ʾ��ַ�壬����IP��ַ��sin_family��Ա��һֱ��AF_INET

	//addrSrv.sin_port = htons(port);
	//htons()���������޷��Ŷ�������ת���������ֽ�˳��

	//��ѯ����
	bool isIni = false;
	for (int i = port; i < 65535; i++)
	{
		addrSrv.sin_port = htons(port);
		if (bind(m_sSocket, (struct sockaddr *)&addrSrv, sizeof(addrSrv)) != SOCKET_ERROR)//�ɹ�
		{
			m_port = i;
			break;
		}
		else
		{
			TRACE("Listen error");
		}
	}
	if (m_port == -1)
		return false;

	//�����ͻ���
	if (listen(m_sSocket, 10) == SOCKET_ERROR)
		return false;


	m_ClientSocket = NULL;
	g_haThread = CreateThread(NULL, 0, AcceptThread, (LPVOID)this, 0, &m_athreadID);    //   ���������̣߳��������տͻ��˵�����

	return true;
}

void CMyServer::SendAll(const char *buf, int len)
{
	Lock lock(&m_criticalSection);//��ȡ�ٽ���

	if (m_ClientSocket == INVALID_SOCKET)
		m_verData.push_back(std::string(buf));
	else
	{
		for (int i = 0; i < m_verData.size(); i++)//������ǰ����
			Send(m_ClientSocket, m_verData.at(i).c_str(), m_verData.at(i).length());

		Send(m_ClientSocket, buf, len);
		m_verData.clear();
	}
}

bool CMyServer::Send(SOCKET socket, const char *buf, int len)
{
	DWORD    dwBytes;
// 	if (SOCKET_ERROR == WSASend(socket, buf, 1, &dwBytes, 0, NULL, NULL))
	if (SOCKET_ERROR == send(socket,buf,len,0))
	{
		this->OnClose(NULL);
		return false;
	}

	return true;
}

void CMyServer::DeleteIocp()
{
	{
		Lock lock(&m_criticalSection);//��ȡ�ٽ���
		closesocket(m_sSocket);
		m_sSocket = INVALID_SOCKET;
		closesocket(m_ClientSocket);
		m_ClientSocket = INVALID_SOCKET;
		m_verData.clear();
	}

	this->m_acceptThread = false;
	this->m_readThread = false;
	this->m_bInit = false;

	//�ȴ�һ���߳̽���
	WaitForSingleObject(g_haThread, INFINITE);
	WaitForSingleObject(g_hrThread, INFINITE);
}

std::string CMyServer::GetStrPort(std::string strHead)
{
	std::string str = strHead;
	char cs[7];
	memset(cs, 0, 7);
	sprintf_s(cs, "%d", m_port);
	str.append(cs);
	return str;
}
