
// CLIENTDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "ClientSocket.h"
#include "afxcmn.h"

// CCLIENTDlg 대화 상자
class CCLIENTDlg : public CDialog
{
// 생성입니다.
public:
	CCLIENTDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	
public:
	CClientSocket clientSocket;
	CIPAddressCtrl ctrl_ipAdress;
	CListBox ctrl_listLog;

	afx_msg void OnBnClickedBtnConnect();
	afx_msg void OnBnClickedBtnSend();
	afx_msg void OnBnClickedBtnLogSave();

	void AddLogString(CString str);
};
