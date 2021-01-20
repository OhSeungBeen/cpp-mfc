// FriendDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CATCHMIND.h"
#include "FriendDlg.h"
#include "Global.h"


// CFriendDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CFriendDlg, CDialog)

CFriendDlg::CFriendDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFriendDlg::IDD, pParent)
{

}

CFriendDlg::~CFriendDlg()
{
}

void CFriendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FRIEND, ctrl_listFriend);
}


BEGIN_MESSAGE_MAP(CFriendDlg, CDialog)
END_MESSAGE_MAP()


// CFriendDlg 메시지 처리기입니다.

BOOL CFriendDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	for(size_t i = 0; i < g_vMember.size(); i++)
	{
		ctrl_listFriend.AddString(g_vMember[i].name);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
