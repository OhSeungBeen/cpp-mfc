#pragma once
#include "afxwin.h"


// CTapOneDlg 대화 상자입니다.

class CTapOneDlg : public CDialog
{
	DECLARE_DYNAMIC(CTapOneDlg)

public:
	CTapOneDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTapOneDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TAP_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl ctrl_listMemo;
};
