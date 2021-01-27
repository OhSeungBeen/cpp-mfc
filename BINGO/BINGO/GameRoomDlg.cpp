#include "stdafx.h"
#include "BINGO.h"
#include "GameRoomDlg.h"
#include "Global.h"
#include "ProfileDlg.h"
#include <vector>

IMPLEMENT_DYNAMIC(CGameRoomDlg, CDialog)

CGameRoomDlg::CGameRoomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGameRoomDlg::IDD, pParent)
{
	
}

CGameRoomDlg::~CGameRoomDlg()
{
	
}

void CGameRoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MESSAGE, ctrl_listChatMsg);
	DDX_Control(pDX, IDC_COMBO_COLOR, ctrl_comColor);
	DDX_Control(pDX, IDC_EDIT_QUIZ, ctrl_editQuiz);
}

BEGIN_MESSAGE_MAP(CGameRoomDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_SEND_MESSAGE, &CGameRoomDlg::OnBnClickedBtnSendMessage)
	ON_CBN_SELCHANGE(IDC_COMBO_COLOR, &CGameRoomDlg::OnCbnSelchangeComboColor)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_GAME_START_READY, &CGameRoomDlg::OnBnClickedBtnGameSatrtReady)
END_MESSAGE_MAP()

BOOL CGameRoomDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	CBingoPanelDlg* bingoPanelDlg = new CBingoPanelDlg;
	bingoPanelDlg->Create(CBingoPanelDlg::IDD, this);
	bingoPanelDlg->MoveWindow(25, 0, 350, 200);
	bingoPanelDlg->SetAllWordsEnbled(TRUE);
	bingoPanelDlg->ShowWindow(SW_SHOW);
	m_bingoPanelDlg[0] = bingoPanelDlg;

	CBingoPanelDlg* bingoPanelDlg2 = new CBingoPanelDlg;
	bingoPanelDlg2->Create(CBingoPanelDlg::IDD, this);
	bingoPanelDlg2->MoveWindow(380, 0, 350, 200);
	bingoPanelDlg2->ShowWindow(SW_SHOW);
	m_bingoPanelDlg[1] = bingoPanelDlg2;

	CBingoPanelDlg* bingoPanelDlg3 = new CBingoPanelDlg;
	bingoPanelDlg3->Create(CBingoPanelDlg::IDD, this);
	bingoPanelDlg3->MoveWindow(25, 200, 350, 200);
	bingoPanelDlg3->ShowWindow(SW_SHOW);
	m_bingoPanelDlg[2] = bingoPanelDlg3;

	CBingoPanelDlg* bingoPanelDlg4 = new CBingoPanelDlg;
	bingoPanelDlg4->Create(CBingoPanelDlg::IDD, this);
	bingoPanelDlg4->MoveWindow(380, 200, 350, 200);
	bingoPanelDlg4->ShowWindow(SW_SHOW);
	m_bingoPanelDlg[3] = bingoPanelDlg4;

	m_rgb = RGB(255, 0, 0);
	ctrl_comColor.AddString("빨강");
	ctrl_comColor.AddString("파랑");
	ctrl_comColor.AddString("초록");
	ctrl_comColor.AddString("노랑");
	ctrl_comColor.AddString("보라");
	ctrl_comColor.SetCurSel(0);

	CFont fnt;
	LOGFONT lf;
	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 30;
	lf.lfWeight = FW_BOLD;
	::lstrcpy(lf.lfFaceName, "Tahoma");
	fnt.CreateFontIndirect(&lf);
	GetDlgItem(IDC_STATIC_MODE)->SetFont(&fnt);
	GetDlgItem(IDC_STATIC_BINGO_CNT)->SetFont(&fnt);
	GetDlgItem(IDC_EDIT_QUIZ)->SetFont(&fnt);
	fnt.Detach();
	return TRUE;
}

void CGameRoomDlg::RefreshProfile(std::vector<Profile> vProfile)
{	
	for(size_t i = 0; i < vProfile.size(); i++)
	{
		m_bingoPanelDlg[i]->SetStaticNickName(vProfile[i].nickName);
	}
}

// Message Send Button Event
void CGameRoomDlg::OnBnClickedBtnSendMessage()
{
	CString message;
	GetDlgItemText(IDC_EDIT_SEND_MESSAGE, message);
	
	// BINGO WORD
	if(m_bingoPanelDlg[0]->CheckWord(message, m_rgb)) 
	{
		for(int i = 1; i < 4; i++)
		{
			m_bingoPanelDlg[i]->CheckWord(message, m_rgb);
		}
		return;
	}
	
	// CHATTING
	if(g_clientSocket.m_connected) // CLIENT
	{
		g_clientSocket.SendChatMsg(g_member.id, message);

		CString strTemp;
		strTemp.Format("[%s] %s", g_member.id, message);

		int index = ctrl_listChatMsg.AddString(strTemp);
		ctrl_listChatMsg.SetCurSel(index);
		SetDlgItemText(IDC_EDIT_SEND_MESSAGE, "");
	}
	else if(g_listenSocket.m_connected) // SERVER
	{
		g_listenSocket.SendAllChatMsg(g_member.nickName, message);

		CString strTemp;
		strTemp.Format("[%s] %s", g_member.id, message);

		int index = ctrl_listChatMsg.AddString(strTemp);
		ctrl_listChatMsg.SetCurSel(index);
		SetDlgItemText(IDC_EDIT_SEND_MESSAGE, "");
	}
}

void CGameRoomDlg::AddMessageToList(CString name, CString message)
{
	CString strTemp;
	strTemp.Format("[%s] %s",name, message);

	int index = ctrl_listChatMsg.AddString(strTemp);
	ctrl_listChatMsg.SetCurSel(index);

	SetDlgItemText(IDC_EDIT_SEND_MESSAGE, "");
}

void CGameRoomDlg::OnBnClickedBtnGameSatrtReady()
{
	if(g_clientSocket.m_connected) // CLIENT
	{
		if(m_bingoPanelDlg[0]->CheckAllWordIsNull())
		{
			AfxMessageBox("단어를 모두 입력해 주세요.");
			return;
		}
		CString words = m_bingoPanelDlg[0]->GetAllWords();
		g_clientSocket.SendGameReady(words);
		m_bingoPanelDlg[0]->SetAllWordsEnbled(FALSE);
		GetDlgItem(IDC_BTN_GAME_START_READY)->EnableWindow(FALSE);
	}
	else if(g_listenSocket.m_connected) // SERVER
	{
		if(m_bingoPanelDlg[0]->CheckAllWordIsNull())
		{
			AfxMessageBox("단어를 모두 입력해 주세요.");
			return;
		}

		if(g_listenSocket.m_vWords.size() != g_listenSocket.m_pServerSocketList.GetSize())
		{
			AfxMessageBox("모두 준비가 되지 않았습니다.");
			return;
		}
		GameStart(g_listenSocket.m_vWords);
		SetMode(1);

		CString words = m_bingoPanelDlg[0]->GetAllWords();
		g_listenSocket.m_vWords.insert(g_listenSocket.m_vWords.begin(), words);
		g_listenSocket.SendAllGameStart();

		m_bingoPanelDlg[0]->SetAllWordsEnbled(FALSE);
		GetDlgItem(IDC_BTN_GAME_START_READY)->EnableWindow(FALSE);
	}
}

// Set New Quiz
void CGameRoomDlg::SetQuiz(CString quiz)
{
	SetDlgItemText(IDC_EDIT_QUIZ, quiz);
}

// Set New Quiz
void CGameRoomDlg::GameStart(std::vector<CString> vWords)
{
	for(size_t i = 0; i < vWords.size(); i ++)
	{
		m_bingoPanelDlg[i + 1]->SetAllWords(vWords[i]);
	}
	AfxMessageBox("GAME START!");
}

// Set Game Mode
void CGameRoomDlg::SetMode(int mode)
{
	if(mode)
	{
		SetDlgItemText(IDC_STATIC_MODE, "내 차례");
	}
	else
	{
		SetDlgItemText(IDC_STATIC_MODE, "다른 유저 차례");
	}
}

void CGameRoomDlg::OnCbnSelchangeComboColor()
{
	CString color;
	ctrl_comColor.GetLBText(ctrl_comColor.GetCurSel(), color);
	if(color == "빨강")
		m_rgb = RGB(255,0,0);
	else if(color == "파랑")
		m_rgb = RGB(0,0,255);
	else if(color == "초록")
		m_rgb = RGB(0,255,0);
	else if(color == "노랑")
		m_rgb = RGB(255,255,0);
	else if(color == "보라")
		m_rgb = RGB(95,0,255);

	for(int i = 0; i < 4; i++)
	{
		m_bingoPanelDlg[i]->SetCheckedWordColor(m_rgb);
	}
}

// Ignore Enter Key, Add Enter Key Event
BOOL CGameRoomDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
			return TRUE;
		else if (pMsg->wParam == VK_RETURN)
		{	
			OnBnClickedBtnSendMessage();
			return TRUE;
		}
		
	}
	return CDialog::PreTranslateMessage(pMsg);
}

