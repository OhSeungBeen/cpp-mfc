// WatingRoomDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CATCHMIND.h"
#include "WatingRoomDlg.h"
#include "Global.h"

// CWatingRoomDlg 대화 상자입니다.

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


// CWatingRoomDlg 메시지 처리기입니다.

void CWatingRoomDlg::OnProfile()
{
	CProfileDlg profileDlg;
	profileDlg.DoModal();

	
	

	/*CProfileDlg* profileDlg = (CProfileDlg*)GetDlgItem(IDD_PROFILE_DIALOG);
	profileDlg->DoModal();*/
}
