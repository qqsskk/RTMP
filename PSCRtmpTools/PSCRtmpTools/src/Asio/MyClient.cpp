#include "stdafx.h"
#include "MyClient.h"
#include <boost/thread.hpp>

boost::asio::io_service g_ios;//asio ����� io_server���� (���������)
int CMyClient::s_port = 1234;
std::string CMyClient::s_ip = "127.0.0.1";
CMyClient::sock_pt CMyClient::m_sock_pt_server = NULL;
DECLARE_SINGLETON_MEMBER(CMyClient);

CMyClient::CMyClient()
{
	memset(_Data, 0, sizeof(_Data));
	m_pIGameBase = CGameBase::instance();
}

void CMyClient::RunAction()
{
	boost::thread thrd(&CMyClient::ConnectServer);
}

//���ӷ�����
void CMyClient::ConnectServer()
{
	std::shared_ptr<CMyClient> pMyClient = instance();
	pMyClient->Init(g_ios, s_ip);
	try
	{
		pMyClient->Start();
		g_ios.run();
		m_sock_pt_server.reset();
	}
	catch (std::exception & e)
	{

	}
}

bool CMyClient::OnSend(const std::string & str)
{
	if (m_sock_pt_server)
	{
		m_sock_pt_server->send(boost::asio::buffer(str));
		return true;
	}
	else
		return false;
}

void CMyClient::Start()
{
	sock_pt sock(new boost::asio::ip::tcp::socket(*ios));//����socket ���� ����ָ�룬�Ա����첽���ù����д���

	sock->async_connect(ep,//�첽����
		boost::bind(&CMyClient::Conn_handler, this, boost::asio::placeholders::error, sock));
}

void CMyClient::Conn_handler(const boost::system::error_code & ec, sock_pt sock)//�첽���Ӵ�����
{
	if (ec)
	{
		Start();//һֱ��ѯ����
		return;
	}

	if (m_pIGameBase)
	{
		m_pIGameBase->OnConnect();
		m_sock_pt_server = sock;
		ReadAction();
	}
}


void CMyClient::ReadAction()
{
	/*boost::shared_ptr<std::vector<char> > str(new std::vector<char>(MAX_RESERVE_SIZE, 0));*/
	m_sock_pt_server->async_read_some(boost::asio::buffer(_Data), boost::bind(&CMyClient::Read_handler, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}


void CMyClient::Read_handler(const boost::system::error_code & ec, std::size_t bytes_transferred)
{
	if (ec)
	{
		if (m_pIGameBase)
		{
			m_sock_pt_server.reset();
			m_sock_pt_server = NULL;
			m_pIGameBase->DisConnect();
			Start();//һֱ��ѯ����
		}

		return;
	}

	if (_Data[0] != '\0')
	{
		std::string str(_Data);
		if (m_pIGameBase)
			m_pIGameBase->OnRead(str);
	}

	//���������ȡ�¼�
	ReadAction();
};

void CMyClient::Init(boost::asio::io_service & io, std::string strAppIP)
{
	ios = &io;
	ep =boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(strAppIP), s_port);
}

void CMyClient::release()
{
	g_ios.stop();
	g_ios.reset();
	m_pIGameBase->Release();//����ɾ���ӿ�
	m_pIGameBase = NULL;
	m_sock_pt_server.reset();
}
