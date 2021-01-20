#include "stdafx.h"
#include "CATCHMIND.h"
#include "CATCHMINDDlg.h"
#include "WatingRoomDlg.h"
#include "CreateRoomSerialDlg.h"
#include "JoinRoomDlg.h"
#include "Global.h"

IMPLEMENT_DYNAMIC(CWatingRoomDlg, CDialog)

CWatingRoomDlg::CWatingRoomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWatingRoomDlg::IDD, pParent)
{
	
}

CWatingRoomDlg::~CWatingRoomDlg()
{
}

void CWatingRoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWatingRoomDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_CREATE_ROOM, &CWatingRoomDlg::OnBnClickedBtnCreateRoom)
	ON_BN_CLICKED(IDC_BTN_JOIN_ROOM, &CWatingRoomDlg::OnBnClickedBtnJoinRoom)
	ON_BN_CLICKED(IDC_BTN_CREATE_ROOM_SERIAL, &CWatingRoomDlg::OnBnClickedBtnCreateRoomSerial)
	ON_MESSAGE(WM_DISCONNECT, CWatingRoomDlg::OnDisConnect)
	ON_MESSAGE(WM_ACCEPT, CWatingRoomDlg::OnAccept)
END_MESSAGE_MAP()


BOOL CWatingRoomDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	return TRUE;
}

// Create Room Button
void CWatingRoomDlg::OnBnClickedBtnCreateRoom()
{
	CCreateRoomDlg createRoomDlg;
	if(createRoomDlg.DoModal() == IDOK)
	{	
		g_listenSocket.Create(createRoomDlg.m_port, SOCK_STREAM, createRoomDlg.m_ip);
		if(g_listenSocket.Listen())
		{
			CString quiz = g_dataBase.SelectRandomQuiz();

			g_listenSocket.m_connected = TRUE;
			g_listenSocket.m_userSize = createRoomDlg.m_userSize;
			g_listenSocket.m_privateRoom = createRoomDlg.m_privateRoom;
			g_listenSocket.m_password = createRoomDlg.m_password;
			g_listenSocket.m_quiz = quiz;

			Profile profile;
			strcpy_s(profile.id, g_member.id);
			strcpy_s(profile.name, g_member.name);
			strcpy_s(profile.imageName, g_member.imageName);
			g_listenSocket.m_vProfile.push_back(profile);
			
			::SendMessage(((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->m_hWnd, WM_ONE_USER_PROFILE, 0, (LPARAM)&profile);
			((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->SetMode(1);
			((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->SetQuiz(quiz);
			((CCATCHMINDDlg*)GetParent())->ChangeDlg(WATING_ROOM, GAME_ROOM);

			AfxMessageBox("ROOM CREATE SUCCESS");
			g_logManager.Log("ROOM CREATE SUCCESS");
		}
		else
		{
			AfxMessageBox("ROOM CREATE FAIL");
			g_logManager.Log("ROOM CREATE FAIL");
		}
	}
}

// Join Room Button
void CWatingRoomDlg::OnBnClickedBtnJoinRoom()
{
	CJoinRoomDlg joinRoomDlg;

	if(joinRoomDlg.DoModal() == IDOK)
	{
		g_clientSocket.Create();
		if(!g_clientSocket.Connect(joinRoomDlg.m_ip, joinRoomDlg.m_port))
		{
			AfxMessageBox("ROOM JOIN FAIL : ROOM DOSE NOT EXIST");
			g_logManager.Log("ROOM JOIN FAIL : ROOM DOSE NOT EXIST");
		}
	}
}

// Message Room Join Fail
LRESULT CWatingRoomDlg::OnDisConnect( WPARAM wParam, LPARAM lParam )
{
	AfxMessageBox("ROOM JOIN FAIL : ROOM FULL OR INCORRECT PASSWORD");
	g_logManager.Log("ROOM JOIN FAIL : ROOM FULL OR INCORRECT PASSWORD");
	return 0;
}

// Message Room join Success
LRESULT CWatingRoomDlg::OnAccept( WPARAM wParam, LPARAM lParam )
{
	g_clientSocket.m_connected = TRUE;
	((CCATCHMINDDlg*)GetParent())->ChangeDlg(WATING_ROOM, GAME_ROOM);
	((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->SetMode(0);
	
	AfxMessageBox("ROOM JOIN SUCCESS");
	g_logManager.Log("ROOM JOIN SUCCESS");
	return 0;
}


// Create Room Nomal Mode (Serial)
void CWatingRoomDlg::OnBnClickedBtnCreateRoomSerial()
{
	CCreateRoomSerialDlg CreateRoomSerial;
	if(CreateRoomSerial.DoModal() == IDOK)
	{
		g_serial.SetComPort(CreateRoomSerial.m_port,
			CreateRoomSerial.m_baudRate, CreateRoomSerial.m_dataBit,
			CreateRoomSerial.m_stopBit, CreateRoomSerial.m_parity); 

		g_serial.CreateComInfo(); 
		if(g_serial.OpenComPort())
		{
			AfxMessageBox("CREATE NOMAL MODE ROOM(SERIAL) SUCCESS");
			g_logManager.Log("CREATE NOMAL MODE ROOM(SERIAL) SUCCESS");
			((CCATCHMINDDlg*)GetParent())->ChangeDlg(WATING_ROOM, GAME_ROOM);
			//g_serial.SetHwnd(((CCATCHMINDDlg*)GetParent())->m_gameRoomDlg->m_hWnd);
		}
		else
		{
			AfxMessageBox("CREATE NOMAL MODE ROOM(SERIAL) FAIL");
			g_logManager.Log("CREATE NOMAL MODE ROOM(SERIAL) FAIL");
		}
	}
}
