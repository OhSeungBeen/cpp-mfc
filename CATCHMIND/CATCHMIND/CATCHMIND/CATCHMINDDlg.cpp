
// CATCHMINDDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "CATCHMIND.h"
#include "CATCHMINDDlg.h"


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


// CCATCHMINDDlg ��ȭ ����




CCATCHMINDDlg::CCATCHMINDDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCATCHMINDDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCATCHMINDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCATCHMINDDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_LOGIN, &CCATCHMINDDlg::OnBnClickedBtnLogin)
	ON_BN_CLICKED(IDC_BTN_JOIN, &CCATCHMINDDlg::OnBnClickedBtnJoin)
END_MESSAGE_MAP()


// CCATCHMINDDlg �޽��� ó����

BOOL CCATCHMINDDlg::OnInitDialog()
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
	g_clientSocket.Create();
	if(g_clientSocket.Connect("127.0.0.1", 8000))
		AfxMessageBox("���� ���� ����");
	else
		AfxMessageBox("���� ���� ����");

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CCATCHMINDDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCATCHMINDDlg::OnPaint()
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
HCURSOR CCATCHMINDDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// �α��� ��ư
void CCATCHMINDDlg::OnBnClickedBtnLogin()
{
	CString id, pw;
	GetDlgItemText(IDC_EDIT_LOGIN_ID, id);
	GetDlgItemText(IDC_EDIT_LOGIN_PW, pw);
	if(id.IsEmpty() || pw.IsEmpty())
	{
		AfxMessageBox("ID�� PASSWORD�� �Է��� �ּ���.");
		return;
	}
	g_clientSocket.SendLoginInfo(id, pw);

}

// ȸ�� ���� ��ư
void CCATCHMINDDlg::OnBnClickedBtnJoin()
{
	CJoinDlg joinDlg;
	
	if(joinDlg.DoModal() == IDOK)
	{
		CString name = joinDlg.m_name; // �⺻ ���� ����
		CString id = joinDlg.m_id;
		CString pw = joinDlg.m_pw;
		g_clientSocket.SendJoinInfo(name, id, pw, "");

		Header header; // �̹��� ����
		header.id = FILE;
		header.size = (int)joinDlg.m_file.GetLength();
		g_clientSocket.Send((char*)&header, sizeof(header));
		byte* imageData = new byte[4096];
		DWORD dwRead;
		do{
			dwRead = joinDlg.m_file.Read(imageData, 4096);
			g_clientSocket.Send(imageData, dwRead);
		}while(dwRead > 0);

		delete imageData;
		joinDlg.m_file.Close();
	}
	
}
