#pragma once
#include "afxwin.h"
#include "Data.h"
#include <vector>
#include "BingoPanelDlg.h"
// CGameRoomDlg 대화 상자입니다.

class CGameRoomDlg : public CDialog
{
	DECLARE_DYNAMIC(CGameRoomDlg)

public:
	CGameRoomDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CGameRoomDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_GAMEROOM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	CBingoPanelDlg* m_bingoPanelDlg[4];

	CListBox ctrl_listChatMsg;
	CComboBox ctrl_comColor;
	CEdit ctrl_editQuiz;
	COLORREF m_rgb;

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void RefreshProfile(std::vector<Profile> vProfile);
	void AddMessageToList(CString name, CString message);
	void SetMode(int mode);
	void SetQuiz(CString quiz);
	void GameStart(std::vector<CString> vWords);

	afx_msg void OnBnClickedBtnSendMessage();
	afx_msg void OnCbnSelchangeComboColor();
	afx_msg void OnBnClickedBtnGameSatrtReady();
};
