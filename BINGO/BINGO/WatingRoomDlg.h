#pragma once
#include "ProfileDlg.h"
#include "BINGO.h"
#include "afxcmn.h"
#include "CreateRoomDlg.h"
#include "GameRoomDlg.h"
#include "afxwin.h"

// CWatingRoomDlg ��ȭ �����Դϴ�.

class CWatingRoomDlg : public CDialog
{
	DECLARE_DYNAMIC(CWatingRoomDlg)

public:
	CWatingRoomDlg(CWnd* pParent);   // ǥ�� �������Դϴ�.
	virtual ~CWatingRoomDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_WATINGROOM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	
	void NoticeFullRoom();

	afx_msg void OnBnClickedBtnCreateRoom();
	afx_msg void OnBnClickedBtnJoinRoom();
};
