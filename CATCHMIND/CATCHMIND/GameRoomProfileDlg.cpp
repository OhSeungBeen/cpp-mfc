// GameRoomProfileDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CATCHMIND.h"
#include "GameRoomProfileDlg.h"

// CGameRoomProfileDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CGameRoomProfileDlg, CDialog)

CGameRoomProfileDlg::CGameRoomProfileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGameRoomProfileDlg::IDD, pParent)
{

}

CGameRoomProfileDlg::~CGameRoomProfileDlg()
{
}

void CGameRoomProfileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_IMAGE, ctrl_staticPicImage);
}


BEGIN_MESSAGE_MAP(CGameRoomProfileDlg, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CGameRoomProfileDlg 메시지 처리기입니다.

BOOL CGameRoomProfileDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;  
}

void CGameRoomProfileDlg::SetProfile(CString name, CString imageName)
{
	SetDlgItemText(IDC_EDIT_PROFILE_NAME, name);

	GetDlgItem(IDC_PIC_IMAGE)->GetWindowRect(m_rect);
	ScreenToClient(m_rect);
	CString imagePath = "profileImage\\" + imageName;
	m_image.Load(imagePath);
	InvalidateRect(m_rect, FALSE);
}


void CGameRoomProfileDlg::OnPaint()
{
	if(!m_image.IsNull())
	{
		 // device context for painting
		CPaintDC dc(this);
		dc.SetStretchBltMode(COLORONCOLOR);
		m_image.Draw(dc, m_rect);
	}
	CDialog::OnPaint();
}
