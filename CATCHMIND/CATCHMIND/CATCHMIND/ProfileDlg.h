#pragma once
#include "CATCHMIND.h"

// CProfileDlg ��ȭ �����Դϴ�.

class CProfileDlg : public CDialog
{
	DECLARE_DYNAMIC(CProfileDlg)

public:
	CProfileDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CProfileDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_PROFILE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
