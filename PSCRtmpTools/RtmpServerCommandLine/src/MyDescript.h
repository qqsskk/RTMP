/********************************************************************
����ʱ�䣺	2014/12/27  14:31:36
�ļ����� 	MyDescript.h
���ߣ�		лС��

���ܣ�		1. ��������ͻ���ͨ��
			2.���ھ����߼�����

˵����	    1.
2.
*********************************************************************/
#ifndef  __MYDESCRIPT_H_
#define  __MYDESCRIPT_H_
#include "IOCP\MyServer.h"

class CmyDescript : public CMyServer
{
public:
	CmyDescript(int port = 1234,bool isLesonMySelf = false);
	~CmyDescript();
	void StartRun();//��ʼִ��
public://�ӿڻص�
	virtual void OnRead(void * p, char *buf, int len);//{ TRACE("��ȡ���ݽӿ�"); };
	//virtual void OnSend(void * p, char *buf, int len);// { TRACE("д�����ݽӿ�"); }; ��ֹ��ȡ
private:
	int m_port = 0;//�����˿ں�
	bool m_isLesonMySelf = false;//�Ƿ񱾵ؼ���
};
#endif