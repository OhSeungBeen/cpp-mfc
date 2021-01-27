// ListenSocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "BINGO.h"
#include "BINGODlg.h"
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
	CServerSocket* serverSocket = new CServerSocket(&m_pServerSocketList, &m_vProfile, &m_vWords);
	
	if(Accept(*serverSocket))
	{
		m_pServerSocketList.AddTail(serverSocket);
		
		if(m_pServerSocketList.GetSize() >= 4) // FULL ROOM
		{
			serverSocket->SendFullRoom();
			return;
		}
		serverSocket->SendProfiles();
	}
	else
	{
		AfxMessageBox("ACCEPT FAIL");
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

// Send All Client GameStart
void CListenSocket::SendAllGameStart()
{
	POSITION pos = m_pServerSocketList.GetHeadPosition();
	int socketListIndex = 1;
	while (pos != NULL) 
	{
		CServerSocket* serverSocket = (CServerSocket*)m_pServerSocketList.GetNext(pos);
		int wordCount = m_vWords.size();
		// SEND HEADER
		serverSocket->SendHeader(GAME_START, wordCount - 1); // �ش� Ŭ���̾�Ʈ words�� ���� ����.
		// SEND BODY
		for(int i = 0; i < wordCount; i++)
		{
			if(i == socketListIndex) continue; // �ش� Ŭ���̾�Ʈ words�� �����ϰ� �����ش�.
			int wordSize = m_vWords[i].GetLength() + 1;
			serverSocket->Send(&wordSize, sizeof(int));
			serverSocket->Send(m_vWords[i].GetBuffer(), wordSize);
		}
		// RECV RESULT RESPONSE
		Response response = serverSocket->RecvResponse();
		if(response.command != GAME_START)
			AfxMessageBox("GAME_START COM ERROR!!");

		socketListIndex++;
	}
}

// Send All Client Quiz
//void CListenSocket::SendAllQuiz(CString quiz)
//{
//	POSITION pos = m_pServerSocketList.GetHeadPosition();
//	while (pos != NULL) 
//	{
//		CServerSocket* serverSocket = (CServerSocket*)m_pServerSocketList.GetNext(pos);
//		serverSocket->SendQuiz(quiz);
//	}
//}

// Send All Client Mode
//void CListenSocket::SendAllMode(int mode)
//{
//	POSITION pos = m_pServerSocketList.GetHeadPosition();
//	while (pos != NULL) 
//	{
//		CServerSocket* serverSocket = (CServerSocket*)m_pServerSocketList.GetNext(pos);
//		serverSocket->SendMode(mode);
//	}
//}