
// SERIAL_COMDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "SERIAL_COM.h"
#include "SERIAL_COMDlg.h"
#include "time.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CSERIAL_COMDlg ��ȭ ����




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


// CSERIAL_COMDlg �޽��� ó����

BOOL CSERIAL_COMDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
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

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CSERIAL_COMDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
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
	
	if (tempBaudRate == "1200") // ���� �ӵ� ����
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
	
	if (tempDataBit == "5") // ������ ��Ʈ ����
		dataBit = 5;
	else if (tempDataBit == "6")
		dataBit = 6;
	else if (tempDataBit == "7")
		dataBit = 7;
	else if (tempDataBit == "8")
		dataBit = 8;

	if (tempStopBit == "1")   // ��ž ��Ʈ ����
		stopBit = ONESTOPBIT;
	else if (tempStopBit == "1.5")
		stopBit = ONE5STOPBITS;
	else if (tempStopBit == "2")
		stopBit = TWOSTOPBITS;

	if(tempParity == "None") // �и�Ƽ ��Ʈ ����
		parity = NOPARITY;
	else if(tempParity == "Even")
		parity = EVENPARITY;
	else if(tempParity == "Odd")
		parity = ODDPARITY;

	
	//����Ʈ�� �����. 
	m_Serial.SetComPort(port, baudRate, dataBit, stopBit, parity); 
	//����Ʈ�� ������ �����. 
	m_Serial.CreateComInfo(); 
	//������Ʈ�� ���� 
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
	m_Serial.DestoryCom(); // �ø��� ��� ����
	CDialog::OnClose();
}


void CSERIAL_COMDlg::OnBnClickedBtnLogSave()
{
	if(ctrl_listLog.GetCount() == 0)
	{
		AfxMessageBox("������ ������ �����ϴ�.");
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
	AfxMessageBox(strFileName + "���� ����Ǿ����ϴ�.");
	logFile.Close();
}
