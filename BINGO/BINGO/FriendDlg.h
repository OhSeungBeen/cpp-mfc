#pragma once
#include "afxwin.h"


// CFriendDlg ��ȭ �����Դϴ�.

class CFriendDlg : public CDialog
{
	DECLARE_DYNAMIC(CFriendDlg)

public:
	CFriendDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CFriendDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_FRIEND_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListBox ctrl_listFriend;
	virtual BOOL OnInitDialog();
};
