/********************************************************************
	����ʱ�䣺	2014/08/15  16:26:54 
	�ļ�����		MyQueue.h
	���ߣ�		лС��
	
	���ܣ�		1. �̰߳�ȫ����
				2.
				
	˵����	    1. ���߳�״̬�µİ�ȫ����
				2. 
*********************************************************************/
#ifndef MYQUEUE_H_
#define MYQUEUE_H_
#include <queue>//std queue
#include <boost/thread/mutex.hpp>

template<typename TYPE>
class CMyQueue
{
private:
	std::queue<TYPE> theQueue_;
	boost::mutex m_oMutex;
public:
	CMyQueue(){};
	~CMyQueue()
	{
		boost::mutex::scoped_lock oLock(m_oMutex);//������
		while(!theQueue_.empty())
		{
			TYPE tmp = theQueue_.front();
			if (tmp.data)
			{
				delete tmp.data;
			}
			theQueue_.pop();
		}
	};
public:
	TYPE pop();//��һ������
	void push( const TYPE &val );//ѹ��һ������
	size_t size();//���г���
	bool empty();//�п�
};
template<typename TYPE>
TYPE CMyQueue<TYPE>::pop()
{
	boost::mutex::scoped_lock oLock(m_oMutex);//������
	if (!theQueue_.empty())
	{
		TYPE tmp = theQueue_.front();
		theQueue_.pop();
		return tmp;
	}
	else
		return TYPE();//�յķ���Ĭ��
}

template<typename TYPE>
void CMyQueue<TYPE>::push( const TYPE &val )
{
	boost::mutex::scoped_lock oLock(m_oMutex);//������
	theQueue_.push(val);
}

template<typename TYPE>
size_t CMyQueue<TYPE>::size()
{
	//boost::mutex::scoped_lock oLock(m_oMutex);//������
	//	size_t size=theQueue_.size();
	return theQueue_.size();
}

template<typename TYPE>
bool CMyQueue<TYPE>::empty()
{
	boost::mutex::scoped_lock oLock(m_oMutex);//������
	return theQueue_.empty();
}

#endif