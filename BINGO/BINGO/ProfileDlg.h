#pragma once
#include "BINGO.h"
#include "afxwin.h"

// CProfileDlg ��ȭ �����Դϴ�.

class CProfileDlg : public CDialog
{
	DECLARE_DYNAMIC(CProfileDlg)

public:
	CProfileDlg(CString name, CString id);   // ǥ�� �������Դϴ�.
	virtual ~CProfileDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_PROFILE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	CString m_name;
	CString m_id;
};
