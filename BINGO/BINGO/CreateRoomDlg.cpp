// CreateRoomDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BINGO.h"
#include "CreateRoomDlg.h"


// CCreateRoomDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCreateRoomDlg, CDialog)

CCreateRoomDlg::CCreateRoomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateRoomDlg::IDD, pParent)
{

}

CCreateRoomDlg::~CCreateRoomDlg()
{
}

void CCreateRoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_USER_SIZE, ctrl_comBingo);
	DDX_Control(pDX, IDD_CREATE_IPADDRESS, ctrl_ipAdress);
}


BEGIN_MESSAGE_MAP(CCreateRoomDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CCreateRoomDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CCreateRoomDlg 메시지 처리기입니다.

BOOL CCreateRoomDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	
	CString strTemp;
	for(int i = 1; i < 9; i++)
	{	
		strTemp.Format("%d", i);
		ctrl_comBingo.AddString(strTemp);
	}
	ctrl_comBingo.SetCurSel(0);

	ctrl_ipAdress.SetAddress(127,0,0,1);
	SetDlgItemInt(IDD_EDIT_CREATE_PORT, 8000);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CCreateRoomDlg::OnBnClickedOk()
{
	CString personnel, roomPrivate;
	ctrl_comBingo.GetLBText(ctrl_comBingo.GetCurSel(), personnel);
	m_ip = IpAdressCtrlToString();
	m_port = GetDlgItemInt(IDD_EDIT_CREATE_PORT);
	OnOK();
}

CString CCreateRoomDlg::IpAdressCtrlToString()
{
	BYTE ipA, ipB, ipC, ipD;

	ctrl_ipAdress.GetAddress(ipA, ipB, ipC, ipD);
	CString ip;
	ip.Format("%d.%d.%d.%d", ipA, ipB, ipC, ipD);

	return ip;
}
