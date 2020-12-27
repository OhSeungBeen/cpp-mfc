// TapFiveDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CALENDAR.h"
#include "TapFiveDlg.h"


// CTapFiveDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTapFiveDlg, CDialog)

CTapFiveDlg::CTapFiveDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTapFiveDlg::IDD, pParent)
{

}

CTapFiveDlg::~CTapFiveDlg()
{
}

void CTapFiveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MEMO5, ctrl_listMemo);
}


BEGIN_MESSAGE_MAP(CTapFiveDlg, CDialog)
END_MESSAGE_MAP()


// CTapFiveDlg 메시지 처리기입니다.
