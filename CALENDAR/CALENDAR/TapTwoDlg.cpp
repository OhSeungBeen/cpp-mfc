// TapTwoDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CALENDAR.h"
#include "TapTwoDlg.h"


// CTapTwoDlg ��ȭ �����Դϴ�.

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


// CTapTwoDlg �޽��� ó�����Դϴ�.
