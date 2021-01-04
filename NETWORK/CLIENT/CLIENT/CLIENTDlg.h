
// CLIENTDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "ClientSocket.h"
#include "afxcmn.h"

// CCLIENTDlg ��ȭ ����
class CCLIENTDlg : public CDialog
{
// �����Դϴ�.
public:
	CCLIENTDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
