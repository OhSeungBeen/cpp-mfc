#pragma once
#include "afxwin.h"


// CTapOneDlg ��ȭ �����Դϴ�.

class CTapOneDlg : public CDialog
{
	DECLARE_DYNAMIC(CTapOneDlg)

public:
	CTapOneDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTapOneDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TAP_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl ctrl_listMemo;
};
