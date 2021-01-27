#include "stdafx.h"
#include "BINGO.h"
#include "BINGODlg.h"
#include "WatingRoomDlg.h"
#include "JoinRoomDlg.h"
#include "Global.h"

IMPLEMENT_DYNAMIC(CWatingRoomDlg, CDialog)

CWatingRoomDlg::CWatingRoomDlg(CWnd* pParent)
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
END_MESSAGE_MAP()


BOOL CWatingRoomDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CFont fnt;
	LOGFONT lf;
	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 30;
	lf.lfWeight = FW_BOLD;
	::lstrcpy(lf.lfFaceName, "Tahoma");
	fnt.CreateFontIndirect(&lf);
	GetDlgItem(IDC_BTN_CREATE_ROOM)->SetFont(&fnt);
	GetDlgItem(IDC_BTN_JOIN_ROOM)->SetFont(&fnt);
	fnt.Detach();
	
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
			g_listenSocket.m_connected = TRUE;

			Profile profile;
			strcpy_s(profile.id, g_member.id);
			strcpy_s(profile.nickName, g_member.nickName);
			g_listenSocket.m_vProfile.push_back(profile);

			g_listenSocket.m_quiz = g_dataBase.SelectRandomQuiz();

			((CBINGODlg*)AfxGetMainWnd())->ChangeDlg(WATING_ROOM, GAME_ROOM);
			((CBINGODlg*)AfxGetMainWnd())->m_gameRoomDlg->SetQuiz(g_listenSocket.m_quiz);
			((CBINGODlg*)AfxGetMainWnd())->m_gameRoomDlg->SetDlgItemText(IDC_BTN_GAME_START_READY, "게임 시작");
			((CBINGODlg*)AfxGetMainWnd())->m_gameRoomDlg->RefreshProfile(g_listenSocket.m_vProfile);
			AfxMessageBox("ROOM CREATE SUCCESS");
		}
		else
		{
			AfxMessageBox("ROOM CREATE FAIL");
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
		if(g_clientSocket.Connect(joinRoomDlg.m_ip, joinRoomDlg.m_port))
		{
			g_clientSocket.m_connected = TRUE;

			Profile profile;
			strcpy_s(profile.id, g_member.id);
			strcpy_s(profile.nickName, g_member.nickName);
			g_clientSocket.m_vProfile.push_back(profile);

			((CBINGODlg*)AfxGetMainWnd())->ChangeDlg(WATING_ROOM, GAME_ROOM);
			((CBINGODlg*)AfxGetMainWnd())->m_gameRoomDlg->SetDlgItemText(IDC_BTN_GAME_START_READY, "게임 준비");
			//AfxMessageBox("ROOM JOIN SUCCESS");
		}
		else
		{
			AfxMessageBox("ROOM JOIN FAIL : ROOM DOSE NOT EXIST");

		}
	}
}

// Notice Full Room 
void CWatingRoomDlg::NoticeFullRoom()
{
	AfxMessageBox("ROOM JOIN FAIL : ROOM FULL");
	((CBINGODlg*)AfxGetMainWnd())->ChangeDlg(GAME_ROOM, WATING_ROOM);
}



