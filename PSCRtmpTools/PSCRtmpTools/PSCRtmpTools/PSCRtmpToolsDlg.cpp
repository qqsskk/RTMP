
// PSCRtmpToolsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PSCRtmpTools.h"
#include "PSCRtmpToolsDlg.h"
#include "afxdialogex.h"
#include "LogDlg.h"
#include "..\src\tools\MyDump.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPSCRtmpToolsDlg �Ի���



CPSCRtmpToolsDlg::CPSCRtmpToolsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPSCRtmpToolsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPSCRtmpToolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_START, m_btnStart);
	DDX_Control(pDX, IDC_PAUSS, m_btnPause);
	DDX_Control(pDX, IDC_STOP, m_btnStop);
}

BEGIN_MESSAGE_MAP(CPSCRtmpToolsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CPSCRtmpToolsDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_START, &CPSCRtmpToolsDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_PAUSS, &CPSCRtmpToolsDlg::OnBnClickedPauss)
	ON_BN_CLICKED(IDC_STOP, &CPSCRtmpToolsDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_REFRESH, &CPSCRtmpToolsDlg::OnBnClickedRefresh)
END_MESSAGE_MAP()


// CPSCRtmpToolsDlg ��Ϣ�������

BOOL CPSCRtmpToolsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);


	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);//dmp
	//_CrtSetBreakAlloc(1896);//1743 1686 2734 1896 1869

	CLogDlg dlg;
	dlg.m_libRtmp = m_MainEcoder.GetLiveEcode();
	if (dlg.DoModal()== IDCANCEL)
		OnCancel();

	m_MainEcoder.Init();


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPSCRtmpToolsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPSCRtmpToolsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPSCRtmpToolsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPSCRtmpToolsDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (MessageBox("ȷ��ֹͣ��", "��ʾ", MB_ICONEXCLAMATION | MB_OKCANCEL) == IDOK)
	{
		m_MainEcoder.Stop();
		CDialogEx::OnCancel();
	}
}


void CPSCRtmpToolsDlg::OnBnClickedStart()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_MainEcoder.Start();//��ʼ
	m_btnStart.EnableWindow(FALSE);
	m_btnPause.EnableWindow(TRUE);
}


void CPSCRtmpToolsDlg::OnBnClickedPauss()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_MainEcoder.Pause();
	m_btnStart.EnableWindow(TRUE);
	m_btnPause.EnableWindow(FALSE);
}


void CPSCRtmpToolsDlg::OnBnClickedStop()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (MessageBox("ȷ��ֹͣ��", "��ʾ", MB_ICONEXCLAMATION | MB_OKCANCEL) == IDOK)
	{
		m_MainEcoder.Stop();
		OnCancel();
	}
}


void CPSCRtmpToolsDlg::OnBnClickedRefresh()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_MainEcoder.Refresh();
}
