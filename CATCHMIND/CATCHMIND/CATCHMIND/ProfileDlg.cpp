// ProfileDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CATCHMIND.h"
#include "ProfileDlg.h"
#include "Global.h"

// CProfileDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CProfileDlg, CDialog)

CProfileDlg::CProfileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProfileDlg::IDD, pParent)
{
	
}


CProfileDlg::~CProfileDlg()
{
}

void CProfileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProfileDlg, CDialog)

END_MESSAGE_MAP()


// CProfileDlg 메시지 처리기입니다.

BOOL CProfileDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemText(IDC_EDIT_PROFILE_NAME, g_clientSocket.m_profileInfo.name);
	SetDlgItemText(IDC_EDIT_PROFILE_ID, g_clientSocket.m_profileInfo.id);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
