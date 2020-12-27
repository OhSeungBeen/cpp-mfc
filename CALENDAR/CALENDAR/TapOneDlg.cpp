// TapOneDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CALENDAR.h"
#include "TapOneDlg.h"


// CTapOneDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTapOneDlg, CDialog)

CTapOneDlg::CTapOneDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTapOneDlg::IDD, pParent)
{

}

CTapOneDlg::~CTapOneDlg()
{
}

void CTapOneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MEMO, ctrl_listMemo);
}


BEGIN_MESSAGE_MAP(CTapOneDlg, CDialog)
END_MESSAGE_MAP()


// CTapOneDlg 메시지 처리기입니다.
