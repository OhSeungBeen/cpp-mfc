
// SERIAL_COMDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "SERIAL_COM.h"
#include "SERIAL_COMDlg.h"
#include "time.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CSERIAL_COMDlg 대화 상자




CSERIAL_COMDlg::CSERIAL_COMDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSERIAL_COMDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSERIAL_COMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PORT, ctrl_comboPort);
	DDX_Control(pDX, IDC_COMBO_BAUNDRATE, ctrl_comboBaundRate);
	DDX_Control(pDX, IDC_COMBO_PARITY, ctrl_comboParity);
	DDX_Control(pDX, IDC_COMBO_DATABITS, ctrl_comboDatabits);
	DDX_Control(pDX, IDC_COMBO_STOPBITS, ctrl_comboStopbits);
	DDX_Control(pDX, IDC_LIST_LOG, ctrl_listLog);
}

BEGIN_MESSAGE_MAP(CSERIAL_COMDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_OPEN, &CSERIAL_COMDlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_SEND, &CSERIAL_COMDlg::OnBnClickedBtnSend)
	ON_WM_CLOSE()
	ON_MESSAGE(WM_RECEIVEDATA, OnReceiveData)
	ON_BN_CLICKED(IDC_BTN_LOG_SAVE, &CSERIAL_COMDlg::OnBnClickedBtnLogSave)
END_MESSAGE_MAP()


// CSERIAL_COMDlg 메시지 처리기

BOOL CSERIAL_COMDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
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
	
	((CButton*)GetDlgItem(IDC_SEND_FORMAT1))->SetCheck(true);
	((CButton*)GetDlgItem(IDC_RECV_FORMAT1))->SetCheck(true);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CSERIAL_COMDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CSERIAL_COMDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSERIAL_COMDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSERIAL_COMDlg::OnBnClickedBtnOpen()
{
	CString port, tempBaudRate, tempDataBit, tempStopBit, tempParity;
	DWORD baudRate;
	byte parity, dataBit, stopBit;

	GetDlgItemText(IDC_COMBO_PORT, port);
	GetDlgItemText(IDC_COMBO_BAUNDRATE, tempBaudRate);
	GetDlgItemText(IDC_COMBO_DATABITS, tempDataBit);
	GetDlgItemText(IDC_COMBO_STOPBITS, tempStopBit);
	GetDlgItemText(IDC_COMBO_PARITY, tempParity);
	
	if (tempBaudRate == "1200") // 전송 속도 설정
		baudRate = CBR_1200;
	else if (tempBaudRate == "2400")
		baudRate = CBR_2400;
	else if (tempBaudRate == "4800")
		baudRate = CBR_4800;
	else if (tempBaudRate == "9600")
		baudRate = CBR_9600;
	else if (tempBaudRate == "14400")
		baudRate = CBR_14400;
	else if (tempBaudRate == "19200")
		baudRate = CBR_19200;
	else if (tempBaudRate == "38400")
		baudRate = CBR_38400;
	else if (tempBaudRate == "57600")
		baudRate = CBR_57600;
	else if (tempBaudRate == "115200")
		baudRate = CBR_115200;
	else if (tempBaudRate == "128000")
		baudRate = CBR_128000;
	else if (tempBaudRate == "256000")
		baudRate = CBR_256000;
	
	if (tempDataBit == "5") // 데이터 비트 설정
		dataBit = 5;
	else if (tempDataBit == "6")
		dataBit = 6;
	else if (tempDataBit == "7")
		dataBit = 7;
	else if (tempDataBit == "8")
		dataBit = 8;

	if (tempStopBit == "1")   // 스탑 비트 설정
		stopBit = ONESTOPBIT;
	else if (tempStopBit == "1.5")
		stopBit = ONE5STOPBITS;
	else if (tempStopBit == "2")
		stopBit = TWOSTOPBITS;

	if(tempParity == "None") // 패리티 비트 설정
		parity = NOPARITY;
	else if(tempParity == "Even")
		parity = EVENPARITY;
	else if(tempParity == "Odd")
		parity = ODDPARITY;

	
	//컴포트를 맞춘다. 
	m_Serial.SetComPort(port, baudRate, dataBit, stopBit, parity); 
	//컴포트의 정보를 만든다. 
	m_Serial.CreateComInfo(); 
	//컴토포트를 연다 
	m_Serial.OpenComPort();
	
	m_Serial.SetHwnd(this->m_hWnd);
	
}

void CSERIAL_COMDlg::OnBnClickedBtnSend()
{
	CString message;
	CString ascii;
	GetDlgItemText(IDC_EDIT_SEND, message);

	if(((CButton*)GetDlgItem(IDC_SEND_FORMAT2))->GetCheck())
	{	
		for(size_t i = 0; i < message.GetLength(); i +=2)
		{
			CString part = message.Mid(i, 2);
			char ch = _tcstoul(part, NULL, 16);
			ascii += ch;
		}
		m_Serial.WriteCom(ascii.GetBuffer(), ascii.GetLength());
		ctrl_listLog.AddString("[Send]" + message);
		return;
	}
	
	m_Serial.WriteCom(message.GetBuffer(), message.GetLength());
	ctrl_listLog.AddString("[Send]" + message);
}

LRESULT CSERIAL_COMDlg::OnReceiveData(UINT WParam,LONG LParam) 
{ 
	ctrl_listLog.AddString("[Recv]" + m_Serial.m_data);
	return TRUE;
} 

void CSERIAL_COMDlg::OnClose()
{
	m_Serial.DestoryCom(); // 시리얼 통신 해제
	CDialog::OnClose();
}


void CSERIAL_COMDlg::OnBnClickedBtnLogSave()
{
	if(ctrl_listLog.GetCount() == 0)
	{
		AfxMessageBox("저장할 내용이 없습니다.");
		return;
	}
	
	time_t t = time(NULL);
	struct tm tm;
	localtime_s(&tm, &t);

	CString strFileName;
	strFileName.Format("Log_%d-%02d-%02d-%02d-%02d-%02d.txt", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	CString name = strFileName;

	CStdioFile logFile;

	logFile.Open(name, CFile::modeCreate | CFile::modeWrite | CFile::typeText);
	CString log;
	for (int i = 0; i < ctrl_listLog.GetCount(); i++) {
		ctrl_listLog.GetText(i, log);
		logFile.WriteString(log + "\n");
	}
	AfxMessageBox(strFileName + "으로 저장되었습니다.");
	logFile.Close();
}
