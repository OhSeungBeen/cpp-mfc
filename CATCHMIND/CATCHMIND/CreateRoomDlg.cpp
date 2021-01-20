// CreateRoomDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CATCHMIND.h"
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
	DDX_Control(pDX, IDC_COMBO_USER_SIZE, ctrl_comUserSize);
	DDX_Control(pDX, IDC_COMBO_PRIVATE, ctrl_comPrivate);
	DDX_Control(pDX, IDD_CREATE_IPADDRESS, ctrl_ipAdress);
}


BEGIN_MESSAGE_MAP(CCreateRoomDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CCreateRoomDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_ROOM_PRIVATE, &CCreateRoomDlg::OnCbnSelchangeComboRoomPrivate)
END_MESSAGE_MAP()


// CCreateRoomDlg �޽��� ó�����Դϴ�.

BOOL CCreateRoomDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ctrl_comUserSize.AddString("3");
	ctrl_comUserSize.AddString("4");
	ctrl_comUserSize.SetCurSel(0);

	ctrl_comPrivate.AddString("����");
	ctrl_comPrivate.AddString("�����");
	ctrl_comPrivate.SetCurSel(0);

	ctrl_ipAdress.SetAddress(127,0,0,1);
	SetDlgItemInt(IDD_EDIT_CREATE_PORT, 8000);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CCreateRoomDlg::OnBnClickedOk()
{
	CString personnel, roomPrivate;
	ctrl_comUserSize.GetLBText(ctrl_comUserSize.GetCurSel(), personnel);
	ctrl_comPrivate.GetLBText(ctrl_comPrivate.GetCurSel(), roomPrivate);
	m_userSize = _ttoi(personnel);

	if(roomPrivate == "����")
		m_privateRoom = FALSE;
	else if(roomPrivate == "�����")
	{
		m_privateRoom = TRUE;
		CString password;
		GetDlgItemText(IDC_EDIT_PASSWORD, password);
		if(password.IsEmpty())
		{
			AfxMessageBox("PASSWORD�� �Է��ϼ���.");
			return;
		}
		m_password = password;
	}

	m_ip = IpAdressCtrlToString();
	m_port = GetDlgItemInt(IDD_EDIT_CREATE_PORT);
	OnOK();
}

void CCreateRoomDlg::OnCbnSelchangeComboRoomPrivate()
{
	CString roomPrivate;
	ctrl_comPrivate.GetLBText(ctrl_comPrivate.GetCurSel(), roomPrivate);
	if(roomPrivate == "����")
	{
		SetDlgItemText(IDC_EDIT_PASSWORD, "");
		GetDlgItem(IDC_EDIT_PASSWORD)->EnableWindow(FALSE);
	}
	else if(roomPrivate == "�����")
	{
		GetDlgItem(IDC_EDIT_PASSWORD)->EnableWindow(TRUE);
	}
}

CString CCreateRoomDlg::IpAdressCtrlToString()
{
	BYTE ipA, ipB, ipC, ipD;

	ctrl_ipAdress.GetAddress(ipA, ipB, ipC, ipD);
	CString ip;
	ip.Format("%d.%d.%d.%d", ipA, ipB, ipC, ipD);

	return ip;
}
