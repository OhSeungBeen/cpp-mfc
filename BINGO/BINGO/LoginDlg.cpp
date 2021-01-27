// LoginDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "BINGO.h"
#include "BINGODlg.h"
#include "LoginDlg.h"
#include "JoinDlg.h"
#include "Global.h"

// CLoginDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CLoginDlg, CDialog)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
{
		
}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	ON_BN_CLICKED(IDD_BTN_LOGIN, &CLoginDlg::OnBnClickedBtnLogin)
	ON_BN_CLICKED(IDD_BTN_JOIN, &CLoginDlg::OnBnClickedBtnJoin)
END_MESSAGE_MAP()


// CLoginDlg �޽��� ó�����Դϴ�.

BOOL CLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	CFont fnt;
	LOGFONT lf;
	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 50;
	lf.lfWeight = FW_BOLD;
	::lstrcpy(lf.lfFaceName, "Tahoma");
	fnt.CreateFontIndirect(&lf);
	GetDlgItem(IDD_STATIC)->SetFont(&fnt);
	fnt.Detach();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

// Member Join Button
void CLoginDlg::OnBnClickedBtnJoin()
{
	CJoinDlg joinDlg;

	if(joinDlg.DoModal() == IDOK)
	{

		int result = g_dataBase.InsertMember(joinDlg.m_id, joinDlg.m_name, joinDlg.m_pw);

		if(result)
		{
			AfxMessageBox("JOIN SUCESSS");
		}
		else
		{
			AfxMessageBox("JOIN FAIL");
		}
	}
}

// Login Button
void CLoginDlg::OnBnClickedBtnLogin()
{
	CString id, pw;
	GetDlgItemText(IDC_EDIT_LOGIN_ID, id);
	GetDlgItemText(IDC_EDIT_LOGIN_PW, pw);
	if(id.IsEmpty() || pw.IsEmpty())
	{
		AfxMessageBox("ID�� PASSWORD�� �Է��� �ּ���.");
		return;
	}
	Member member = g_dataBase.SelectMember(id, pw);

	if(member.valid)
	{
		g_member = member;
		g_vMember = g_dataBase.SelectAllOhterMember(member.id);
		((CBINGODlg*)GetParent())->ChangeDlg(LOGIN_ROOM, WATING_ROOM);
		AfxMessageBox("LOGIN SUCCESS");
	}
	else
		AfxMessageBox("LOGIN FAIL");
}



