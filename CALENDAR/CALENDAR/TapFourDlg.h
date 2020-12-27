#pragma once
#include "afxwin.h"


// CTapFourDlg 대화 상자입니다.

class CTapFourDlg : public CDialog
{
	DECLARE_DYNAMIC(CTapFourDlg)

public:
	CTapFourDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTapFourDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TAP_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl ctrl_listMemo;
};
