// MemoInputDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CALENDAR.h"
#include "MemoInputDlg.h"


// CMemoInputDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMemoInputDlg, CDialog)

CMemoInputDlg::CMemoInputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMemoInputDlg::IDD, pParent)
{

}

CMemoInputDlg::~CMemoInputDlg()
{
}

void CMemoInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER, ctrl_datePicker);
}


BEGIN_MESSAGE_MAP(CMemoInputDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CMemoInputDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMemoInputDlg 메시지 처리기입니다.

void CMemoInputDlg::OnBnClickedOk()
{	
	CString strTemp;
	GetDlgItemText(IDC_EDIT_CONTENT, strTemp);
	m_content = strTemp;
	CTime cTime;
	ctrl_datePicker.GetTime(cTime);
	strTemp.Format("%02d:%02d:%02d", cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());
	m_time = strTemp;
	OnOK();
}
