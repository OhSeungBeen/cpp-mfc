
// CATCHMINDSERVERDlg.h : ��� ����
//

#pragma once
#include "ListenSocket.h"

// CCATCHMINDSERVERDlg ��ȭ ����
class CCATCHMINDSERVERDlg : public CDialog
{
// �����Դϴ�.
public:
	CCATCHMINDSERVERDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CATCHMINDSERVER_DIALOG };

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
	CListenSocket m_serverSocket;

};
