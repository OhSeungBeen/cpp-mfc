// CreateRoomDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "BINGO.h"
#include "CreateRoomDlg.h"


// CCreateRoomDlg ��ȭ �����Դϴ�.

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


// CCreateRoomDlg �޽��� ó�����Դϴ�.

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
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
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
