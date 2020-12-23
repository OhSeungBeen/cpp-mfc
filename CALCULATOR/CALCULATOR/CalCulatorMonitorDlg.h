#pragma once
#include "afxwin.h"


// CCalCulatorMonitorDlg 대화 상자입니다.

class CCalCulatorMonitorDlg : public CDialog
{
	DECLARE_DYNAMIC(CCalCulatorMonitorDlg)

public:
	CCalCulatorMonitorDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCalCulatorMonitorDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CALCULATOR_MONITOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	
	DECLARE_MESSAGE_MAP()

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT UserMessageFunc(WPARAM wParam, LPARAM lParam);
public:
	CListBox ctrl_listMonitor;
};
