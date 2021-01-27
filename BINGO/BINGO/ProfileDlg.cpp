// ProfileDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "BINGO.h"
#include "ProfileDlg.h"
#include "Global.h"

// CProfileDlg ��ȭ �����Դϴ�.

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


// CProfileDlg �޽��� ó�����Դϴ�.

BOOL CProfileDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemText(IDC_EDIT_PROFILE_NAME, m_name);
	SetDlgItemText(IDC_EDIT_PROFILE_ID, m_id);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

