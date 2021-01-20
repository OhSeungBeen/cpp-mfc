// ServerSocket.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CATCHMIND.h"
#include "CATCHMINDDlg.h"
#include "ServerSocket.h"
#include "Data.h"
#include "Global.h"

// CServerSocket

CServerSocket::CServerSocket(CObList* pServerSocketList, std::vector<Profile>* vProfile)
{
	this->m_pServerSocketList = pServerSocketList;
	this->m_vProfile = vProfile;
}

CServerSocket::~CServerSocket()
{
}

// Send Full Room Notice
void CServerSocket::SendFullRoom()
{
	SendHeader(FULL_ROOM, 0);
}

// Send Private Room Notice
void CServerSocket::SendPrivate(CString password)
{
	char *pString = password.GetBuffer();
	int passwordSize = g_listenSocket.m_password.GetLength() + 1;
	SendHeader(PRIVATE_ROOM, passwordSize);
	Send(pString, passwordSize);
}

// Send Accept Success Notice
void CServerSocket::SendAccept()
{
	SendHeader(ACCEPT, 0);
}

// Send Header
void CServerSocket::SendHeader(byte command, int dataSize)
{
	Header header;
	header.startBit = 0x21;
	header.command = command;
	header.dataSize = dataSize;
	Send((char*)&header, sizeof(Header));
	byte result;
	Receive(&result, sizeof(byte));
}


// Send Chatting Message
void CServerSocket::SendChatMsg(CString name, CString message)
{
	ChatMessage chatMessage;
	strcpy_s(chatMessage.name, name);
	strcpy_s(chatMessage.message, message);
	SendHeader(MESSAGE, sizeof(ChatMessage));
	Send((char*)&chatMessage, sizeof(ChatMessage));
}

// Send Point (Draw)
void CServerSocket::SendPoint(CPoint startPoint, CPoint endPoint, int thinkness, COLORREF rgb)
{
	Point point;
	point.startX = (short)startPoint.x;
	point.startY = (short)startPoint.y;
	point.endX = (short)endPoint.x;
	point.endY = (short)endPoint.y;
	point.thinkness = thinkness;
	point.rgb = rgb;

	SendHeader(POINT, sizeof(Point));
	Send(&point, sizeof(Point));
	byte result;
	Receive(&result, sizeof(byte));
}

// Send Quiz
void CServerSocket::SendQuiz(CString quiz)
{
	int quizSize= quiz.GetLength() + 1;
	char *pQuiz = new char[quizSize];
	memcpy(pQuiz, quiz.GetBuffer(), quizSize);
	SendHeader(QUIZ, quizSize);
	Send(pQuiz, quizSize);
	delete[] pQuiz;
}

// Send OtherClient Chatting Message
void CServerSocket::SendOtherChatMsg(CString name, CString message)
{
	POSITION pos = m_pServerSocketList->GetHeadPosition();
	while (pos != NULL)
	{
		CServerSocket* serverSocket = (CServerSocket*)m_pServerSocketList->GetNext(pos);
		if(serverSocket == this) continue;
		serverSocket->SendChatMsg(name, message);
	}
}



// Send Other Client Mode
void CServerSocket::SendOtherMode(int mode)
{
	POSITION pos = m_pServerSocketList->GetHeadPosition();
	while (pos != NULL)
	{
		CServerSocket* serverSocket = (CServerSocket*)m_pServerSocketList->GetNext(pos);
		if(serverSocket == this) continue;
		serverSocket->SendMode(mode);
	}
}

// Send OtherClient Quiz
void CServerSocket::SendOhterQuiz(CString quiz)
{
	POSITION pos = m_pServerSocketList->GetHeadPosition();
	while (pos != NULL)
	{
		CServerSocket* serverSocket = (CServerSocket*)m_pServerSocketList->GetNext(pos);
		if(serverSocket == this) continue;
		serverSocket->SendQuiz(quiz);
	}
}

void CServerSocket::SendMode(int mode)
{
	SendHeader(CHANGE_MODE, sizeof(int));
	Send(&mode, sizeof(int));
}

// Send OtherClient Profile Received Profile
void CServerSocket::SendOtherProfile(Profile profile)
{
	POSITION pos = m_pServerSocketList->GetHeadPosition();
	while (pos != NULL)
	{
		CServerSocket* serverSocket = (CServerSocket*)m_pServerSocketList->GetNext(pos);
		if(serverSocket == this) continue;
		// profile
		serverSocket->SendHeader(PROFILE2, sizeof(Profile));
		serverSocket->Send((char*)&profile, sizeof(Profile));

		// image
		CFile imageFile;
		byte* imageData = new byte[4096];
		DWORD dwRead;

		CString imageName;
		imageName.Format("profileImage\\server\\%s", profile.imageName);
		imageFile.Open(imageName, CFile::modeReadWrite | CFile::typeBinary);

		ULONGLONG imageSize = imageFile.GetLength();
		serverSocket->Send(&imageSize, sizeof(ULONGLONG));
		do{
			dwRead = imageFile.Read(imageData, 4096);
			serverSocket->Send(imageData, dwRead);
		}while(dwRead > 0);

		delete imageData;
		imageFile.Close();
	}
}

// Send Client OtherClientProfile and ServerProfile (include image data)
void CServerSocket::SendProfiles()
{
	int size = m_vProfile->size();
	SendHeader(PROFILE, sizeof(Profile) * size);
	for(int i = 0; i < size; i++)
	{
		Send((char*)&m_vProfile->at(i), sizeof(Profile));
		
		// image send
		CFile imageFile;
		byte* imageData = new byte[4096];
		DWORD dwRead;
		
		CString imageName;
		if(i == 0) // Server
			imageName.Format("profileImage\\%s", m_vProfile->at(i).imageName);
		else
			imageName.Format("profileImage\\server\\%s", m_vProfile->at(i).imageName); // Client
		
		imageFile.Open(imageName, CFile::modeRead | CFile::typeBinary);

		ULONGLONG imageSize = imageFile.GetLength();

		Send(&imageSize, sizeof(ULONGLONG));

		do{
			dwRead = imageFile.Read(imageData, 4096);

			Send(imageData, dwRead);
			
		}while(dwRead > 0);
		
		byte result;
		Receive(&result, sizeof(byte)); 

		delete imageData;
		imageFile.Close();
	}
}


CString CServerSocket::RecvString(int dataSize)
{
	char* pChar = new char[dataSize];
	Receive(pChar, dataSize);
	CString str = (LPSTR)pChar;
	delete[] pChar;
	return str;
}

void CServerSocket::OnReceive(int nErrorCode)
{
	Header header;
	Receive(&header, sizeof(Header));
	byte result = 1;
	Send(&result, sizeof(byte));

	switch(header.command)
	{
	case POINT :
		{
			Point point;
			Receive(&point, header.dataSize);
			
			POSITION pos = m_pServerSocketList->GetHeadPosition();
			while (pos != NULL) {
				CServerSocket* serverSocket = (CServerSocket*)m_pServerSocketList->GetNext(pos);
				serverSocket->SendHeader(POINT, sizeof(Point));
				serverSocket->Send((char*)&point, sizeof(Point));
				byte result;
				Receive(&result, sizeof(byte));
			}
			//((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->RecvDraw(point);
			SendMessage(((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->m_hWnd, WM_DRAW, 0, (LPARAM)&point);
			
			break;
		}
	case MESSAGE :
		{	
			ChatMessage chatMessage;
			Receive((char*)&chatMessage, header.dataSize);
			CString name = (LPSTR)chatMessage.name;
			CString message = (LPSTR)chatMessage.message;
			CString preQuiz = g_listenSocket.m_quiz;

			if(message == preQuiz) // Answer
			{
				CString managerName = "MANAGER";
				message.Format("* * *%s Answer!! : %s * * *",name, message);
				g_listenSocket.SendAllChatMsg(managerName, message);
				SendMessage(((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->m_hWnd, WM_RECV_MESSAGE, (WPARAM)&managerName, (LPARAM)&message);
				// Alter Mode
				SendOtherMode(0); // OhterClient Mode : 0
				SendMode(1); // Correct Answer Client Mode : 1
				((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->SetMode(0); // Server Mode : 0
				
				// Set New Quiz
				CString newQuiz = g_dataBase.SelectRandomQuiz();
				g_listenSocket.m_quiz = newQuiz;
				SendOhterQuiz(newQuiz);
				SendQuiz(newQuiz);
				((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->SetQuiz(newQuiz);
			}
			else // Chatting
			{
				SendOtherChatMsg(name, message);
				SendMessage(((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->m_hWnd, WM_RECV_MESSAGE, (WPARAM)&name, (LPARAM)&message);
			}
			break;
		}
	case PROFILE :
		{
			Profile profile;
			Receive((char*)&profile, header.dataSize);
			m_profile = profile;
			m_vProfile->push_back(profile);

			ULONGLONG fileSize;
			Receive(&fileSize, sizeof(ULONGLONG));
			
			// image save
			byte* imageData = new byte[4096];
			DWORD dwRead;
			ULONGLONG receiveSize = 0;
			
			CString imageName = profile.imageName;
			CString imagePath = "profileImage\\server\\" + imageName;

			CFile file;
			file.Open(imagePath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
			do{
				dwRead = Receive(imageData, 4096);
				file.Write(imageData, dwRead);
				receiveSize += dwRead;
				if(receiveSize >= fileSize)
					break;
			}while(dwRead > 0);

			delete imageData;
			file.Close();
			SendMessage(((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->m_hWnd, WM_ONE_USER_PROFILE, 0, (LPARAM)&profile);

			SendOtherProfile(profile);
			break;
		}
	}
}

// Client Disconnect
void CServerSocket::OnClose(int nErrorCode)
{
	CSocket::OnClose(nErrorCode);
	CServerSocket* p;
	POSITION pos = m_pServerSocketList->GetHeadPosition(), pre_pos;
	while (pos != NULL) 
	{
		pre_pos = pos;
		p = (CServerSocket *)m_pServerSocketList->GetNext(pos);
		if (p == this) 
		{
			m_pServerSocketList->RemoveAt(pre_pos);
			delete p;
		}
	}
	AfxMessageBox("CLIENT(USER) CLOSE");
	g_logManager.Log("CLIENT(USER) CLOSE");
}