#pragma once


// CJoinDlg ��ȭ �����Դϴ�.

class CJoinDlg : public CDialog
{
	DECLARE_DYNAMIC(CJoinDlg)

public:
	CJoinDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CJoinDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_JOIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();

	CString m_name;
	CString m_id;
	CString m_pw;
};
