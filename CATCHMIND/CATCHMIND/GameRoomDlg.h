#pragma once
#include "afxwin.h"
#include "Data.h"
#include <vector>

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
	CPoint m_startPoint;
	CPoint m_endPoint;
	COLORREF m_rgb;
	int m_thickness;
	int m_mode;

	CListBox ctrl_listChatMsg;
	CListBox ctrl_listProfile;
	CComboBox ctrl_comThinkness;
	CComboBox ctrl_comColor;
	CEdit ctrl_editQuiz;
	
	int m_preMilliSec;
	int m_nowMilliSec;
	int m_miliseconds;
	int m_seconds;
	int m_minute;
	int m_hour;

	CWinThread* m_pTimeThread;

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void AddProfileToList(Profile* profile);
	void AddProfilesToList(std::vector<Profile>* vProfile);
	void AddMessageToList(CString name, CString message);
	void SetMode(int mode);
	void SetQuiz(CString quiz);
	void Draw(Point* point);
	void Clear();

	afx_msg void OnBnClickedBtnSendMessage();
	afx_msg void OnBnClickedBtnProfile();
	afx_msg void OnBnClickedBtnCapture();
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnCbnSelchangeComboThinkness();
	afx_msg void OnCbnSelchangeComboColor();
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnBnClickedBtnSerialModeOrder();

	afx_msg LRESULT OnDisConnect( WPARAM wParam, LPARAM lParam );

	afx_msg void OnPaint();
};
UINT TimeThread(LPVOID pParam) /* 반드시 UNIT형?반환해야되고 LPVOID형의 포인터를 인자 ?받아야한다. */;