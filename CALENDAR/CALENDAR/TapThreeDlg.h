#pragma once
#include "afxwin.h"


// CTapThreeDlg 대화 상자입니다.

class CTapThreeDlg : public CDialog
{
	DECLARE_DYNAMIC(CTapThreeDlg)

public:
	CTapThreeDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTapThreeDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TAP_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl ctrl_listMemo;
};
