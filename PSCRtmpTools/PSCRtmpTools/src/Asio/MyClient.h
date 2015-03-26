#ifndef MYCLIENT_H_
#define MYCLIENT_H_
#include <string>
#include <vector>

//boost asio head 
#ifdef _MSC_VER
#define _WIN32_WINNT 0x0501
#endif 
#define BOOST_REGEX_NO_LIB
#define BOOST_DATE_TIME_SOURCE
#define BOOST_SYSTEM_NO_LOB
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/locale/encoding.hpp>
#include "../tools/MySingleton.h"
#include <boost/asio/io_service.hpp>
#include <boost/smart_ptr/scoped_ptr.hpp>
#include "../Data/GameBase.h"

#define MAX_RESERVE_SIZE 1024*8  //�����ճߴ�

class CMyClient : public MySingleton<CMyClient>
{
public:
	CMyClient();
// 	CMyClient(boost::asio::io_service & io, std::string strAppIP) :ios(&io),
// 		ep(boost::asio::ip::address::from_string(strAppIP), s_port){}
	static void RunAction();//��ʼִ��
	//virtual void OnRead(const std::string & str);//��ȡ�����ļ�
	bool OnSend(const std::string & str);//�����¼� ȥ����������
public:
	static int s_port;//�˿ں�
	static std::string s_ip;//ip
	void Init(boost::asio::io_service & io, std::string strAppIP);
	void release();
//-------------------------------------˽�д����-----------------------------------------------------------
protected:
	typedef boost::shared_ptr<boost::asio::ip::tcp::socket> sock_pt;//client ����Ҫaccept��ֱ��connect
	void Start();
	void ReadAction();//��ȡ�¼����
	void Conn_handler(const boost::system::error_code & ec, sock_pt sock);//�첽���Ӵ�����
	void Read_handler(const boost::system::error_code & ec, std::size_t bytes_transferred);
	static void ConnectServer();//���ӷ�����
private:
	boost::asio::io_service * ios = NULL;//io_server����
	boost::asio::ip::tcp::endpoint ep;//TCP �˵�
	static sock_pt m_sock_pt_server;//����������׽��� ����ָ�� (��Ҫ���ڷ������ݵ�������)
	std::shared_ptr<CGameBase> m_pIGameBase;//��Ϸ���࣬���ڴ������ݷ��͹���
	char _Data[MAX_RESERVE_SIZE];
};

#endif