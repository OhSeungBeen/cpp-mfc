// TapOneDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CALENDAR.h"
#include "TapOneDlg.h"


// CTapOneDlg ��ȭ �����Դϴ�.

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


// CTapOneDlg �޽��� ó�����Դϴ�.
