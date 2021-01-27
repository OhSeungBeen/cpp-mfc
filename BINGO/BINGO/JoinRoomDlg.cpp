// JoinRoomDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BINGO.h"
#include "JoinRoomDlg.h"


// CJoinRoomDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CJoinRoomDlg, CDialog)

CJoinRoomDlg::CJoinRoomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CJoinRoomDlg::IDD, pParent)
{

}

CJoinRoomDlg::~CJoinRoomDlg()
{
}

void CJoinRoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDD_IPADDRESS, ctrl_ipAdress);
}


BEGIN_MESSAGE_MAP(CJoinRoomDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CJoinRoomDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CJoinRoomDlg 메시지 처리기입니다.


BOOL CJoinRoomDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ctrl_ipAdress.SetAddress(127,0,0,1);
	SetDlgItemInt(IDD_EDIT_JOIN_PORT, 8000);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CJoinRoomDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_ip = IpAdressCtrlToString();
	m_port = GetDlgItemInt(IDD_EDIT_JOIN_PORT);
	OnOK();
}


CString CJoinRoomDlg::IpAdressCtrlToString()
{
	BYTE ipA, ipB, ipC, ipD;

	ctrl_ipAdress.GetAddress(ipA, ipB, ipC, ipD);
	CString ip;
	ip.Format("%d.%d.%d.%d", ipA, ipB, ipC, ipD);
	return ip;
}