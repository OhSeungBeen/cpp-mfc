
// CLIENTDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "CLIENT.h"
#include "CLIENTDlg.h"

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


// CCLIENTDlg 대화 상자




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


// CCLIENTDlg 메시지 처리기

BOOL CCLIENTDlg::OnInitDialog()
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
	ctrl_ipAdress.SetAddress(127,0,0,1);
	SetDlgItemInt(IDC_EDIT_PORT, 8000);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCLIENTDlg::OnPaint()
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
	sendMessage[0] = stx; // 맨앞 stx
	memcpy(sendMessage + 1, message.GetBuffer(), dataSize);
	sendMessage[dataSize - 1] = etx; // 맨뒤 etx
	clientSocket.Send(sendMessage, dataSize);
	ctrl_listLog.AddString("[send]" + message);
}



void CCLIENTDlg::OnBnClickedBtnLogSave()
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
