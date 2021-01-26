// ListenSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CATCHMIND.h"
#include "CATCHMINDDlg.h"
#include "ListenSocket.h"
#include "ServerSocket.h"
#include "Global.h"

// CListenSocket

CListenSocket::CListenSocket()
{
}

CListenSocket::~CListenSocket()
{
}

// Client Accept
void CListenSocket::OnAccept(int nErrorCode)
{
	CServerSocket* serverSocket = new CServerSocket(&m_pServerSocketList, &m_vProfile);
	
	if(Accept(*serverSocket))
	{
		//AfxMessageBox("TRY ACCEPT");
		//g_log.Log("TRY ACCEPT");
		m_pServerSocketList.AddTail(serverSocket);
		
		if(m_userSize <= m_pServerSocketList.GetSize()) // FULL ROOM
		{
			serverSocket->SendFullRoom();
			return;
		}

		if(m_privateRoom) // PROVIATE ROOM
		{
			serverSocket->SendPrivate(m_password);
			return;
		}
		 // ACCEPT SUCCESS
		serverSocket->SendAccept(); // NOTICE ACCEPT
		serverSocket->SendQuiz(g_listenSocket.m_quiz); // SEND QUIZ
		serverSocket->SendProfiles(); // SEND PROFILES
		serverSocket->RequestProfile(); // GIVE ME PROFILE
	}
	else
	{
		AfxMessageBox("ACCEPT FAIL");
		g_logManager.Log("ACCEPT FAIL");
	}
	CSocket::OnAccept(nErrorCode);
}


// Send All Client ChatMsg
void CListenSocket::SendAllChatMsg(CString name, CString message)
{
	POSITION pos = m_pServerSocketList.GetHeadPosition();
	while (pos != NULL) 
	{
		CServerSocket* serverSocket = (CServerSocket*)m_pServerSocketList.GetNext(pos);
		serverSocket->SendChatMsg(name, message);
	}
}

// Send All Client Point(Draw)
void CListenSocket::SendAllPoint(CPoint startPoint, CPoint endPoint, int thinkness, COLORREF rgb)
{
	POSITION pos = m_pServerSocketList.GetHeadPosition();
	while (pos != NULL) 
	{
		CServerSocket* serverSocket = (CServerSocket*)m_pServerSocketList.GetNext(pos);
		serverSocket->SendPoint(startPoint, endPoint, thinkness, rgb);
	}
}

// Send All Client Quiz
void CListenSocket::SendAllQuiz(CString quiz)
{
	POSITION pos = m_pServerSocketList.GetHeadPosition();
	while (pos != NULL) 
	{
		CServerSocket* serverSocket = (CServerSocket*)m_pServerSocketList.GetNext(pos);
		serverSocket->SendQuiz(quiz);
	}
}

// Send All Client Mode
void CListenSocket::SendAllMode(int mode)
{
	POSITION pos = m_pServerSocketList.GetHeadPosition();
	while (pos != NULL) 
	{
		CServerSocket* serverSocket = (CServerSocket*)m_pServerSocketList.GetNext(pos);
		serverSocket->SendMode(mode);
	}
}

// Send All Client Clear
void CListenSocket::SendAllClear()
{
	POSITION pos = m_pServerSocketList.GetHeadPosition();
	while (pos != NULL) 
	{
		CServerSocket* serverSocket = (CServerSocket*)m_pServerSocketList.GetNext(pos);
		serverSocket->SendClear();
	}
}