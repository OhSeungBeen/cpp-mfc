// ThreadEx.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "mfc-basic.h"
#include "ThreadExDlg.h"


// CThreadEx 대화 상자입니다.

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

UINT ThreadWaitNotpad(LPVOID pParam) // 반드시 UNIT형을 반환해야되고 LPVOID형의 포인터를 인자로 받아야한다.
{                                    // 스레드로 실행할 함수가 특정 클래스의 멤버인 경우에는 반드시 정적(static) 멤버 함수여야 한다.
	TCHAR szWinPath[MAX_PATH];
	::GetWindowsDirectory(szWinPath, MAX_PATH);  // C:\Windows
	lstrcat(szWinPath, "\\notepad.exe"); // lstrcat 문자열 결합 함수 C:\Windows\notepad.exe 

	SHELLEXECUTEINFO sei;
	::ZeroMemory(&sei, sizeof(sei));
	sei.cbSize = sizeof(sei);
	sei.hwnd = NULL; // 메시지 상자 출력용 윈도우 핸들  NULL(바탕화면)
	sei.lpFile = szWinPath; // 파일 경로
	sei.nShow = SW_SHOW; // 화면에 보이도록 할지 결정
	sei.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_NO_CONSOLE;
	sei.lpVerb = __TEXT("open"); // 파일/문서/폴더/URL OEPN 의미
	sei.lpParameters = NULL; // 실행파일에 인자로 넣고자 하는 내용

	//if(::ShellExecuteEx(&sei)) // 특정 경로의 파일을 실행하는 API 함수
	//{
	//	::WaitForSingleObject(sei.hProcess, INFINITE);// 특정 객체의 상태가 설정될 때 까지 현재 스레드의 실행을 멈추는 역할
	//}
	
	if(::ShellExecuteEx(&sei))
	{

		HANDLE arhList[2];
		arhList[0] = sei.hProcess;
		arhList[1] = (HANDLE)g_ExitEvent;
		// 감시할 대상 핸들을 2개로 설정
		// 메모장 프로세스 핸들 종료 , 종료 이벤트 핸들
		DWORD dwResult = ::WaitForMultipleObjects(2, arhList, FALSE, INFINITE); // 갯수, 핸들리스트 , FALSE 하나만 설정되어도 함수 반환 (응용프로그램 또는 메모장 종료될 경우)

		if(dwResult == WAIT_OBJECT_0)
		{
			AfxMessageBox("메모장이 종료 되었습니다.");
		}
		else if(dwResult == WAIT_OBJECT_0 + 1)
		{
			OutputDebugString("Thread 예제가 종료되었습니다!");
		}
	}

	g_pThread = NULL;
	return 0;
}

void CThreadExDlg::OnBnClickedButtonRunNotepad()
{	// CwinThread 객체 나중에 자동으로 삭제
	//CWinThread* pThread = AfxBeginThread(ThreadWaitNotpad, NULL); // afxBeginThread() 스레드 생성 / 스레드르 실행할 함수 주소를 인자로 받는다.
	
	if(g_pThread != NULL)
	{
		AfxMessageBox("메모장 스레드가 이미 실행중입니다.");
		return;
	}
	// 글로벌 변수를 사용하여 중복 스레드 실행을 방지한다.
	g_pThread = AfxBeginThread(ThreadWaitNotpad, NULL);
	if(g_pThread == NULL)                                           
	{
		AfxMessageBox("ERROR: Faild to begin worker-thread!");
	}
}
