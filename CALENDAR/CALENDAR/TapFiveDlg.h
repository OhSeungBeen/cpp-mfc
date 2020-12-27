#pragma once
#include "afxwin.h"


// CTapFiveDlg 대화 상자입니다.

class CTapFiveDlg : public CDialog
{
	DECLARE_DYNAMIC(CTapFiveDlg)

public:
	CTapFiveDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTapFiveDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TAP_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl ctrl_listMemo;
};
