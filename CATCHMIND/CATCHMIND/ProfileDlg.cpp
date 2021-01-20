// ProfileDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CATCHMIND.h"
#include "ProfileDlg.h"
#include "Global.h"

// CProfileDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CProfileDlg, CDialog)

CProfileDlg::CProfileDlg(CWnd* pParent /*=NULL*/,CString name, CString id, CString imageName )
	: CDialog(CProfileDlg::IDD, pParent)
{
	m_name = name;
	m_id = id;
	m_imageName = imageName;
}


CProfileDlg::~CProfileDlg()
{
}

void CProfileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_IMAGE, ctrl_pictureImage);
}


BEGIN_MESSAGE_MAP(CProfileDlg, CDialog)

	ON_WM_PAINT()
END_MESSAGE_MAP()


// CProfileDlg �޽��� ó�����Դϴ�.

BOOL CProfileDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemText(IDC_EDIT_PROFILE_NAME, m_name);
	SetDlgItemText(IDC_EDIT_PROFILE_ID, m_id);
	
	GetDlgItem(IDC_PIC_IMAGE)->GetWindowRect(m_rect);
	ScreenToClient(m_rect);
	CString imageName = m_imageName;
	CString imagePath = "profileImage\\" + imageName;
	m_image.Load(imagePath);
	InvalidateRect(m_rect, FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CProfileDlg::OnPaint()
{
	if(!m_image.IsNull())
	{
		CPaintDC dc(this); // device context for painting
		dc.SetStretchBltMode(COLORONCOLOR);
		m_image.Draw(dc, m_rect);
	}
}
