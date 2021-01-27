// ProfileDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BINGO.h"
#include "ProfileDlg.h"
#include "Global.h"

// CProfileDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CProfileDlg, CDialog)

CProfileDlg::CProfileDlg(CString name, CString id)
	: CDialog(CProfileDlg::IDD)
{
	m_name = name;
	m_id = id;
}


CProfileDlg::~CProfileDlg()
{
}

void CProfileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProfileDlg, CDialog)

	ON_WM_PAINT()
END_MESSAGE_MAP()


// CProfileDlg 메시지 처리기입니다.

BOOL CProfileDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemText(IDC_EDIT_PROFILE_NAME, m_name);
	SetDlgItemText(IDC_EDIT_PROFILE_ID, m_id);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

