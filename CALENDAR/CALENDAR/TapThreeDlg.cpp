// TapThreeDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CALENDAR.h"
#include "TapThreeDlg.h"


// CTapThreeDlg ��ȭ �����Դϴ�.

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


// CTapThreeDlg �޽��� ó�����Դϴ�.
