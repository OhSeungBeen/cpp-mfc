// serverSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SERVER.h"
#include "ListenSocket.h"
#include "ClientSocket.h"
#include "SERVERDlg.h"

// serverSocket

CListenSocket::CListenSocket()
{
}

CListenSocket::~CListenSocket()
{
}


// 클라이언트로부터 접속이 되면 호출된다.
// 새로운 소켓을 생성
void CListenSocket::OnAccept(int nErrorCode)
{
	//클라이언트에 접속이될때마다 동적으로 소켓을 생성하고 List에 추가한다.
	//생성자를통해 ClientSocket객체를 생성할때 자기자신을 담을 리스트의 주소를
	//넣어 초기화한다. (접속을 해제했을때 리스트에서 자기자신을 지우기위해)
	CClientSocket* clientSocket = new CClientSocket(&m_clientSocketList);
	m_clientSocketList.AddTail(clientSocket);
	
	CSERVERDlg* serverDlg = (CSERVERDlg*)AfxGetMainWnd();
	if(Accept(*clientSocket)) // 각각의 클라이언트 Accept
	{
		serverDlg->AddLogString("Accept Success!");
	}
	else
	{
		serverDlg->AddLogString("Accept Fail!");
	}
	CSocket::OnAccept(nErrorCode);
}



