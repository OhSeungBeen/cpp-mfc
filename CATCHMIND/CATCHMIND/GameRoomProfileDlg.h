#pragma once
#include "afxwin.h"


// CGameRoomProfileDlg 대화 상자입니다.

class CGameRoomProfileDlg : public CDialog
{
	DECLARE_DYNAMIC(CGameRoomProfileDlg)

public:
	CGameRoomProfileDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CGameRoomProfileDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_GAMEROOM_PROFILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CStatic ctrl_staticPicImage;

	CRect m_rect;
	CImage m_image;

	void SetProfile(CString name, CString imageName);

	afx_msg void OnPaint();
};
