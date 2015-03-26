// LogDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PSCRtmpTools.h"
#include "LogDlg.h"
#include "afxdialogex.h"
#include <string>
#include <boost\algorithm\string.hpp>
#include "..\src\tools\MyTools.h"
#include "..\src\Asio\MyClient.h"


// CLogDlg �Ի���

IMPLEMENT_DYNAMIC(CLogDlg, CDialog)

CLogDlg::CLogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLogDlg::IDD, pParent)
{

}

CLogDlg::~CLogDlg()
{
}

void CLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLogDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CLogDlg::OnBnClickedOk)
END_MESSAGE_MAP()


void CLogDlg::Init()
{
	((CEdit *)GetDlgItem(IDC_EDIT1))->SetWindowText(CString(m_myIni.GetStringConfig("serverAdd").c_str()));
}


BOOL CLogDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	Init();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

// CLogDlg ��Ϣ�������


void CLogDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString cstr;
	((CEdit *)GetDlgItem(IDC_EDIT1))->GetWindowText(cstr);
	std::string str(cstr.GetBuffer());
	cstr.ReleaseBuffer();

	if (str.length() < 1)
	{
		MessageBox("������һ��rtmp ��������ַ", "��ʾ");
		return;
	}

	boost::replace_all(str,"\\","/");

	if (!boost::istarts_with(str, "rtmp://"))
		str = "rtmp://" + str;

	unsigned int loc = str.find("//");
	if (loc != std::string::npos)
	{
		unsigned int loc1 = str.find("/", loc + 2);

		if (loc1 != std::string::npos)
			CMyClient::s_ip = MyTools::FindLastStr(MyTools::FindFirstStr(str, loc1,true),loc1-loc-2,true);
	}

	if (!m_libRtmp->Open(str.c_str()))//����ʧ��
	{
		MessageBox("rtmp ����ʧ�ܣ�\n�����־��Ϣ�� �鿴 librtmp.log���˽����ԭ��", "��ʾ");
		return;
	}
	else
	{
		m_myIni.SetStringConfig("serverAdd", str);
		std::shared_ptr<CMyClient> client = CMyClient::instance();
		if (client) client->RunAction();

		CDialog::OnOK();
	}
	//m_libRtmp->Close();

}


