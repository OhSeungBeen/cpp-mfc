#pragma once

// CThreadEx ��ȭ �����Դϴ�.

class CWorkThread : public CDialog
{
	DECLARE_DYNAMIC(CWorkThread)

public:
	CWorkThread(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CWorkThread();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_THREAD_EX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonRunNotepad();
};
