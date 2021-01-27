#pragma once
#include "afxwin.h"


// CFriendDlg 대화 상자입니다.

class CFriendDlg : public CDialog
{
	DECLARE_DYNAMIC(CFriendDlg)

public:
	CFriendDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CFriendDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_FRIEND_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox ctrl_listFriend;
	virtual BOOL OnInitDialog();
};
