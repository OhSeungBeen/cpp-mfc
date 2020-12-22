
// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "MFCBasic.h"

#include "MainFrm.h"
#include "WorkThreadDlg.h"
#include "UIThread.h" // UIThread include

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_MENU_THREAD_EX, &CMainFrame::OnMenuThreadEx)
	ON_COMMAND(ID_Menu_UIThread, &CMainFrame::OnMenuUithread)
	ON_COMMAND(ID_Menu_ResumeThread, &CMainFrame::OnMenuResumethread)
	ON_COMMAND(ID_Menu_SuspendThread, &CMainFrame::OnMenuSuspendthread)
	ON_COMMAND(ID_Menu_ExitThread, &CMainFrame::OnMenuExitthread)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기

void CMainFrame::OnMenuThreadEx()
{
	CWorkThread threadExDlg;
	threadExDlg.DoModal();
}

void CMainFrame::OnMenuUithread()
{
	if(g_pUIThread != NULL)
	{
		AfxMessageBox("사용자 인터페이스 스레드가 실행중입니다.");
		return;
	}
	g_pUIThread = AfxBeginThread(RUNTIME_CLASS(CUIThread));
}

void CMainFrame::OnMenuResumethread()
{
	if(g_pUIThread != NULL)
		g_pUIThread->ResumeThread();
}

void CMainFrame::OnMenuSuspendthread()
{
	if(g_pUIThread != NULL)
		g_pUIThread->SuspendThread();
}

void CMainFrame::OnMenuExitthread()
{
	if(g_pUIThread != NULL)
		g_pUIThread->PostThreadMessage(WM_QUIT, NULL, NULL);
}
