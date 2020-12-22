#pragma once

// CThreadEx 대화 상자입니다.

class CWorkerThreadDlg : public CDialog
{
	DECLARE_DYNAMIC(CWorkerThreadDlg)

public:
	CWorkerThreadDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CWorkerThreadDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_THREADDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonRunNotepad();
};
