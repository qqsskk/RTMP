#ifndef __MYMAINECODER_H_
#define __MYMAINECODER_H_
#include "RtmpLiveEncoder.h"
#include "VideoEncoder.h"
#include "AudioEncoder.h"
#include <thread>

class CMyMainEcode : public EcoderCtr
{
public:
	std::shared_ptr<LibRtmp> GetLiveEcode(){ return m_RtmpLiveEcoder.m_libRtmp; };
	void Init();//��ʼ�� �����ȳ�ʼ����
	void Start();//��ʼ
	void Pause();//��ͣ
	void Stop();//ֹͣ
	void Refresh();//ˢ��

	CMyMainEcode();
	~CMyMainEcode();
private:
	RtmpLiveEncoder m_RtmpLiveEcoder;//��rtmp serverͨѶ����
	VideoEncoderThread m_videoEcoder;//��Ƶ��������
	AudioEncoderThread m_audioEcoder;//��Ƶ��������

// 	bool m_is_stop = true;
// 	bool m_is_pause = false;

	//�߳�
	std::thread m_thread_video;//��Ƶ�����߳�
	std::thread m_thread_audio;//��Ƶ�����߳�
	std::thread m_thread_rtmpLiveEcode;//rtmp server ͨѶ�����߳�
};

#endif