
// SERVERDlg.h : ��� ����
//

#pragma once
#include "ListenSocket.h"
#include "afxwin.h"
#include "afxcmn.h"

// CSERVERDlg ��ȭ ����
class CSERVERDlg : public CDialog
{
// �����Դϴ�.
public:
	CSERVERDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SERVER_DIALOG };

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
	CListenSocket serverSocket;

	CListBox ctrl_listLog;
	CIPAddressCtrl ctrl_ipAdress;
	CEdit ctrl_editPort;

	void AddLogString(CString str);
	
	afx_msg void OnBnClickedBtnOppen();
	afx_msg void OnBnClickedBtnLogSave();
	afx_msg void OnBnClickedBtnSend();
};
