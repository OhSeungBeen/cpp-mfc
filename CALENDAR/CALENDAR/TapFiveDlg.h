#pragma once
#include "afxwin.h"


// CTapFiveDlg ��ȭ �����Դϴ�.

class CTapFiveDlg : public CDialog
{
	DECLARE_DYNAMIC(CTapFiveDlg)

public:
	CTapFiveDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTapFiveDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TAP_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl ctrl_listMemo;
};
