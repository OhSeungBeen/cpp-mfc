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
			
			((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->AddProfileToList(&profile);
			((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->SetMode(1);
			((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->SetQuiz(quiz);
			((CCATCHMINDDlg*)AfxGetMainWnd())->ChangeDlg(WATING_ROOM, GAME_ROOM);

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

// Notice Full Room 
void CWatingRoomDlg::NoticeFullRoom()
{
	AfxMessageBox("ROOM JOIN FAIL : ROOM FULL");
	g_logManager.Log("ROOM JOIN FAIL : ROOM FULL");
}

// Notice Password Incorrect
void CWatingRoomDlg::NoticeIncorrectPassword()
{
	AfxMessageBox("ROOM JOIN FAIL : PASSWORD INCORRECT OR CANCEL");
	g_logManager.Log("ROOM JOIN FAIL : PASSWORD INCORRECT OR CANCEL");
}

// Notice Room join Success
void CWatingRoomDlg::NoticeAccept()
{
	g_clientSocket.m_connected = TRUE;

	Profile profile;
	strcpy_s(profile.id, g_member.id);
	strcpy_s(profile.name, g_member.name);
	strcpy_s(profile.imageName, g_member.imageName);
	g_clientSocket.m_vProfile.push_back(profile);
	

	((CCATCHMINDDlg*)AfxGetMainWnd())->ChangeDlg(WATING_ROOM, GAME_ROOM);
	((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->SetMode(0);
	((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->AddProfileToList(&profile);

	AfxMessageBox("ROOM JOIN SUCCESS");
	g_logManager.Log("ROOM JOIN SUCCESS");
}


// Create Room Normal Mode (Serial)
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
			Profile profile;
			strcpy_s(profile.id, g_member.id);
			strcpy_s(profile.name, g_member.name);
			strcpy_s(profile.imageName, g_member.imageName);
			g_serial.m_vProfile.push_back(profile);
			
			CString quiz = g_dataBase.SelectRandomQuiz();

			//g_serial.WriteProfile(JOINED_NEW_USER_PROFILE);
			
			AfxMessageBox("CREATE NOMAL MODE ROOM(SERIAL) SUCCESS");
			g_logManager.Log("CREATE NOMAL MODE ROOM(SERIAL) SUCCESS");
			((CCATCHMINDDlg*)GetParent())->ChangeDlg(WATING_ROOM, GAME_ROOM);
			((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->AddProfileToList(&profile);
			((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->SetMode(1);
			((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->GetDlgItem(IDC_BTN_SERIAL_MODE_ORDER)->ShowWindow(TRUE);
		}
		else
		{
			AfxMessageBox("CREATE NOMAL MODE ROOM(SERIAL) FAIL");
			g_logManager.Log("CREATE NOMAL MODE ROOM(SERIAL) FAIL");
		}
	}
}
