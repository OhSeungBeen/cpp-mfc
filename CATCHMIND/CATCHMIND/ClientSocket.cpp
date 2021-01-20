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
	header.dataSize = dataSize;
	Send((char*)&header, sizeof(Header));
	byte result = 1;
	Receive(&result, sizeof(byte));
}


CString CClientSocket::RecvString(int dataSize)
{
	char* pChar = new char[dataSize];
	Receive(pChar, dataSize);
	CString str = (LPSTR)pChar;
	delete[] pChar;
	return str;
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

// Send Profile To Server
void CClientSocket::SendProfile()
{
	// profile
	Profile profile;
	strcpy_s(profile.name, g_member.name);
	strcpy_s(profile.id, g_member.id);
	strcpy_s(profile.imageName, g_member.imageName);
	SendHeader(PROFILE, sizeof(Profile));
	Send((char*)&profile, sizeof(Profile));

	// image
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
}

void CClientSocket::OnReceive(int nErrorCode)
{
	Header header;
	Receive(&header, sizeof(Header));
	byte result = 1;
	Send(&result, sizeof(byte));

	if(header.startBit != 0x21)
		return;

	switch(header.command)
	{
	case FULL_ROOM : 
		{
			SendMessage(((CCATCHMINDDlg*)AfxGetMainWnd())->m_watingRoomDlg->m_hWnd, WM_DISCONNECT, 0, 0);
			this->Close(); // socket disconnect
			break;
		}
	case ACCEPT :
		{
			SendMessage(((CCATCHMINDDlg*)AfxGetMainWnd())->m_watingRoomDlg->m_hWnd, WM_ACCEPT, 0, 0);
			break;
		}
	case PRIVATE_ROOM :
		{
			CString password = RecvString(header.dataSize);
			CPasswordDlg passwordDlg;
			if(passwordDlg.DoModal() == IDOK)
			{
				if(passwordDlg.m_password == password)
				{
					AfxMessageBox("PRIVATE ROOM JOIN SUCCESS");
					g_logManager.Log("PRIVATE ROOM JOIN SUCCESS");
					SendMessage(((CCATCHMINDDlg*)AfxGetMainWnd())->m_watingRoomDlg->m_hWnd, WM_ACCEPT, 0, 0);
					return;
				}
			}
			AfxMessageBox("PRIVATE ROOM PASSWORD INCORRECT");
			g_logManager.Log("PRIVATE ROOM PASSWORD INCORRECT");
			this->Close();	
			SendMessage(((CCATCHMINDDlg*)AfxGetMainWnd())->m_watingRoomDlg->m_hWnd, WM_DISCONNECT, 0, 0);

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
			break;
		}
	case PROFILE :
		{
			int size = header.dataSize / sizeof(Profile);
			for(int i = 0; i < size; i ++)
			{
				// profile
				Profile profile;
				Receive((char*)&profile, sizeof(Profile));
				m_vProfile.push_back(profile);

				byte result = 1;
				

				// image save
				ULONGLONG fileSize;
				Receive(&fileSize, sizeof(ULONGLONG));

				Send(&result, sizeof(byte)); //
				
				byte* imageData = new byte[4096];
				DWORD dwRead;
				ULONGLONG receiveSize = 0;

				CString imageName = profile.imageName;
				CString imagePath = "profileImage\\client\\" + imageName;
				CFile file;
				file.Open(imagePath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
				do{
					dwRead = Receive(imageData, 4096);

					Send(&result, sizeof(byte)); //

					file.Write(imageData, dwRead);
					receiveSize += dwRead;
					if(receiveSize >= fileSize)
						break;
				}while(dwRead > 0);

				delete imageData;
				file.Close();
			}
			SendMessage(((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->m_hWnd, WM_USER_PROFILE, 0, (LPARAM)&m_vProfile);
			SendProfile();
			break;
		}

	case QUIZ :
		{
			m_quiz = RecvString(header.dataSize);
			((CCATCHMINDDlg*)AfxGetMainWnd())->m_gameRoomDlg->SetQuiz(m_quiz);
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




 