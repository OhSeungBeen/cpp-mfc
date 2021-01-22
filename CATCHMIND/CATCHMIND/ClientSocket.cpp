// ClientSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CATCHMIND.h"
#include "CATCHMINDDlg.h"
#include "ClientSocket.h"
#include "Data.h"
#include "PasswordDlg.h"

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
	header.startBit = 0x21;
	header.dataSize = dataSize;
	Send((char*)&header, sizeof(Header));

	byte result;
	Receive(&result, sizeof(byte));
}


// Send Chatting Message To Server
void CClientSocket::SendChatMsg( CString name, CString message )
{
	ChatMessage chatMessage;
	strcpy_s(chatMessage.name, name);
	strcpy_s(chatMessage.message, message);
	SendHeader(MESSAGE, sizeof(ChatMessage));
	Send((char*)&chatMessage, sizeof(ChatMessage));
}

// Send Server My Profile
void CClientSocket::SendMyProfile()
{
	// SEND HEADER
	SendHeader(JOINED_NEW_USER_PROFILE, sizeof(Profile));

	// SEND PROFILE BODY
	Profile profile;
	strcpy_s(profile.name, g_member.name);
	strcpy_s(profile.id, g_member.id);
	strcpy_s(profile.imageName, g_member.imageName);
	Send((char*)&profile, sizeof(Profile));

	// SEND IMAGE BODY
	CFile imageFile;
	byte* imageData = new byte[4096];
	DWORD dwRead;

	CString imageName;
	imageName.Format("profileImage\\%s", g_member.imageName);
	imageFile.Open(imageName, CFile::modeReadWrite | CFile::typeBinary);

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
	if(response.command != JOINED_NEW_USER_PROFILE)
		AfxMessageBox("JOINED_NEW_USER_PROFILE COM ERROR!!");
}

// Send Point (Draw)
void CClientSocket::SendPoint(CPoint startPoint, CPoint endPoint, int thinkness, COLORREF rgb)
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

CString CClientSocket::RecvString(int dataSize)
{
	char* pChar = new char[dataSize];
	Receive(pChar, dataSize);
	CString str = (LPSTR)pChar;
	delete[] pChar;
	return str;
}

void CClientSocket::OnReceive(int nErrorCode)
{
	// HEADER RECV
	Header header;
	Receive(&header, sizeof(Header));

	byte result = 1;
	Send(&result, sizeof(byte));

	if(header.startBit != 0x21) // START BIT CHECK
		return;
	
	switch(header.command)
	{
	case FULL_ROOM : 
		{
			// RECEIVE BODY X

			// LOGIC
			((CCATCHMINDDlg*)AfxGetMainWnd())->m_watingRoomDlg->NoticeFullRoom();

			// SEND RESULT RESPONSE
			SendResponse(FULL_ROOM, 1);

			this->Close(); // Socket Close
			break;
		}
	case PRIVATE_ROOM :
		{
			// RECEIVE BODY
			CString password = RecvString(header.dataSize);

			// LOGIC
			CPasswordDlg passwordDlg;
			if(passwordDlg.DoModal() == IDOK)
			{
				if(passwordDlg.m_password == password) // LOGIN SUCCESS
				{
					AfxMessageBox("PRIVATE ROOM JOIN SUCCESS");
					g_logManager.Log("PRIVATE ROOM JOIN SUCCESS");
					((CCATCHMINDDlg*)AfxGetMainWnd())->m_watingRoomDlg->NoticeAccept();

					// SEND RESPONSE
					SendResponse(PRIVATE_ROOM, 1);

					return;
				}
			} 
			// LOGIN FAIL OR PASSWORDDLG CANCEL
			AfxMessageBox("PRIVATE ROOM PASSWORD INCORRECT OR CANCEL");
			g_logManager.Log("PRIVATE ROOM PASSWORD INCORRECT OR CACEL");
			((CCATCHMINDDlg*)AfxGetMainWnd())->m_watingRoomDlg->NoticeFullRoom();

			// SEND RESULT RESPONSE
			SendResponse(PRIVATE_ROOM, 0);

			this->Close();	
			break;
		}
	case ACCEPT :
		{
			// BODY X

			// LOGIC 
			((CCATCHMINDDlg*)AfxGetMainWnd())->m_watingRoomDlg->NoticeAccept();

			// SEND RESPONSE
			SendResponse(ACCEPT, 0);
			break;
		}
	case MESSAGE :
		{
			ChatMessage chatMessage;
			Receive((char*)&chatMessage, header.dataSize);
			CString name = (LPSTR)chatMessage.name;
			CString message = (LPSTR)chatMessage.message;
			SendMessage(((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->m_hWnd, WM_RECV_MESSAGE, (WPARAM)&name, (LPARAM)&message);
			break;
		}
	case POINT :
		{
			Point point;
			Receive((char*)&point, header.dataSize);
			SendMessage(((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->m_hWnd, WM_DRAW, 0, (LPARAM)&point);
			byte result = 1;
			Send(&result, sizeof(byte));
			break;

		}
	case EXISTING_USER_IN_ROOM_PROFILE :
		{
			// RECV BODY PROFILE
			Profile profile;
			Receive((char*)&profile, sizeof(Profile));
			m_vProfile.push_back(profile);

			// RECV BODY IMAGE & LOGIC
			ULONGLONG fileSize;
			Receive(&fileSize, sizeof(ULONGLONG));
			
			byte* imageData = new byte[4096];
			DWORD dwRead;
			ULONGLONG receiveSize = 0;
			
			CString imageName = profile.imageName;
			CString imagePath = "profileImage\\client\\" + imageName;
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

			// SEND RESULT RESPONSE
			SendResponse(EXISTING_USER_IN_ROOM_PROFILE, 1);
			((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->AddProfileToList(&profile);

			break;
			
		}
	case REQUEST_PROFILE:
		{
			SendMyProfile();
			//SendResponse(REQUEST_PROFILE, 1);
			break;
		}

	case JOINED_NEW_USER_PROFILE :
		{
			// profile
			Profile profile;
			Receive((char*)&profile, sizeof(Profile));
			m_vProfile.push_back(profile);

			// image save
			ULONGLONG fileSize;

			Receive(&fileSize, sizeof(ULONGLONG));

			byte* imageData = new byte[4096];
			DWORD dwRead;
			ULONGLONG receiveSize = 0;

			CString imageName = profile.imageName;
			CString imagePath = "profileImage\\client\\" + imageName;
			CFile file;
			file.Open(imagePath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
			do{
				dwRead = Receive(imageData, 4096);
				file.Write(imageData, dwRead);
				receiveSize += dwRead;
				if(receiveSize >= fileSize)
					break;
			}while(dwRead > 0);

			byte result = 1;
			Send(&result, sizeof(byte));

			delete imageData;
			file.Close();
			((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->AddProfileToList(&profile);

			break;
		}
	case QUIZ :
		{
			// RECV BODY
			m_quiz = RecvString(header.dataSize);
			
			// ROGIC
			((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->SetQuiz(m_quiz);
			
			// SEND RESULT RESPONSE
			SendResponse(QUIZ, 1);
			break;
		}
	case CHANGE_MODE :
		{
			int mode;
			Receive(&mode, header.dataSize);
			((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->SetMode(mode);
			break;
		}
	}

}




