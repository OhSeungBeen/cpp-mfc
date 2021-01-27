// JoinDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "BINGO.h"
#include "JoinDlg.h"


// CJoinDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CJoinDlg, CDialog)

CJoinDlg::CJoinDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CJoinDlg::IDD, pParent)
{
}

CJoinDlg::~CJoinDlg()
{
}

void CJoinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CJoinDlg, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CJoinDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CJoinDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ȸ�� ���� ��ư
void CJoinDlg::OnBnClickedOk()
{
	CString name, id, pw;
	GetDlgItemText(IDC_EDIT_JOIN_NAME, name);
	GetDlgItemText(IDC_EDIT_JOIN_ID, id);
	GetDlgItemText(IDC_EDIT_JOIN_PW, pw);
	if(id.IsEmpty() || pw.IsEmpty() || name.IsEmpty())
	{
		AfxMessageBox("�ʼ�(NAME, ID, PASSWORD)�� �Է��� �ּ���.");
		return;
	}

	m_name = name;
	m_id = id;
	m_pw = pw;
	OnOK();
}

// ��� ��ư
void CJoinDlg::OnBnClickedCancel()
{
	OnCancel();
}


