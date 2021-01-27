#pragma once
#include "afxwin.h"


// CGameRoomProfileDlg ��ȭ �����Դϴ�.

class CGameRoomProfileDlg : public CDialog
{
	DECLARE_DYNAMIC(CGameRoomProfileDlg)

public:
	CGameRoomProfileDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CGameRoomProfileDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_GAMEROOM_PROFILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CStatic ctrl_staticPicImage;

	CRect m_rect;
	CImage m_image;

	void SetProfile(CString name, CString imageName);

	afx_msg void OnPaint();
};
