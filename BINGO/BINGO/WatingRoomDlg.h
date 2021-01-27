#pragma once
#include "ProfileDlg.h"
#include "BINGO.h"
#include "afxcmn.h"
#include "CreateRoomDlg.h"
#include "GameRoomDlg.h"
#include "afxwin.h"

// CWatingRoomDlg 대화 상자입니다.

class CWatingRoomDlg : public CDialog
{
	DECLARE_DYNAMIC(CWatingRoomDlg)

public:
	CWatingRoomDlg(CWnd* pParent);   // 표준 생성자입니다.
	virtual ~CWatingRoomDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_WATINGROOM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	
	void NoticeFullRoom();

	afx_msg void OnBnClickedBtnCreateRoom();
	afx_msg void OnBnClickedBtnJoinRoom();
};
