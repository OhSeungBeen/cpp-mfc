#include "stdafx.h"
#include "CATCHMIND.h"
#include "GameRoomDlg.h"
#include "Global.h"
#include "ProfileDlg.h"


IMPLEMENT_DYNAMIC(CGameRoomDlg, CDialog)

CGameRoomDlg::CGameRoomDlg(CWnd* pParent /*=NULL*/)
: CDialog(CGameRoomDlg::IDD, pParent)
{
	m_lButtonClick = FALSE;
	m_thickness = 1;
	m_rgb = RGB(0, 0, 0);
	m_mode = 1;
}

CGameRoomDlg::~CGameRoomDlg()
{

}

void CGameRoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MESSAGE, ctrl_listChatMsg);
	DDX_Control(pDX, IDC_LIST_USER, ctrl_listProfile);
	DDX_Control(pDX, IDC_COMBO_THINKNESS, ctrl_comThinkness);
	DDX_Control(pDX, IDC_COMBO_COLOR, ctrl_comColor);
	DDX_Control(pDX, IDC_EDIT_QUIZ, ctrl_editQuiz);
}

BEGIN_MESSAGE_MAP(CGameRoomDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_SEND_MESSAGE, &CGameRoomDlg::OnBnClickedBtnSendMessage)
	ON_BN_CLICKED(IDC_BTN_PROFILE, &CGameRoomDlg::OnBnClickedBtnProfile)
	ON_CBN_SELCHANGE(IDC_COMBO_THINKNESS, &CGameRoomDlg::OnCbnSelchangeComboThinkness)
	ON_CBN_SELCHANGE(IDC_COMBO_COLOR, &CGameRoomDlg::OnCbnSelchangeComboColor)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CGameRoomDlg::OnBnClickedBtnClear)
	ON_BN_CLICKED(IDC_BTN_SERIAL_MODE_ORDER, &CGameRoomDlg::OnBnClickedBtnSerialModeOrder)
END_MESSAGE_MAP()

BOOL CGameRoomDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ctrl_comColor.AddString("검정");
	ctrl_comColor.AddString("파랑");
	ctrl_comColor.AddString("초록");
	ctrl_comColor.AddString("노랑");
	ctrl_comColor.AddString("보라");
	ctrl_comColor.SetCurSel(0);

	ctrl_comThinkness.AddString("1");
	ctrl_comThinkness.AddString("2");
	ctrl_comThinkness.AddString("3");
	ctrl_comThinkness.AddString("4");
	ctrl_comThinkness.AddString("5");
	ctrl_comThinkness.SetCurSel(0);
	return TRUE;
}


// Message Send Button Event
void CGameRoomDlg::OnBnClickedBtnSendMessage()
{
	CString message;
	GetDlgItemText(IDC_EDIT_SEND_MESSAGE, message);

	// TCP/IP
	if(g_clientSocket.m_connected) // CLIENT
	{
		g_clientSocket.SendChatMsg(g_member.id, message);
		CString strTemp;
		strTemp.Format("[%s] %s", g_member.id, message);
		int index = ctrl_listChatMsg.AddString(strTemp);
		ctrl_listChatMsg.SetCurSel(index);
		SetDlgItemText(IDC_EDIT_SEND_MESSAGE, "");
		return;
	}

	if(g_listenSocket.m_connected) // SERVER
	{
		CString preQuiz = g_listenSocket.m_quiz;
		if(preQuiz == message) // correct answer
		{
			CString newQuiz = g_dataBase.SelectRandomQuiz();

			g_listenSocket.m_quiz = newQuiz;
			g_listenSocket.SendAllQuiz(newQuiz);
			g_listenSocket.SendAllMode(0);

			CString managerName = "MANAGER";
			message.Format("* * *%s Answer!! : %s * * *",g_member.name, message);
			g_listenSocket.SendAllChatMsg(managerName, message);

			SetQuiz(newQuiz);
			SetMode(1);
			int index = ctrl_listChatMsg.AddString("[" + managerName + "]" + message);
			ctrl_listChatMsg.SetCurSel(index);
		}
		else // chatting
		{
			g_listenSocket.SendAllChatMsg(g_member.name, message);
			CString strTemp;
			strTemp.Format("[%s] %s", g_member.id, message);
			int index = ctrl_listChatMsg.AddString(strTemp);
			ctrl_listChatMsg.SetCurSel(index);
			SetDlgItemText(IDC_EDIT_SEND_MESSAGE, "");
		}
		return;
	}

	// SERIAL
	if(g_serial.m_connected)
	{
		CString oldQuiz;
		GetDlgItemText(IDC_EDIT_QUIZ, oldQuiz);
		
		if(oldQuiz == message) // correct answer
		{
			CString newQuiz = g_dataBase.SelectRandomQuiz();
			
			CString managerName = "MANAGER";
			message.Format("* * *%s Answer!! : %s * * *",g_member.name, message);
			g_serial.WriteChatMessage(managerName, message);

			g_serial.WriteQuiz(newQuiz);
			g_serial.WriteMode(0);

			SetQuiz(newQuiz);
			SetMode(1);
			int index = ctrl_listChatMsg.AddString("[" + managerName + "]" + message);
			ctrl_listChatMsg.SetCurSel(index);
			SetDlgItemText(IDC_EDIT_SEND_MESSAGE, "");
		}
		else
		{
			g_serial.WriteChatMessage(g_member.id, message);
			CString strTemp;
			strTemp.Format("[%s] %s", g_member.id, message);
			int index = ctrl_listChatMsg.AddString(strTemp);
			ctrl_listChatMsg.SetCurSel(index);
			SetDlgItemText(IDC_EDIT_SEND_MESSAGE, "");
		}
	}
}

void CGameRoomDlg::AddMessageToList(CString name, CString message)
{
	CString strTemp;
	strTemp.Format("[%s] %s",name, message);
	int index = ctrl_listChatMsg.AddString(strTemp);
	ctrl_listChatMsg.SetCurSel(index);
}



// Add One User Profile To List
void CGameRoomDlg::AddProfileToList(Profile* profile)
{
	ctrl_listProfile.AddString(profile->name);
}

// Add User Profiles To List
void CGameRoomDlg::AddProfilesToList(std::vector<Profile>* vProfile)
{
	for(size_t i = 0; i < vProfile->size(); i++)
	{
		ctrl_listProfile.AddString(vProfile->at(i).name);
	}
}

// Profile Button Event
void CGameRoomDlg::OnBnClickedBtnProfile()
{
	int index = ctrl_listProfile.GetCurSel();
	if(index == -1)
	{
		AfxMessageBox("PLEASE SELECT USER");
		return;
	}

	CString name;
	CString id;
	CString imageName;

	// TCP/IP
	if(g_clientSocket.m_connected) // CLIENT
	{

		name = g_clientSocket.m_vProfile[index].name;
		id = g_clientSocket.m_vProfile[index].id;
		if(index == 0)
			imageName.Format("%s", g_clientSocket.m_vProfile[index].imageName);
		else
			imageName.Format("client\\%s", g_clientSocket.m_vProfile[index].imageName);
	}
	else if(g_listenSocket.m_connected) // SERVER
	{
		name = g_listenSocket.m_vProfile[index].name;
		id = g_listenSocket.m_vProfile[index].id;
		if(index == 0)
			imageName.Format("%s", g_listenSocket.m_vProfile[index].imageName);
		else
			imageName.Format("server\\%s", g_listenSocket.m_vProfile[index].imageName);
	}
	else if(g_serial.m_connected)
	{
		name = g_serial.m_vProfile[index].name;
		id = g_serial.m_vProfile[index].id;
		if(index == 0)
			imageName.Format("%s", g_serial.m_vProfile[index].imageName);
		else
			imageName.Format("client\\%s", g_serial.m_vProfile[index].imageName);
	}
	CProfileDlg profileDlg(name, id, imageName);
	profileDlg.DoModal();
}

void CGameRoomDlg::Draw(Point* point)
{
	CClientDC dc(this);

	CPoint startPoint, endPoint;
	startPoint.SetPoint(point->startX, point->startY);
	endPoint.SetPoint(point->endX, point->endY);

	CPen pen;
	pen.CreatePen(PS_SOLID, point->thinkness ,point->rgb);
	CPen *oldPen=dc.SelectObject(&pen);

	dc.MoveTo(startPoint);
	dc.LineTo(endPoint);

	dc.SelectObject(oldPen);
}

// Mouse L Button Down
// Send Point To Server or Client or Serial Port
void CGameRoomDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_mode == 0)
		return;

	m_lButtonClick = TRUE;
	//SetCapture();
	m_prePoint = point;

	CClientDC dc(this);

	// draw in picture control
	CRect rect;
	GetDlgItem(IDC_STATIC_PANEL)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	if(point.y < rect.top || point.y < rect.top)
		return;
	if(point.y > rect.bottom || point.y > rect.bottom)
		return;
	if(point.x > rect.right || point.x > rect.right)
		return;
	if(point.x < rect.left || point.x < rect.left)
		return;

	CPen pen;
	pen.CreatePen(PS_SOLID, m_thickness ,m_rgb);
	CPen *oldPen=dc.SelectObject(&pen);

	dc.MoveTo(point);
	dc.LineTo(point);



	// TCP/IP
	if(g_listenSocket.m_connected)// Server
		g_listenSocket.SendAllPoint(m_prePoint, point, m_thickness, m_rgb);

	if(g_clientSocket.m_connected) // Client
		g_clientSocket.SendPoint(m_prePoint, point, m_thickness, m_rgb);

	// Serial
	if(g_serial.m_connected)
		g_serial.WritePoint(point, point, m_thickness, m_rgb);

	dc.SelectObject(oldPen);
	CDialog::OnLButtonDown(nFlags, point);
}

// Mouse Move 
// Send Point To Server or Client or Serial Port
void CGameRoomDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_mode == 0)
		return;

	if(m_lButtonClick)
	{
		CClientDC dc(this);

		// draw in picture control	
		CRect rect;
		GetDlgItem(IDC_STATIC_PANEL)->GetWindowRect(&rect);
		ScreenToClient(&rect);
		if(m_prePoint.y < rect.top || m_prePoint.y < rect.top)
			return;
		if(m_prePoint.y > rect.bottom || m_prePoint.y > rect.bottom)
			return;
		if(m_prePoint.x > rect.right || m_prePoint.x > rect.right)
			return;
		if(m_prePoint.x < rect.left || m_prePoint.x < rect.left)
			return;
		if(point.y < rect.top || point.y < rect.top)
			return;
		if(point.y > rect.bottom || point.y > rect.bottom)
			return;
		if(point.x > rect.right || point.x > rect.right)
			return;
		if(point.x < rect.left || point.x < rect.left)
			return;

		CPen pen;
		pen.CreatePen(PS_SOLID, m_thickness ,m_rgb);
		CPen *oldPen=dc.SelectObject(&pen);

		dc.MoveTo(m_prePoint);
		dc.LineTo(point);

		// TCP/IP
		if(g_listenSocket.m_connected)// Server
			g_listenSocket.SendAllPoint(m_prePoint, point, m_thickness, m_rgb);

		if(g_clientSocket.m_connected) // Client
			g_clientSocket.SendPoint(m_prePoint, point, m_thickness, m_rgb);

		// Serial
		if(g_serial.m_connected)
			g_serial.WritePoint(m_prePoint, point, m_thickness, m_rgb);

		/*dc.SelectObject(oldPen);*/
		m_prePoint = point;
	}
	CDialog::OnMouseMove(nFlags, point);
}

// Message Mouse L Button Up
void CGameRoomDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_lButtonClick = FALSE;
	//ReleaseCapture();
	CDialog::OnLButtonUp(nFlags, point);
}

// Set New Quiz
void CGameRoomDlg::SetQuiz(CString quiz)
{
	SetDlgItemText(IDC_EDIT_QUIZ, quiz);
}

// Set Game Mode
void CGameRoomDlg::SetMode(int mode)
{
	m_mode = mode;
	if(mode)
	{
		SetDlgItemText(IDC_STATIC_MODE, "그림을 그려주세요!");
		GetDlgItem(IDC_EDIT_QUIZ)->ShowWindow(TRUE);
	}
	else
	{
		SetDlgItemText(IDC_STATIC_MODE, "그림을 보고 문제를 맞히세요!");
		GetDlgItem(IDC_EDIT_QUIZ)->ShowWindow(FALSE);
		GetDlgItem(IDC_BTN_SERIAL_MODE_ORDER)->ShowWindow(FALSE);
	}
}

// Select Draw Pen Thickness (ComBoBox)
void CGameRoomDlg::OnCbnSelchangeComboThinkness()
{
	CString thickness;
	ctrl_comThinkness.GetLBText(ctrl_comThinkness.GetCurSel(), thickness);
	if(thickness == "1")
		m_thickness = 1;
	else if(thickness == "2")
		m_thickness = 2;
	else if(thickness == "3")
		m_thickness = 3;
	else if(thickness == "4")
		m_thickness = 4;
	else if(thickness == "5")
		m_thickness = 5;
}

// Select Draw Color (ComBoBox)
void CGameRoomDlg::OnCbnSelchangeComboColor()
{
	CString color;
	ctrl_comColor.GetLBText(ctrl_comColor.GetCurSel(), color);
	if(color == "검정")
		m_rgb = RGB(0,0,0);
	else if(color == "파랑")
		m_rgb = RGB(0,0,255);
	else if(color == "초록")
		m_rgb = RGB(0,255,0);
	else if(color == "노랑")
		m_rgb = RGB(255,255,0);
	else if(color == "보라")
		m_rgb = RGB(95,0,255);
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

void CGameRoomDlg::OnBnClickedBtnClear()
{
	CClientDC dc(this);
}


void CGameRoomDlg::OnBnClickedBtnSerialModeOrder()
{
	CString quiz = g_dataBase.SelectRandomQuiz();

	g_serial.WriteMode(0);
	g_serial.WriteQuiz(quiz);

	GetDlgItem(IDC_BTN_SERIAL_MODE_ORDER)->ShowWindow(FALSE);
	SetDlgItemText(IDC_EDIT_QUIZ, quiz);
}
