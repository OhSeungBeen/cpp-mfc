// JoinRoomDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "BINGO.h"
#include "JoinRoomDlg.h"


// CJoinRoomDlg ��ȭ �����Դϴ�.

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


// CJoinRoomDlg �޽��� ó�����Դϴ�.


BOOL CJoinRoomDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ctrl_ipAdress.SetAddress(127,0,0,1);
	SetDlgItemInt(IDD_EDIT_JOIN_PORT, 8000);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CJoinRoomDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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