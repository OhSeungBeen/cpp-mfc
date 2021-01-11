// ListenSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CATCHMINDSERVER.h"
#include "ListenSocket.h"

// ListenSocket

CListenSocket::CListenSocket()
{
}

CListenSocket::~CListenSocket()
{
}


void CListenSocket::OnAccept(int nErrorCode)
{
	CClientSocket* clientSocket = new CClientSocket(&m_clientSocketList);
	m_clientSocketList.AddTail(clientSocket);

	if(Accept(*clientSocket))
	{
		//AfxMessageBox("Accept Success!");
	}
	else
	{
		AfxMessageBox("Accept Fail!");
	}
	CSocket::OnAccept(nErrorCode);
}

