#pragma once
#include "MFCBasic.h"

// CKeyboardDlg ��ȭ �����Դϴ�.

class CKeyboardDlg : public CDialog
{
	DECLARE_DYNAMIC(CKeyboardDlg)

public:
	CKeyboardDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CKeyboardDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_KEYBOARDDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
