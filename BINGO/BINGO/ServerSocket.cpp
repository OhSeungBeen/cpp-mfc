// ServerSocket.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "BINGO.h"
#include "BINGODlg.h"
#include "ServerSocket.h"
#include "Data.h"
#include "Global.h"

// CServerSocket

CServerSocket::CServerSocket(CObList* pServerSocketList, std::vector<Profile>* vProfile, std::vector<CString>* vWords)
{
	this->m_pServerSocketList = pServerSocketList;
	this->m_vProfile = vProfile;
	this->m_vWords = vWords;
}

CServerSocket::~CServerSocket()
{
}

// Send Header
void CServerSocket::SendHeader(byte command, int dataSize)
{
	Header header;
	header.startBit = 0x02;
	header.command = command;
	header.dataSize = dataSize;
	Send((char*)&header, sizeof(Header));

	int result;
	Receive(&result, sizeof(int));
}

void CServerSocket::SendResponse(byte command, byte result)
{
	Response response;
	response.command = command;
	response.result = result;
	Send(&response, sizeof(Response));
}

Response CServerSocket::RecvResponse()
{
	Response response;
	Receive(&response, sizeof(Response));
	return response;
}

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

// Send OtherClient Profile Received Profile
void CServerSocket::SendProfiles()
{
	int profileSize = m_vProfile->size();
	
	// SEND HEADER
	SendHeader(PROFILE, sizeof(Profile) * profileSize);
	for(int i = 0; i < profileSize; i++)
	{
		// SEND PROFILE BODY
		Send((char*)&m_vProfile->at(i), sizeof(Profile));
	}
	// RECV RESULT RESPONSE
	Response response;
	Receive(&response, sizeof(Response));
	if(response.command != PROFILE)
		AfxMessageBox("PROFILE COM ERROR!!");
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
		serverSocket->SendHeader(PROFILE2, sizeof(Profile));

		// SEND PROFILE BODY
		serverSocket->Send((char*)&profile, sizeof(Profile));

		// RECV RESULT RESPONSE
		Response response;
		serverSocket->Receive(&response, sizeof(Response));
		if(response.command != PROFILE2)
			AfxMessageBox("PROFILE2 COM ERROR!!");
	}
}

// Send Chatting Message
void CServerSocket::SendChatMsg(CString name, CString message)
{
	ChatMessage chatMessage;
	strcpy_s(chatMessage.name, name);
	strcpy_s(chatMessage.message, message);

	// SEND HEADER
	SendHeader(MESSAGE, sizeof(ChatMessage));
	
	// SEND BODY
	Send((char*)&chatMessage, sizeof(ChatMessage));

	// RECV RESULT RESPONSE
	Response response = RecvResponse();
	if(response.command != MESSAGE)
		AfxMessageBox("MESSAGE COM ERROR!!");
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
		AfxMessageBox("QUIZ COM ERROR!!");
	delete[] pQuiz;
}

// Send Other Client Mode
//void CServerSocket::SendOtherMode(int mode)
//{
//	POSITION pos = m_pServerSocketList->GetHeadPosition();
//	while (pos != NULL)
//	{
//		CServerSocket* serverSocket = (CServerSocket*)m_pServerSocketList->GetNext(pos);
//		if(serverSocket == this) continue;
//		serverSocket->SendMode(mode);
//	}
//}

// Send OtherClient Quiz
//void CServerSocket::SendOhterQuiz(CString quiz)
//{
//	POSITION pos = m_pServerSocketList->GetHeadPosition();
//	while (pos != NULL)
//	{
//		CServerSocket* serverSocket = (CServerSocket*)m_pServerSocketList->GetNext(pos);
//		if(serverSocket == this) continue;
//		serverSocket->SendQuiz(quiz);
//	}
//}

//void CServerSocket::SendMode(int mode)
//{
//	// SEND HEADER
//	SendHeader(CHANGE_MODE, sizeof(int));
//
//	// SEND BODY
//	Send(&mode, sizeof(int));
//
//	// RECV RESULT RESPONSE
//	Response response;
//	Receive(&response, sizeof(Response));
//	if(response.command != CHANGE_MODE)
//		AfxMessageBox("CHANGE_MODE COM ERROR!!");
//}


//CString CServerSocket::RecvString(int dataSize)
//{
//	char* pChar = new char[dataSize];
//	Receive(pChar, dataSize);
//	CString str = (LPSTR)pChar;
//	delete[] pChar;
//	return str;
//}



void CServerSocket::OnReceive(int nErrorCode)
{
	Header header;
	Receive(&header, sizeof(Header));
	
	int result = 1;
	Send(&result, sizeof(int));

	if(header.startBit != 0x02) // START BIT CHECK
		return;

	switch(header.command)
	{
		case PROFILE :
			{
				//RECV PROFILE BODY
				Profile profile;
				Receive(&profile, header.dataSize);

				// LOGIC
				m_vProfile->push_back(profile);

				((CBINGODlg*)AfxGetMainWnd())->m_gameRoomDlg->RefreshProfile(*m_vProfile);
				// SEND RESULT RESPONSE
				SendResponse(PROFILE, 1);
				SendOtherProfile(profile);
				SendQuiz(g_listenSocket.m_quiz);
				break;
			}

			case MESSAGE :
				{
					// RECV BODY
					ChatMessage chatMessage;
					Receive((char*)&chatMessage, header.dataSize);

					// SEND RESPONSE
					SendResponse(MESSAGE, 1);

					CString name = (LPSTR)chatMessage.name;
					CString message = (LPSTR)chatMessage.message;
					SendOtherChatMsg(name, message);
					((CBINGODlg*)AfxGetMainWnd())->m_gameRoomDlg->AddMessageToList(name, message);
					break;
				}
			case GAME_READY :
				{
					// RECV BODY
					char* pWords = new char[header.dataSize];
					Receive(pWords, header.dataSize);
					CString words = (LPSTR)pWords;
					delete[] pWords;
					
					// LOGIC
					m_vWords->push_back(words);

					// SEND RESPONSE
					SendResponse(GAME_READY, 1);
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
}