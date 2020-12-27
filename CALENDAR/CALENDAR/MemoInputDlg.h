#pragma once
#include "afxdtctl.h"


// CMemoInputDlg 대화 상자입니다.

class CMemoInputDlg : public CDialog
{
	DECLARE_DYNAMIC(CMemoInputDlg)

public:
	CMemoInputDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMemoInputDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MEMO_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	CString m_content;
	CString m_time;

	afx_msg void OnBnClickedOk();
	CDateTimeCtrl ctrl_datePicker;
};
