#pragma once
#include "afxcmn.h"


// CJoinRoomDlg 대화 상자입니다.

class CJoinRoomDlg : public CDialog
{
	DECLARE_DYNAMIC(CJoinRoomDlg)

public:
	CJoinRoomDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CJoinRoomDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_JOIN_ROOM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_ip;
	int m_port;
	CIPAddressCtrl ctrl_ipAdress;

	CString IpAdressCtrlToString();
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();

};
