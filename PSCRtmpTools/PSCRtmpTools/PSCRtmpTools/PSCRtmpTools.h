
// PSCRtmpTools.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPSCRtmpToolsApp: 
// �йش����ʵ�֣������ PSCRtmpTools.cpp
//

class CPSCRtmpToolsApp : public CWinApp
{
public:
	CPSCRtmpToolsApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPSCRtmpToolsApp theApp;