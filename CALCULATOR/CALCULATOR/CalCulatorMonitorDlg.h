#pragma once
#include "afxwin.h"


// CCalCulatorMonitorDlg ��ȭ �����Դϴ�.

class CCalCulatorMonitorDlg : public CDialog
{
	DECLARE_DYNAMIC(CCalCulatorMonitorDlg)

public:
	CCalCulatorMonitorDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCalCulatorMonitorDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CALCULATOR_MONITOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	
	DECLARE_MESSAGE_MAP()

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT UserMessageFunc(WPARAM wParam, LPARAM lParam);
public:
	CListBox ctrl_listMonitor;
};
