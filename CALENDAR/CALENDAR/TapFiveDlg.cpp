// TapFiveDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CALENDAR.h"
#include "TapFiveDlg.h"


// CTapFiveDlg ��ȭ �����Դϴ�.

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


// CTapFiveDlg �޽��� ó�����Դϴ�.
