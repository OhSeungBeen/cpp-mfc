#pragma once
#include "afxcmn.h"


// CJoinRoomDlg ��ȭ �����Դϴ�.

class CJoinRoomDlg : public CDialog
{
	DECLARE_DYNAMIC(CJoinRoomDlg)

public:
	CJoinRoomDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CJoinRoomDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_JOIN_ROOM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_ip;
	int m_port;
	CIPAddressCtrl ctrl_ipAdress;

	CString IpAdressCtrlToString();
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();

};
