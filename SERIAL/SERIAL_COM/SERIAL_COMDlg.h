
// SERIAL_COMDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "Serial.h"
#define  WM_RECEIVEDATA WM_USER + 1

// CSERIAL_COMDlg ��ȭ ����
class CSERIAL_COMDlg : public CDialog
{
// �����Դϴ�.
public:
	CSERIAL_COMDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SERIAL_COM_DIALOG };

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
	CSerial m_Serial;

	CComboBox ctrl_comboPort;
	CComboBox ctrl_comboBaundRate;
	CComboBox ctrl_comboDatabits;
	CComboBox ctrl_comboStopbits;
	CComboBox ctrl_comboParity;
	CListBox ctrl_listLog;
	
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedBtnSend();
	afx_msg void OnClose();

	afx_msg LRESULT OnReceiveData(UINT,LONG);
	afx_msg void OnBnClickedBtnLogSave();
};
