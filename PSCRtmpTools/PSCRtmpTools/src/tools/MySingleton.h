/********************************************************************
	����ʱ�䣺	2014/08/07  11:35:23 
	�ļ�����    	MySingleton.h
	���ߣ�		лС��
	
	���ܣ�		1.
				2.
				
	˵����	    1. 
				2. 
*********************************************************************/
#ifndef MYSINGLETION_H_
#define MYSINGLETION_H_
#include <memory>

template <class T>
class MySingleton
{
public:
	//��ȡ���Ψһʵ��
	static inline std::shared_ptr<T> instance();

	//�ͷ����Ψһʵ��
	static void Release();
protected:
	MySingleton(){}
	~MySingleton(){ Release(); };
	static std::shared_ptr<T> _instance;
};

template <class T>
std::shared_ptr<T> MySingleton<T>::instance()
{
	if (!_instance)
		_instance = std::shared_ptr<T>(new T);
	return _instance;
}

template <class T>
void MySingleton<T>::Release()
{
	if (!_instance)
		return;

	//_instance->release();
	_instance.reset();
	//delete _instance;

	 _instance = NULL;
}

//���� ��̬����
#define DECLARE_SINGLETON_MEMBER(_Ty)\
	template <> std::shared_ptr<_Ty> MySingleton<_Ty>::_instance = NULL;


#endif