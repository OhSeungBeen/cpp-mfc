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

	// SEND HEADER
	SendHeader(POINT, sizeof(Point));

	// SEND BODY
	Send(&point, sizeof(Point));

	// RECV RESULT RESPONSE
	Response response = RecvResponse();
	if(response.command != POINT)
		AfxMessageBox("POINT COM ERROR!!");
}

void CClientSocket::SendClear()
{
	// SEND HEADER
	SendHeader(CLEAR, 0);

	// BODY X

	// RECV RESULT RESPONSE
	Response response = RecvResponse();
	if(response.command != CLEAR)
		AfxMessageBox("CLEAR COM ERROR!!");
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

	int result = 1;
	Send(&result, sizeof(int));

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
			SendResponse(ACCEPT, 1);
			break;
		}
	case MESSAGE :
		{
			//RECV BODY
			ChatMessage chatMessage;
			Receive((char*)&chatMessage, header.dataSize);

			// LOGIC
			((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->AddMessageToList((LPSTR)chatMessage.name, (LPSTR)chatMessage.message);

			// SEND RESPONSE
			SendResponse(MESSAGE, 1);
			break;
		}
	case POINT :
		{
			// RECV BODY
			Point point;
			Receive((char*)&point, header.dataSize);

			// LOGIC
			((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->Draw(&point);

			// SEND RESPONSE
			SendResponse(POINT, 1);
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
			// BODY X

			// SEND RESULT RESPONSE
			SendResponse(REQUEST_PROFILE, 1);

			SendMyProfile();
			break;
		}
	case JOINED_NEW_USER_PROFILE :
		{
			// RECV PROFILE BODY
			Profile profile;
			Receive((char*)&profile, sizeof(Profile));
			m_vProfile.push_back(profile);

			// RECV IMAGE BODY & LOGIC
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
			((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->AddProfileToList(&profile);
			// SEND RESULT RESPONSE
			SendResponse(JOINED_NEW_USER_PROFILE, 1);
			break;
		}
	case QUIZ :
		{
			// RECV BODY
			m_quiz = RecvString(header.dataSize);

			// LOGIC
			((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->SetQuiz(m_quiz);

			// SEND RESULT RESPONSE
			SendResponse(QUIZ, 1);
			break;
		}
	case CHANGE_MODE :
		{
			// RECV BODY
			int mode;
			Receive(&mode, header.dataSize);

			// LOGIC
			((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->SetMode(mode);

			// SEND RESULT RESPONSE
			SendResponse(CHANGE_MODE, 1);
			break;
		}
	case CLEAR :
		{
			// LOGIC
			((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->Clear();

			// SEND RESULT RESPONSE
			SendResponse(CLEAR, 1);
			break;
		}
	}

}




