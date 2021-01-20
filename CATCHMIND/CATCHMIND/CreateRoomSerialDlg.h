#pragma once
#include "afxwin.h"


// CCreateRoomSerial ��ȭ �����Դϴ�.

class CCreateRoomSerialDlg : public CDialog
{
	DECLARE_DYNAMIC(CCreateRoomSerialDlg)

public:
	CCreateRoomSerialDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCreateRoomSerialDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ROOM_SERIAL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
