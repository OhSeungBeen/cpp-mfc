// CreateRoomDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CATCHMIND.h"
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
	DDX_Control(pDX, IDC_COMBO_USER_SIZE, ctrl_comUserSize);
	DDX_Control(pDX, IDC_COMBO_PRIVATE, ctrl_comPrivate);
	DDX_Control(pDX, IDD_CREATE_IPADDRESS, ctrl_ipAdress);
}


BEGIN_MESSAGE_MAP(CCreateRoomDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CCreateRoomDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_ROOM_PRIVATE, &CCreateRoomDlg::OnCbnSelchangeComboRoomPrivate)
END_MESSAGE_MAP()


// CCreateRoomDlg 메시지 처리기입니다.

BOOL CCreateRoomDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ctrl_comUserSize.AddString("3");
	ctrl_comUserSize.AddString("4");
	ctrl_comUserSize.SetCurSel(0);

	ctrl_comPrivate.AddString("공개");
	ctrl_comPrivate.AddString("비공개");
	ctrl_comPrivate.SetCurSel(0);

	ctrl_ipAdress.SetAddress(127,0,0,1);
	SetDlgItemInt(IDD_EDIT_CREATE_PORT, 8000);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CCreateRoomDlg::OnBnClickedOk()
{
	CString personnel, roomPrivate;
	ctrl_comUserSize.GetLBText(ctrl_comUserSize.GetCurSel(), personnel);
	ctrl_comPrivate.GetLBText(ctrl_comPrivate.GetCurSel(), roomPrivate);
	m_userSize = _ttoi(personnel);

	if(roomPrivate == "공개")
		m_privateRoom = FALSE;
	else if(roomPrivate == "비공개")
	{
		m_privateRoom = TRUE;
		CString password;
		GetDlgItemText(IDC_EDIT_PASSWORD, password);
		if(password.IsEmpty())
		{
			AfxMessageBox("PASSWORD를 입력하세요.");
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
	if(roomPrivate == "공개")
	{
		SetDlgItemText(IDC_EDIT_PASSWORD, "");
		GetDlgItem(IDC_EDIT_PASSWORD)->EnableWindow(FALSE);
	}
	else if(roomPrivate == "비공개")
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
