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
	int m_userSize;
	bool m_privateRoom;
	CString m_password;
	CString m_ip;
	int m_port;

	CIPAddressCtrl ctrl_ipAdress;
	CEdit ctrl_editPort;
	CComboBox ctrl_comUserSize;
	CComboBox ctrl_comPrivate;

	virtual BOOL OnInitDialog();

	CString IpAdressCtrlToString();
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeComboRoomPrivate();
};

