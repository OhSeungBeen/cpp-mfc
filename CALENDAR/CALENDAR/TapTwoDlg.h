#pragma once
#include "afxwin.h"


// CTapTwoDlg ��ȭ �����Դϴ�.

class CTapTwoDlg : public CDialog
{
	DECLARE_DYNAMIC(CTapTwoDlg)

public:
	CTapTwoDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTapTwoDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TAP_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl ctrl_listMemo;
};
