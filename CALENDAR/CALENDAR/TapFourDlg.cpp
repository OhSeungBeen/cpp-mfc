// TapFourDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CALENDAR.h"
#include "TapFourDlg.h"


// CTapFourDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTapFourDlg, CDialog)

CTapFourDlg::CTapFourDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTapFourDlg::IDD, pParent)
{

}

CTapFourDlg::~CTapFourDlg()
{
}

void CTapFourDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MEMO4, ctrl_listMemo);
}


BEGIN_MESSAGE_MAP(CTapFourDlg, CDialog)
END_MESSAGE_MAP()


// CTapFourDlg 메시지 처리기입니다.
