// CreateRoomSerial.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CATCHMIND.h"
#include "CreateRoomSerialDlg.h"
#include "CreateRoomSerialDlg.h"


// CCreateRoomSerial 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCreateRoomSerialDlg, CDialog)

CCreateRoomSerialDlg::CCreateRoomSerialDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateRoomSerialDlg::IDD, pParent)
{

}

CCreateRoomSerialDlg::~CCreateRoomSerialDlg()
{
}

void CCreateRoomSerialDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PORT, ctrl_comboPort);
	DDX_Control(pDX, IDC_COMBO_BAUNDRATE, ctrl_comboBaundRate);
	DDX_Control(pDX, IDC_COMBO_DATABITS, ctrl_comboDatabits);
	DDX_Control(pDX, IDC_COMBO_STOPBITS, ctrl_comboStopbits);
	DDX_Control(pDX, IDC_COMBO_PARITY, ctrl_comboParity);
}


BEGIN_MESSAGE_MAP(CCreateRoomSerialDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CCreateRoomSerialDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CCreateRoomSerial 메시지 처리기입니다.

BOOL CCreateRoomSerialDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ctrl_comboPort.AddString("COM1");
	ctrl_comboPort.AddString("COM2");
	ctrl_comboPort.AddString("COM3");
	ctrl_comboPort.AddString("COM4");
	ctrl_comboPort.AddString("COM5");

	ctrl_comboBaundRate.AddString("1200");
	ctrl_comboBaundRate.AddString("2400");
	ctrl_comboBaundRate.AddString("4800");
	ctrl_comboBaundRate.AddString("9600");
	ctrl_comboBaundRate.AddString("14400");
	ctrl_comboBaundRate.AddString("19200");
	ctrl_comboBaundRate.AddString("38400");
	ctrl_comboBaundRate.AddString("57600");
	ctrl_comboBaundRate.AddString("115200");
	ctrl_comboBaundRate.AddString("128000");
	ctrl_comboBaundRate.AddString("256000");

	ctrl_comboDatabits.AddString("5");
	ctrl_comboDatabits.AddString("6");
	ctrl_comboDatabits.AddString("7");
	ctrl_comboDatabits.AddString("8");

	ctrl_comboStopbits.AddString("1");
	ctrl_comboStopbits.AddString("1.5");
	ctrl_comboStopbits.AddString("2");

	ctrl_comboParity.AddString("None");
	ctrl_comboParity.AddString("Odd");
	ctrl_comboParity.AddString("Even");

	ctrl_comboPort.SetCurSel(0);
	ctrl_comboBaundRate.SetCurSel(3);
	ctrl_comboDatabits.SetCurSel(3);
	ctrl_comboStopbits.SetCurSel(0);
	ctrl_comboParity.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CCreateRoomSerialDlg::OnBnClickedOk()
{
	CString tempBaudRate, tempDataBit, tempStopBit, tempParity;

	GetDlgItemText(IDC_COMBO_PORT, m_port);
	GetDlgItemText(IDC_COMBO_BAUNDRATE, tempBaudRate);
	GetDlgItemText(IDC_COMBO_DATABITS, tempDataBit);
	GetDlgItemText(IDC_COMBO_STOPBITS, tempStopBit);
	GetDlgItemText(IDC_COMBO_PARITY, tempParity);

	if (tempBaudRate == "1200") // 전송 속도 설정
		m_baudRate = CBR_1200;
	else if (tempBaudRate == "2400")
		m_baudRate = CBR_2400;
	else if (tempBaudRate == "4800")
		m_baudRate = CBR_4800;
	else if (tempBaudRate == "9600")
		m_baudRate = CBR_9600;
	else if (tempBaudRate == "14400")
		m_baudRate = CBR_14400;
	else if (tempBaudRate == "19200")
		m_baudRate = CBR_19200;
	else if (tempBaudRate == "38400")
		m_baudRate = CBR_38400;
	else if (tempBaudRate == "57600")
		m_baudRate = CBR_57600;
	else if (tempBaudRate == "115200")
		m_baudRate = CBR_115200;
	else if (tempBaudRate == "128000")
		m_baudRate = CBR_128000;
	else if (tempBaudRate == "256000")
		m_baudRate = CBR_256000;

	if (tempDataBit == "5") // 데이터 비트 설정
		m_dataBit = 5;
	else if (tempDataBit == "6")
		m_dataBit = 6;
	else if (tempDataBit == "7")
		m_dataBit = 7;
	else if (tempDataBit == "8")
		m_dataBit = 8;

	if (tempStopBit == "1")   // 스탑 비트 설정
		m_stopBit = ONESTOPBIT;
	else if (tempStopBit == "1.5")
		m_stopBit = ONE5STOPBITS;
	else if (tempStopBit == "2")
		m_stopBit = TWOSTOPBITS;

	if(tempParity == "None") // 패리티 비트 설정
		m_parity = NOPARITY;
	else if(tempParity == "Even")
		m_parity = EVENPARITY;
	else if(tempParity == "Odd")
		m_parity = ODDPARITY;

	OnOK();
}

