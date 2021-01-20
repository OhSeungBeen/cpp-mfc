#pragma once
#include "CATCHMIND.h"
#include "afxwin.h"

// CProfileDlg ��ȭ �����Դϴ�.

class CProfileDlg : public CDialog
{
	DECLARE_DYNAMIC(CProfileDlg)

public:
	CProfileDlg(CWnd* pParent, CString name, CString id, CString imageName );   // ǥ�� �������Դϴ�.
	virtual ~CProfileDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_PROFILE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();

	CStatic ctrl_pictureImage;

	CRect m_rect;
	CImage m_image;

	CString m_name;
	CString m_id;
	CString m_imageName;

};
