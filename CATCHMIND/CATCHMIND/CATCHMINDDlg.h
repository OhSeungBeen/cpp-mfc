
// CATCHMINDDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "Global.h"
#include "JoinDlg.h"
#include "LoginDlg.h"
#include "WatingRoomDlg.h"
#include "GameRoomDlg.h"

#define LOGIN_ROOM 1
#define WATING_ROOM 2
#define GAME_ROOM 3

// CCATCHMINDDlg 대화 상자
class CCATCHMINDDlg : public CDialog
{
// 생성입니다.
public:
	CCATCHMINDDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CATCHMIND_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	
public:
	void ChangeDlg(int preDlg, int newDlg);

	CLoginDlg* m_loginDlg;
	CWatingRoomDlg* m_watingRoomDlg;
	CGameRoomDlg* m_gameRoomDlg;

	afx_msg void OnUpdateProfile(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFriendView(CCmdUI *pCmdUI);
	afx_msg void OnProfile();
	afx_msg void OnFriendView();
	afx_msg void OnBnClickedBtnCapture();
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnLogPath();
};
