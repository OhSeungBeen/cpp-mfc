
// CATCHMINDDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "BINGO.h"
#include "BINGODlg.h"
#include "FriendDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	//enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog()
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCATCHMINDDlg ��ȭ ����

CBINGODlg::CBINGODlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBINGODlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBINGODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBINGODlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_PROFILE, &CBINGODlg::OnProfile)
	ON_COMMAND(ID_FRIEND_VIEW, &CBINGODlg::OnFriendView)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CCATCHMINDDlg �޽��� ó����

BOOL CBINGODlg::OnInitDialog()
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
	
	AfxOleInit();
	g_dataBase.Connect();

	m_loginDlg = new CLoginDlg;
	m_loginDlg->Create(CLoginDlg::IDD, this);
	m_loginDlg->CenterWindow();
	m_loginDlg->ShowWindow( SW_SHOW );

	m_watingRoomDlg = new CWatingRoomDlg(this);
	m_watingRoomDlg->Create(CWatingRoomDlg::IDD, this);
	m_watingRoomDlg->CenterWindow();
	m_watingRoomDlg->ShowWindow(SW_HIDE);

	m_gameRoomDlg = new CGameRoomDlg;
	m_gameRoomDlg->Create(CGameRoomDlg::IDD, this);
	m_gameRoomDlg->CenterWindow();
	m_gameRoomDlg->ShowWindow(SW_HIDE);
	
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CBINGODlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBINGODlg::OnPaint()
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
HCURSOR CBINGODlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// �ڽ� ���̾�α� ��ȯ
void CBINGODlg::ChangeDlg(int preDlg, int newDlg)
{
	if(preDlg == LOGIN_ROOM)
		m_loginDlg->ShowWindow(SW_HIDE);
	else if(preDlg == WATING_ROOM)
		m_watingRoomDlg->ShowWindow(SW_HIDE);
	else if(preDlg == GAME_ROOM)
		m_gameRoomDlg->ShowWindow(SW_HIDE);
	
	if(newDlg == LOGIN_ROOM)
		m_loginDlg->ShowWindow(SW_SHOW);
	else if(newDlg == WATING_ROOM)
		m_watingRoomDlg->ShowWindow(SW_SHOW);
	else if(newDlg == GAME_ROOM)
		m_gameRoomDlg->ShowWindow(SW_SHOW);
}


void CBINGODlg::OnProfile()
{
	if(g_member.valid == FALSE)
		return;

	CProfileDlg profileDlg(g_member.nickName, g_member.id);
	profileDlg.DoModal();
}

void CBINGODlg::OnFriendView()
{
	if(g_member.valid == FALSE)
		return;

	CFriendDlg friendDlg;
	friendDlg.DoModal();
}

void CBINGODlg::OnClose()
{
	// delete memory
	delete m_loginDlg;
	delete m_watingRoomDlg;
	delete m_gameRoomDlg;
	CDialog::OnClose();
}

