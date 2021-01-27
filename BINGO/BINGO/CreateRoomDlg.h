#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// CCreateRoomDlg ��ȭ �����Դϴ�.

class CCreateRoomDlg : public CDialog
{
	DECLARE_DYNAMIC(CCreateRoomDlg)

public:
	CCreateRoomDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCreateRoomDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CREATE_ROOM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_bingo;
	CString m_ip;
	int m_port;

	CIPAddressCtrl ctrl_ipAdress;
	CEdit ctrl_editPort;
	CComboBox ctrl_comBingo;

	virtual BOOL OnInitDialog();

	CString IpAdressCtrlToString();
	afx_msg void OnBnClickedOk();
};

