#pragma once
#include "afxwin.h"


// CCreateRoomSerial 대화 상자입니다.

class CCreateRoomSerialDlg : public CDialog
{
	DECLARE_DYNAMIC(CCreateRoomSerialDlg)

public:
	CCreateRoomSerialDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCreateRoomSerialDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ROOM_SERIAL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox ctrl_comboPort;
	CComboBox ctrl_comboBaundRate;
	CComboBox ctrl_comboDatabits;
	CComboBox ctrl_comboStopbits;
	CComboBox ctrl_comboParity;
	
	CString m_port;
	DWORD m_baudRate;
	byte m_parity, m_dataBit, m_stopBit;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
