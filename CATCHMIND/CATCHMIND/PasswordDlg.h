#pragma once


// CPasswordDlg ��ȭ �����Դϴ�.

class CPasswordDlg : public CDialog
{
	DECLARE_DYNAMIC(CPasswordDlg)

public:
	CPasswordDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CPasswordDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_PASSWORD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	CString m_password;

	afx_msg void OnBnClickedOk();
};
