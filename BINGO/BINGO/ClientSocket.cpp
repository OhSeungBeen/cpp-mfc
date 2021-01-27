// ClientSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BINGO.h"
#include "BINGODlg.h"
#include "ClientSocket.h"

// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}

void CClientSocket::SendHeader(byte command, int dataSize)
{
	Header header;
	header.command = command;
	header.startBit = 0x02;
	header.dataSize = dataSize;
	Send((char*)&header, sizeof(Header));

	int result;
	Receive(&result, sizeof(int));
}

void CClientSocket::SendResponse(byte command, byte result)
{
	Response response;
	response.command = command;
	response.result = result;
	Send(&response, sizeof(Response));
}

Response CClientSocket::RecvResponse()
{
	Response response;
	Receive(&response, sizeof(Response));
	return response;
}

// Send Server My Profile
void CClientSocket::SendProfile()
{
	// SEND HEADER
	SendHeader(PROFILE, sizeof(Profile));

	// SEND PROFILE BODY
	Profile profile;
	strcpy_s(profile.nickName, g_member.nickName);
	strcpy_s(profile.id, g_member.id);
	Send((char*)&profile, sizeof(Profile));

	// RECV RESULT RESPONSE
	Response response = RecvResponse();
	if(response.command != PROFILE)
		AfxMessageBox("PROFILE COM ERROR!!");
}

// Send Chatting Message To Server
void CClientSocket::SendChatMsg( CString name, CString message )
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

// Send Server My Profile
void CClientSocket::SendGameReady(CString words)
{
	// SEND HEADER
	SendHeader(GAME_READY, words.GetLength() + 1);

	// BODY
	Send(words.GetBuffer(), words.GetLength() + 1);

	// RECV RESULT RESPONSE
	Response response = RecvResponse();
	if(response.command != GAME_READY)
		AfxMessageBox("GAME_READY COM ERROR!!");
}


void CClientSocket::OnReceive(int nErrorCode)
{
	// HEADER RECV
	Header header;
	Receive(&header, sizeof(Header));

	if(header.startBit != 0x02) // START BIT CHECK
		return;

	int result = 1;
	Send(&result, sizeof(int));
	
	switch(header.command)
	{
		case FULL_ROOM : 
			{
				// RECEIVE BODY X

				// LOGIC
				((CBINGODlg*)AfxGetMainWnd())->m_watingRoomDlg->NoticeFullRoom();

				// SEND RESULT RESPONSE
				SendResponse(FULL_ROOM, 1);

				this->Close(); // Socket Close
				break;
			}
			case PROFILE :
				{
					// RECV PROFILE BODY
					int profileSize = header.dataSize / sizeof(Profile);

					for(int i = 0; i < profileSize; i++)
					{
						Profile profile;
						Receive((char*)&profile, sizeof(Profile));
						m_vProfile.push_back(profile);
					}
					// LOGIC
					((CBINGODlg*)AfxGetMainWnd())->m_gameRoomDlg->RefreshProfile(m_vProfile);
					// SEND RESULT RESPONSE
					SendResponse(PROFILE, 1);
					SendProfile();
					break;
				}
			case PROFILE2 :
				{
					// RECV PROFILE BODY
					int profileSize = header.dataSize / sizeof(Profile);

					for(int i = 0; i < profileSize; i++)
					{
						Profile profile;
						Receive((char*)&profile, sizeof(Profile));
						m_vProfile.push_back(profile);
					}
					// LOGIC
					((CBINGODlg*)AfxGetMainWnd())->m_gameRoomDlg->RefreshProfile(m_vProfile);

					// SEND RESULT RESPONSE
					SendResponse(PROFILE2, 1);
					break;
				}
			case MESSAGE :
				{
					//RECV BODY
					ChatMessage chatMessage;
					Receive((char*)&chatMessage, header.dataSize);

					// LOGIC
					((CBINGODlg*)AfxGetMainWnd())->m_gameRoomDlg->AddMessageToList((LPSTR)chatMessage.name, (LPSTR)chatMessage.message);

					// SEND RESPONSE
					SendResponse(MESSAGE, 1);
					break;
				}
			case QUIZ :
				{
					// RECV BODY
					char* pQuiz = new char[header.dataSize];
					Receive(pQuiz, header.dataSize);
					CString quiz = (LPSTR)pQuiz;
					delete[] pQuiz;

					// LOGIC
					((CBINGODlg*)AfxGetMainWnd())->m_gameRoomDlg->SetQuiz(quiz);
					// SEND RESULT RESPONSE
					SendResponse(QUIZ, 1);
					break;
				}
			case GAME_START :
				{
					int wordCount = header.dataSize;
					
					std::vector<CString> words;
					// RECV BODY
					for(int i = 0; i < wordCount; i++)
					{
						int wordSize;
						Receive(&wordSize, sizeof(int));

						char* pWord = new char[wordSize];
						Receive(pWord, wordSize);

						words.push_back((LPSTR)pWord);
						delete[] pWord;
					}
					// LOGIC
					((CBINGODlg*)AfxGetMainWnd())->m_gameRoomDlg->GameStart(words);
					// SEND RESULT RESPONSE
					SendResponse(GAME_START, 1);
					break;
				}
	}
	
	
	//case POINT :
	//	{
	//		// RECV BODY
	//		Point point;
	//		Receive((char*)&point, header.dataSize);
	//		
	//		// LOGIC
	//		((BINGODlg*)AfxGetMainWnd())->m_gameRoomDlg->Draw(&point);

	//		// SEND RESPONSE
	//		SendResponse(POINT, 1);
	//		break;

	//	}
	//case EXISTING_USER_IN_ROOM_PROFILE :
	//	{
	//		// RECV BODY PROFILE
	//		Profile profile;
	//		Receive((char*)&profile, sizeof(Profile));
	//		m_vProfile.push_back(profile);

	//		// RECV BODY IMAGE & LOGIC
	//		ULONGLONG fileSize;
	//		Receive(&fileSize, sizeof(ULONGLONG));
	//		
	//		byte* imageData = new byte[4096];
	//		DWORD dwRead;
	//		ULONGLONG receiveSize = 0;
	//		
	//		CString imageName = profile.imageName;
	//		CString imagePath = "profileImage\\client\\" + imageName;
	//		CFile file;
	//		file.Open(imagePath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
	//		do{
	//			dwRead = Receive(imageData, 4096);
	//			file.Write(imageData, dwRead);
	//			receiveSize += dwRead;
	//			if(receiveSize >= fileSize)
	//				break;
	//		}while(dwRead > 0);

	//		delete imageData;
	//		file.Close();

	//		// SEND RESULT RESPONSE
	//		SendResponse(EXISTING_USER_IN_ROOM_PROFILE, 1);
	//		((BINGODlg*)AfxGetMainWnd())->m_gameRoomDlg->AddProfileToList(&profile);

	//		break;
	//		
	//	}
	
	
	
	//case CHANGE_MODE :
	//	{
	//		// RECV BODY
	//		int mode;
	//		Receive(&mode, header.dataSize);

	//		// LOGIC
	//		((BINGODlg*)AfxGetMainWnd())->m_gameRoomDlg->SetMode(mode);

	//		// SEND RESULT RESPONSE
	//		SendResponse(CHANGE_MODE, 1);
	//		break;
	//	}
	//}

}




