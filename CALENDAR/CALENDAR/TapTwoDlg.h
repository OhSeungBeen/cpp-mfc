#pragma once
#include "afxwin.h"


// CTapTwoDlg 대화 상자입니다.

class CTapTwoDlg : public CDialog
{
	DECLARE_DYNAMIC(CTapTwoDlg)

public:
	CTapTwoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTapTwoDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TAP_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl ctrl_listMemo;
};
