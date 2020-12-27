
// CALENDARDlg.h : ��� ����
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

// CCALENDARDlg ��ȭ ����
class CCALENDARDlg : public CDialog
{
// �����Դϴ�.
public:
	CCALENDARDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CALENDAR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
