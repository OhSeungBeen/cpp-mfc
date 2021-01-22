#pragma once
#include "ProfileDlg.h"
#include "CATCHMIND.h"
#include "afxcmn.h"
#include "CreateRoomDlg.h"
#include "GameRoomDlg.h"
#include "afxwin.h"

// CWatingRoomDlg ��ȭ �����Դϴ�.

class CWatingRoomDlg : public CDialog
{
	DECLARE_DYNAMIC(CWatingRoomDlg)

public:
	CWatingRoomDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CWatingRoomDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_WATINGROOM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	void NoticeFullRoom();
	void NoticeIncorrectPassword();
	void NoticeAccept();

	afx_msg void OnProfile();
	afx_msg void OnBnClickedBtnCreateRoom();
	afx_msg void OnBnClickedBtnJoinRoom();
	afx_msg void OnBnClickedBtnCapture();
	afx_msg void OnBnClickedBtnGameStart();
	afx_msg void OnBnClickedBtnCreateRoomSerial();

};
