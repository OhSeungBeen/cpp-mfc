
// SERIAL_COMDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "Serial.h"
#define  WM_RECEIVEDATA WM_USER + 1

// CSERIAL_COMDlg 대화 상자
class CSERIAL_COMDlg : public CDialog
{
// 생성입니다.
public:
	CSERIAL_COMDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SERIAL_COM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
