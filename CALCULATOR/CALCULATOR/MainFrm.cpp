
// MainFrm.cpp : CMainFrame Ŭ������ ����
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
	ID_SEPARATOR,           // ���� �� ǥ�ñ�
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/�Ҹ�

CMainFrame::CMainFrame()
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
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
		TRACE0("���� ǥ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return TRUE;
}

// CMainFrame ����

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


// CMainFrame �޽��� ó����

void CMainFrame::OnCalculatorExcute()
{
	if (m_pCalCulatorDlgList.GetCount() >= 10)
	{
		AfxMessageBox("10���̻� ���⸦ ���� �� �� �����ϴ�.");
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
