
// CALENDARDlg.h : 헤더 파일
//

#pragma once
#include "afxdtctl.h"
#include "afxcmn.h"

#include "TapOneDlg.h"
#include "TapTwoDlg.h"
#include "TapThreeDlg.h"
#include "TapFourDlg.h"
#include "TapFiveDlg.h"

#include "MemoData.h"

// CCALENDARDlg 대화 상자
class CCALENDARDlg : public CDialog
{
// 생성입니다.
public:
	CCALENDARDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CALENDAR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	CPtrList m_pMemoDataList;
	CString m_date;

	afx_msg void OnMcnSelchangeMonthcalendar(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnMemoAdd();

	void InitTabContorl();
	void InitListContorl();
	void AddListItem(int tabNo, CString content, CString aram);
	void RemoveAllTabListItem();
	CString GetTimeString();
	CString GetDateString();

	CMonthCalCtrl ctrl_monthCal;
	CTabCtrl ctrl_tab;

	CWnd* m_pWndShow;
	CTapOneDlg m_tabOneDlg;
	CTapTwoDlg m_tabTwoDlg;
	CTapThreeDlg m_tabThreeDlg;
	CTapFourDlg m_tabFourDlg;
	CTapFiveDlg m_tabFiveDlg;

	CWinThread *m_pThread;
	HANDLE hThread;
	static UINT aramCheckThread(LPVOID pParam);
	afx_msg void OnBnClickedBtnMemoDelete();
	
};
