#pragma once

// CThreadEx 대화 상자입니다.

class CThreadExDlg : public CDialog
{
	DECLARE_DYNAMIC(CThreadExDlg)

public:
	CThreadExDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CThreadExDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_THREAD_EX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMenuThreadEx();
	afx_msg void OnBnClickedButtonRunNotepad();
};
