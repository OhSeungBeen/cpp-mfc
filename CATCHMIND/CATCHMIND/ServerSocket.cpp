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

void CServerSocket::SendResponse(byte command, byte result)
{
	Response response;
	response.command = command;
	response.result = result;
	Send(&response, sizeof(Response));
}

// Send Full Room Notice
void CServerSocket::SendFullRoom()
{
	//SEND HEADER
	SendHeader(FULL_ROOM, 0);

	//SEND BODY X

	//RECV RESULT RESPONSE
	Response response = RecvResponse();
	if(response.command != FULL_ROOM)
		AfxMessageBox("FULL_ROOM COM ERROR!!");
}

// Send Private Room Notice
void CServerSocket::SendPrivate(CString password)
{
	char *pString = password.GetBuffer();
	int passwordSize = g_listenSocket.m_password.GetLength() + 1;

	// SEND HEADER
	SendHeader(PRIVATE_ROOM, passwordSize);

	// SEND BODY
	Send(pString, passwordSize);

	// RECV RESULT RESPONSE
	Response response = RecvResponse();
	if(response.command != PRIVATE_ROOM)
		AfxMessageBox("PRIVATE_ROOM COM ERROR!!");
}

// Send Accept Success Notice
void CServerSocket::SendAccept()
{
	// SEND HEADER
	SendHeader(ACCEPT, 0);

	// SEND BODY X

	// RECV RESULT RESPONSE
	Response response = RecvResponse();
	if(response.command != ACCEPT)
		AfxMessageBox("ACCEPT COM ERROR!!");
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

	// SEND HEADER
	SendHeader(QUIZ, quizSize);

	// SEND BODY
	Send(pQuiz, quizSize);
	
	// RECV RESULT RESPONSE
	Response response = RecvResponse();
	if(response.command != QUIZ)
		AfxMessageBox("ACCEPT COM ERROR!!");

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
		// SEND HEADER
		serverSocket->SendHeader(JOINED_NEW_USER_PROFILE, sizeof(Profile));

		// SEND PROFILE BODY
		serverSocket->Send((char*)&profile, sizeof(Profile));

		// SEND IMAGE BODY
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
		// RECV RESULT RESPONSE
		Response response = RecvResponse();
		if(response.command != JOINED_NEW_USER_PROFILE)
			AfxMessageBox("JOINED_NEW_USER_PROFILE COM ERROR!!");
	}
}

void CServerSocket::RequestProfile()
{
	// SEND HEADER
	SendHeader(REQUEST_PROFILE, 0);
	// BODY X
	
	//
	// RECV RESULT RESPONSE
	/*Response response = RecvResponse();
	if(response.command != REQUEST_PROFILE)
		AfxMessageBox("REQUEST_PROFILE COM ERROR!!");*/
}

// Send Client OtherClientProfile and ServerProfile (include image data)
void CServerSocket::SendProfiles()
{
	int size = m_vProfile->size();
	for(int i = 0; i < size; i++)
	{

		// SEND HEADER 
		SendHeader(EXISTING_USER_IN_ROOM_PROFILE, sizeof(Profile));
	
		// PROFILE BODY
		Send((char*)&m_vProfile->at(i), sizeof(Profile));

		// IMAGE BODY
		CFile imageFile;
		byte* imageData = new byte[4096];
		DWORD dwRead;

		CString imageName;
		if(i == 0) // Server profile image
			imageName.Format("profileImage\\%s", m_vProfile->at(i).imageName);
		else
			imageName.Format("profileImage\\server\\%s", m_vProfile->at(i).imageName); // client profile image path

		imageFile.Open(imageName, CFile::modeRead | CFile::typeBinary);

		ULONGLONG imageSize = imageFile.GetLength();
		Send(&imageSize, sizeof(ULONGLONG));

		do{
			dwRead = imageFile.Read(imageData, 4096);

			Send(imageData, dwRead);

		}while(dwRead > 0);

		delete imageData;
		imageFile.Close();	

		// RECV RESULT RESPONSE
		Response response = RecvResponse();
		if(response.command != EXISTING_USER_IN_ROOM_PROFILE)
			AfxMessageBox("EXISTING_USER_IN_ROOM_PROFILE COM ERROR!!");
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

Response CServerSocket::RecvResponse()
{
	Response response;
	Receive(&response, sizeof(Response));
	return response;
}

void CServerSocket::OnReceive(int nErrorCode)
{
	Header header;
	Receive(&header, sizeof(Header));

	byte result = 1;
	Send(&result, sizeof(byte));

	if(header.startBit != 0x21) // START BIT CHECK
		return;

	switch(header.command)
	{
	case POINT :
		{
			Point point;
			Receive(&point, header.dataSize);

			byte result = 1;
			Send(&result, sizeof(byte));

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
				/*SendOhterQuiz(newQuiz);
				SendQuiz(newQuiz);*/
				((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->SetQuiz(newQuiz);
			}
			else // Chatting
			{
				SendOtherChatMsg(name, message);
				SendMessage(((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->m_hWnd, WM_RECV_MESSAGE, (WPARAM)&name, (LPARAM)&message);
			}
			break;
		}
	case JOINED_NEW_USER_PROFILE :
		{
			//RECV PROFILE BODY
			Profile profile;
			Receive(&profile, header.dataSize);

			// RECV IMAGE BODY & LOGIC
			m_profile = profile;
			m_vProfile->push_back(profile);

			ULONGLONG fileSize;
			Receive(&fileSize, sizeof(ULONGLONG));

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
			
			((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->AddProfileToList(&profile);
			// SEND RESULT RESPONSE
			SendResponse(JOINED_NEW_USER_PROFILE, 1);

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