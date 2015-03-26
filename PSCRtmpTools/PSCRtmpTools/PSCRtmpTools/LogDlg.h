#pragma once
#include <memory>
#include "..\src\librtmp\LibRtmp.h"
#include "..\src\tools\MyIni.h"


// CLogDlg �Ի���

class CLogDlg : public CDialog
{
	DECLARE_DYNAMIC(CLogDlg)

public:
	CLogDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLogDlg();

// �Ի�������
	enum { IDD = IDD_LOG_DIALOG };

	std::shared_ptr<LibRtmp> m_libRtmp = nullptr;
	CMyIni m_myIni;
	void Init();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
