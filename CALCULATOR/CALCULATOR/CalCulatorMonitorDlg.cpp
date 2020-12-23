// CalCulatorMonitorDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CALCULATOR.h"
#include "CalCulatorMonitorDlg.h"


// CCalCulatorMonitorDlg ��ȭ �����Դϴ�.

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


// CCalCulatorMonitorDlg �޽��� ó�����Դϴ�.
LRESULT CCalCulatorMonitorDlg::UserMessageFunc(WPARAM wParam, LPARAM lParam)
{	
	CString strTemp;
	CString *a = (CString *)lParam;
	strTemp.Format("%p���� ���⿡�� ��� : %s", wParam, a->GetString());
	ctrl_listMonitor.AddString(strTemp);
	return 0;
}