#pragma once
#include "ProfileDlg.h"
#include "CATCHMIND.h"

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
	afx_msg void OnProfile();
};
