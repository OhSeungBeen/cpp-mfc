// ProfileDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CATCHMIND.h"
#include "ProfileDlg.h"
#include "Global.h"

// CProfileDlg ��ȭ �����Դϴ�.

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


// CProfileDlg �޽��� ó�����Դϴ�.

BOOL CProfileDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemText(IDC_EDIT_PROFILE_NAME, g_clientSocket.m_profileInfo.name);
	SetDlgItemText(IDC_EDIT_PROFILE_ID, g_clientSocket.m_profileInfo.id);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
