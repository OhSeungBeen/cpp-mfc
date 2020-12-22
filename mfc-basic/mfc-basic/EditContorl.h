#pragma once
#include "MFCBasic.h"

// CEditContorl 대화 상자입니다.

class CEditContorl : public CDialog
{
	DECLARE_DYNAMIC(CEditContorl)

public:
	CEditContorl(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CEditContorl();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_EDITCONTROLDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strEditId; // EditControl ID = IDC_Edit_Id
	CString m_strEditPassword;
	afx_msg void OnBnClickedButtonOk();
};
