#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// CCreateRoomDlg 대화 상자입니다.

class CCreateRoomDlg : public CDialog
{
	DECLARE_DYNAMIC(CCreateRoomDlg)

public:
	CCreateRoomDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCreateRoomDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CREATE_ROOM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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

