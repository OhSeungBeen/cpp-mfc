#pragma once
#include "afxwin.h"


// CTapFourDlg ��ȭ �����Դϴ�.

class CTapFourDlg : public CDialog
{
	DECLARE_DYNAMIC(CTapFourDlg)

public:
	CTapFourDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTapFourDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TAP_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl ctrl_listMemo;
};
