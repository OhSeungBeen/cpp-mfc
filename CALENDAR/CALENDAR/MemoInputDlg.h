#pragma once
#include "afxdtctl.h"


// CMemoInputDlg ��ȭ �����Դϴ�.

class CMemoInputDlg : public CDialog
{
	DECLARE_DYNAMIC(CMemoInputDlg)

public:
	CMemoInputDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMemoInputDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MEMO_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	CString m_content;
	CString m_time;

	afx_msg void OnBnClickedOk();
	CDateTimeCtrl ctrl_datePicker;
};
