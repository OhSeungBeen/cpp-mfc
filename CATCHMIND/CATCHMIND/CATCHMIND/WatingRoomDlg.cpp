// WatingRoomDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CATCHMIND.h"
#include "WatingRoomDlg.h"
#include "Global.h"

// CWatingRoomDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CWatingRoomDlg, CDialog)

CWatingRoomDlg::CWatingRoomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWatingRoomDlg::IDD, pParent)
{

}

CWatingRoomDlg::~CWatingRoomDlg()
{
}

void CWatingRoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWatingRoomDlg, CDialog)
	ON_COMMAND(ID_PROFILE, &CWatingRoomDlg::OnProfile)
END_MESSAGE_MAP()


// CWatingRoomDlg �޽��� ó�����Դϴ�.

void CWatingRoomDlg::OnProfile()
{
	CProfileDlg profileDlg;
	profileDlg.DoModal();

	
	

	/*CProfileDlg* profileDlg = (CProfileDlg*)GetDlgItem(IDD_PROFILE_DIALOG);
	profileDlg->DoModal();*/
}
