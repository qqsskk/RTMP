
// PSCRtmpToolsDlg.h : ͷ�ļ�
//

#pragma once
#include "..\src\Encoder\MyMainEcoder.h"
#include "afxwin.h"


// CPSCRtmpToolsDlg �Ի���
class CPSCRtmpToolsDlg : public CDialogEx
{
// ����
public:
	CPSCRtmpToolsDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PSCRTMPTOOLS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
public:
	CMyMainEcode m_MainEcoder;//�����ӿ�����
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedPauss();
	afx_msg void OnBnClickedStop();
	CButton m_btnStart;
	CButton m_btnPause;
	CButton m_btnStop;
	afx_msg void OnBnClickedRefresh();
};
