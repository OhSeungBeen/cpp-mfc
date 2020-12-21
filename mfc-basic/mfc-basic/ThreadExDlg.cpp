// ThreadEx.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "mfc-basic.h"
#include "ThreadExDlg.h"


// CThreadEx ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CThreadExDlg, CDialog)

CThreadExDlg::CThreadExDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CThreadExDlg::IDD, pParent)
{

}

CThreadExDlg::~CThreadExDlg()
{
}

void CThreadExDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CThreadExDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_RUN_NOTEPAD, &CThreadExDlg::OnBnClickedButtonRunNotepad)
END_MESSAGE_MAP()

UINT ThreadWaitNotpad(LPVOID pParam) // �ݵ�� UNIT���� ��ȯ�ؾߵǰ� LPVOID���� �����͸� ���ڷ� �޾ƾ��Ѵ�.
{                                    // ������� ������ �Լ��� Ư�� Ŭ������ ����� ��쿡�� �ݵ�� ����(static) ��� �Լ����� �Ѵ�.
	TCHAR szWinPath[MAX_PATH];
	::GetWindowsDirectory(szWinPath, MAX_PATH);  // C:\Windows
	lstrcat(szWinPath, "\\notepad.exe"); // lstrcat ���ڿ� ���� �Լ� C:\Windows\notepad.exe 

	SHELLEXECUTEINFO sei;
	::ZeroMemory(&sei, sizeof(sei));
	sei.cbSize = sizeof(sei);
	sei.hwnd = NULL; // �޽��� ���� ��¿� ������ �ڵ�  NULL(����ȭ��)
	sei.lpFile = szWinPath; // ���� ���
	sei.nShow = SW_SHOW; // ȭ�鿡 ���̵��� ���� ����
	sei.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_NO_CONSOLE;
	sei.lpVerb = __TEXT("open"); // ����/����/����/URL OEPN �ǹ�
	sei.lpParameters = NULL; // �������Ͽ� ���ڷ� �ְ��� �ϴ� ����

	//if(::ShellExecuteEx(&sei)) // Ư�� ����� ������ �����ϴ� API �Լ�
	//{
	//	::WaitForSingleObject(sei.hProcess, INFINITE);// Ư�� ��ü�� ���°� ������ �� ���� ���� �������� ������ ���ߴ� ����
	//}
	
	if(::ShellExecuteEx(&sei))
	{

		HANDLE arhList[2];
		arhList[0] = sei.hProcess;
		arhList[1] = (HANDLE)g_ExitEvent;
		// ������ ��� �ڵ��� 2���� ����
		// �޸��� ���μ��� �ڵ� ���� , ���� �̺�Ʈ �ڵ�
		DWORD dwResult = ::WaitForMultipleObjects(2, arhList, FALSE, INFINITE); // ����, �ڵ鸮��Ʈ , FALSE �ϳ��� �����Ǿ �Լ� ��ȯ (�������α׷� �Ǵ� �޸��� ����� ���)

		if(dwResult == WAIT_OBJECT_0)
		{
			AfxMessageBox("�޸����� ���� �Ǿ����ϴ�.");
		}
		else if(dwResult == WAIT_OBJECT_0 + 1)
		{
			OutputDebugString("Thread ������ ����Ǿ����ϴ�!");
		}
	}

	g_pThread = NULL;
	return 0;
}

void CThreadExDlg::OnBnClickedButtonRunNotepad()
{	// CwinThread ��ü ���߿� �ڵ����� ����
	//CWinThread* pThread = AfxBeginThread(ThreadWaitNotpad, NULL); // afxBeginThread() ������ ���� / �����帣 ������ �Լ� �ּҸ� ���ڷ� �޴´�.
	
	if(g_pThread != NULL)
	{
		AfxMessageBox("�޸��� �����尡 �̹� �������Դϴ�.");
		return;
	}
	// �۷ι� ������ ����Ͽ� �ߺ� ������ ������ �����Ѵ�.
	g_pThread = AfxBeginThread(ThreadWaitNotpad, NULL);
	if(g_pThread == NULL)                                           
	{
		AfxMessageBox("ERROR: Faild to begin worker-thread!");
	}
}
