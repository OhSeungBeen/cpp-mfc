
// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "CALCULATOR.h"

#include "MainFrm.h"
#include "CALCULATORDlg.h"
#include "CalCulatorMonitorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_CALCULATOR_EXCUTE, &CMainFrame::OnCalculatorExcute)
	ON_MESSAGE(WM_USER_MESSAGE, UserMessageFunc)
	ON_WM_DESTROY()
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
	
	m_pCalculatorMonitorDlg = new CCalCulatorMonitorDlg;
	m_pCalculatorMonitorDlg->Create(IDD_CALCULATOR_MONITOR, this);
	m_pCalculatorMonitorDlg->ShowWindow(SW_SHOW);

	CDialog* pCalculatorDlg = new CCALCULATORDlg;
	pCalculatorDlg->Create(IDD_CALCULATOR, this);
	pCalculatorDlg->ShowWindow(SW_SHOW);
	m_pCalCulatorDlgList.AddTail(pCalculatorDlg);


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

void CMainFrame::OnCalculatorExcute()
{
	if (m_pCalCulatorDlgList.GetCount() >= 10)
	{
		AfxMessageBox("10개이상 계산기를 실행 할 수 없습니다.");
		return;
	}
	CDialog* pCalculatorDlg = new CCALCULATORDlg;
	pCalculatorDlg->Create(IDD_CALCULATOR, this);
	pCalculatorDlg->ShowWindow(SW_SHOW);
	m_pCalCulatorDlgList.AddTail(pCalculatorDlg);
}

LRESULT CMainFrame::UserMessageFunc(WPARAM wParam, LPARAM lParam)
{	
	POSITION pos = m_pCalCulatorDlgList.GetHeadPosition();
	while(pos != NULL)
	{
		CDialog* pCalculatorDlg = (CDialog*)m_pCalCulatorDlgList.GetNext(pos);
		if(pCalculatorDlg == (CDialog*)lParam)
		{
			POSITION removePos = m_pCalCulatorDlgList.Find(pCalculatorDlg);
			m_pCalCulatorDlgList.RemoveAt(removePos);
		}
	}
	return 0;
}

void CMainFrame::OnDestroy()
{
	CMDIFrameWnd::OnDestroy();

	POSITION pos = m_pCalCulatorDlgList.GetHeadPosition();
	while(pos != NULL)
	{
		CDialog* pCalculatorDlg = (CDialog*)m_pCalCulatorDlgList.GetNext(pos);
	    POSITION removePos = m_pCalCulatorDlgList.Find(pos);
		m_pCalCulatorDlgList.RemoveAt(removePos);
	}

	delete m_pCalculatorMonitorDlg;
}
