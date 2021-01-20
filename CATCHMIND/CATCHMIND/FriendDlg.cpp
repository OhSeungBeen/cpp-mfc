// FriendDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CATCHMIND.h"
#include "FriendDlg.h"
#include "Global.h"


// CFriendDlg ��ȭ �����Դϴ�.

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


// CFriendDlg �޽��� ó�����Դϴ�.

BOOL CFriendDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	for(size_t i = 0; i < g_vMember.size(); i++)
	{
		ctrl_listFriend.AddString(g_vMember[i].name);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
