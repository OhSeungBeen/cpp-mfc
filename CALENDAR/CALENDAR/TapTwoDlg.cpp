// TapTwoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CALENDAR.h"
#include "TapTwoDlg.h"


// CTapTwoDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTapTwoDlg, CDialog)

CTapTwoDlg::CTapTwoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTapTwoDlg::IDD, pParent)
{

}

CTapTwoDlg::~CTapTwoDlg()
{
}

void CTapTwoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MEMO2, ctrl_listMemo);
}


BEGIN_MESSAGE_MAP(CTapTwoDlg, CDialog)
END_MESSAGE_MAP()


// CTapTwoDlg 메시지 처리기입니다.
