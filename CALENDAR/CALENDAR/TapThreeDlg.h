#pragma once
#include "afxwin.h"


// CTapThreeDlg ��ȭ �����Դϴ�.

class CTapThreeDlg : public CDialog
{
	DECLARE_DYNAMIC(CTapThreeDlg)

public:
	CTapThreeDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTapThreeDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TAP_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl ctrl_listMemo;
};
