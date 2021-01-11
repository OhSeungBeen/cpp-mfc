#pragma once
#include "CATCHMIND.h"

// CProfileDlg 대화 상자입니다.

class CProfileDlg : public CDialog
{
	DECLARE_DYNAMIC(CProfileDlg)

public:
	CProfileDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CProfileDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PROFILE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
