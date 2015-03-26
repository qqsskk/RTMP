/********************************************************************
	����ʱ�䣺	2014/08/05  17:40:22 
	�ļ����� 	HostMsPaintChild.h
	���ߣ�		лС��

	���ܣ�		1. ����Ƕ��һ���Ӵ��ڵ�������
	2.

	˵����	    1.
	2.
*********************************************************************/

#ifndef HOSTMSPAINTCHILD_H_
#define HOSTMSPAINTCHILD_H_

/*************Global functions for hosting******************/
class ChostChildDlg
{	
public:
	//����������
	//args �����Կո�ͷ
	bool ActionHostmspaint(HWND parent,const CRect & rect,LPCTSTR path,LPCTSTR name,LPCTSTR args = "");

	//����
	void ActionKillprocess();
public:
	ChostChildDlg();
	~ChostChildDlg();

private:
	HANDLE m_handle;//process handle
	static HWND s_apphwnd;//window handle
	//Function to enumerate all windows.
	static int CALLBACK EnumWindowsProc(HWND hwnd, LPARAM param)
	{
		DWORD pID;
		DWORD TpID = GetWindowThreadProcessId(hwnd, &pID);//get process id
		if (TpID == (DWORD)param)
		{
			s_apphwnd=hwnd;//hwnd is the window handle
			return false;
		}
		return true;
	}
	
	//Functio to start a orocess and return the process handle
	HANDLE StartProcess(LPCTSTR program,LPCTSTR filename, LPCTSTR args);
};

/**********************************************************/

#endif