// TapThreeDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CALENDAR.h"
#include "TapThreeDlg.h"


// CTapThreeDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTapThreeDlg, CDialog)

CTapThreeDlg::CTapThreeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTapThreeDlg::IDD, pParent)
{

}

CTapThreeDlg::~CTapThreeDlg()
{
}

void CTapThreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MEMO3, ctrl_listMemo);
}


BEGIN_MESSAGE_MAP(CTapThreeDlg, CDialog)
END_MESSAGE_MAP()


// CTapThreeDlg 메시지 처리기입니다.
