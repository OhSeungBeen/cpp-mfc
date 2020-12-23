// CalCulatorMonitorDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CALCULATOR.h"
#include "CalCulatorMonitorDlg.h"


// CCalCulatorMonitorDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCalCulatorMonitorDlg, CDialog)

CCalCulatorMonitorDlg::CCalCulatorMonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCalCulatorMonitorDlg::IDD, pParent)
{

}

CCalCulatorMonitorDlg::~CCalCulatorMonitorDlg()
{
}

void CCalCulatorMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MONITOR, ctrl_listMonitor);
}


BEGIN_MESSAGE_MAP(CCalCulatorMonitorDlg, CDialog)
	ON_MESSAGE(WM_USER_MESSAGE2, UserMessageFunc)
END_MESSAGE_MAP()


// CCalCulatorMonitorDlg 메시지 처리기입니다.
LRESULT CCalCulatorMonitorDlg::UserMessageFunc(WPARAM wParam, LPARAM lParam)
{	
	CString strTemp;
	CString *a = (CString *)lParam;
	strTemp.Format("%p번지 계산기에서 결과 : %s", wParam, a->GetString());
	ctrl_listMonitor.AddString(strTemp);
	return 0;
}