#pragma once
#include "MFCBasic.h"

// CEditContorl ��ȭ �����Դϴ�.

class CEditContorl : public CDialog
{
	DECLARE_DYNAMIC(CEditContorl)

public:
	CEditContorl(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CEditContorl();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_EDITCONTROLDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strEditId; // EditControl ID = IDC_Edit_Id
	CString m_strEditPassword;
	afx_msg void OnBnClickedButtonOk();
};
