#pragma once


// CJoinDlg 대화 상자입니다.

class CJoinDlg : public CDialog
{
	DECLARE_DYNAMIC(CJoinDlg)

public:
	CJoinDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CJoinDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_JOIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();

	CString m_name;
	CString m_id;
	CString m_pw;
};
