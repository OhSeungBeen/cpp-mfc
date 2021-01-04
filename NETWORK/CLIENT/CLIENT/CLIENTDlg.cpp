
// CLIENTDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "CLIENT.h"
#include "CLIENTDlg.h"

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


// CCLIENTDlg ��ȭ ����




CCLIENTDlg::CCLIENTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCLIENTDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCLIENTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LOG, ctrl_listLog);
	DDX_Control(pDX, IDC_IPADDRESS, ctrl_ipAdress);
}

BEGIN_MESSAGE_MAP(CCLIENTDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_SEND, &CCLIENTDlg::OnBnClickedBtnSend)
	ON_BN_CLICKED(IDC_BTN_CONNECT, &CCLIENTDlg::OnBnClickedBtnConnect)
	ON_BN_CLICKED(IDC_BTN_LOG_SAVE, &CCLIENTDlg::OnBnClickedBtnLogSave)
END_MESSAGE_MAP()


// CCLIENTDlg �޽��� ó����

BOOL CCLIENTDlg::OnInitDialog()
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
	ctrl_ipAdress.SetAddress(127,0,0,1);
	SetDlgItemInt(IDC_EDIT_PORT, 8000);
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CCLIENTDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCLIENTDlg::OnPaint()
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
HCURSOR CCLIENTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCLIENTDlg::AddLogString(CString str)
{
	ctrl_listLog.AddString(str);
}

void CCLIENTDlg::OnBnClickedBtnConnect()
{
	BYTE ipA, ipB, ipC, ipD;

	ctrl_ipAdress.GetAddress(ipA, ipB, ipC, ipD);
	CString ip;
	ip.Format("%d.%d.%d.%d", ipA, ipB, ipC, ipD);

	int port = GetDlgItemInt(IDC_EDIT_PORT);

	clientSocket.Create();
	if (clientSocket.Connect(ip, port)) // ip, port
		AddLogString("Connected !!");
	else
		AddLogString("Disconnected !!");
}

void CCLIENTDlg::OnBnClickedBtnSend()
{
	CString message, stxHex, etxHex;
	GetDlgItemText(IDC_EDIT_SEND, message);
	GetDlgItemText(IDC_EDIT_STX, stxHex);
	GetDlgItemText(IDC_EDIT_ETX, etxHex);
	char stx = (char)_tcstoul(stxHex, NULL, 16);
	char etx = (char)_tcstoul(etxHex, NULL, 16);

	int dataSize = message.GetLength() + 2;
	char* sendMessage = new char[dataSize];
	sendMessage[0] = stx; // �Ǿ� stx
	memcpy(sendMessage + 1, message.GetBuffer(), dataSize);
	sendMessage[dataSize - 1] = etx; // �ǵ� etx
	clientSocket.Send(sendMessage, dataSize);
	ctrl_listLog.AddString("[send]" + message);
}



void CCLIENTDlg::OnBnClickedBtnLogSave()
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
