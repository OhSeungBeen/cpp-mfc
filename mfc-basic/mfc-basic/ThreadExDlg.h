#pragma once

// CThreadEx ��ȭ �����Դϴ�.

class CThreadExDlg : public CDialog
{
	DECLARE_DYNAMIC(CThreadExDlg)

public:
	CThreadExDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CThreadExDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_THREAD_EX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonRunNotepad();
};
