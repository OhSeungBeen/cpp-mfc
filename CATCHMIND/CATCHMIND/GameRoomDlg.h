#pragma once
#include "afxwin.h"
#include "Data.h"
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
	bool m_lButtonClick;
	CPoint m_prePoint;
	COLORREF m_rgb;
	int m_thickness;
	int m_mode;

	CListBox ctrl_listChatMsg;
	CListBox ctrl_listUser;
	CComboBox ctrl_comThinkness;
	CComboBox ctrl_comColor;
	CEdit ctrl_editQuiz;

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void SetMode(int mode);
	void SetQuiz(CString quiz);

	afx_msg void OnBnClickedBtnSendMessage();
	afx_msg void OnBnClickedBtnProfile();
	afx_msg void OnBnClickedBtnCapture();
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnCbnSelchangeComboThinkness();
	afx_msg void OnCbnSelchangeComboColor();
	
	afx_msg LRESULT OnDisConnect( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnRecvChatMsg(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDraw(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserProfileSave( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnOneUserProfileSave(WPARAM wParam, LPARAM lParam);
	
};
