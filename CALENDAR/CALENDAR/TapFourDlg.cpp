// TapFourDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CALENDAR.h"
#include "TapFourDlg.h"


// CTapFourDlg ��ȭ �����Դϴ�.

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


// CTapFourDlg �޽��� ó�����Դϴ�.
