#pragma once

// CThreadEx ��ȭ �����Դϴ�.

class CWorkerThreadDlg : public CDialog
{
	DECLARE_DYNAMIC(CWorkerThreadDlg)

public:
	CWorkerThreadDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CWorkerThreadDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_THREADDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonRunNotepad();
};
