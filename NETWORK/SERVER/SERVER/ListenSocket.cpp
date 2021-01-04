// serverSocket.cpp : ���� �����Դϴ�.
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


// Ŭ���̾�Ʈ�κ��� ������ �Ǹ� ȣ��ȴ�.
// ���ο� ������ ����
void CListenSocket::OnAccept(int nErrorCode)
{
	//Ŭ���̾�Ʈ�� �����̵ɶ����� �������� ������ �����ϰ� List�� �߰��Ѵ�.
	//�����ڸ����� ClientSocket��ü�� �����Ҷ� �ڱ��ڽ��� ���� ����Ʈ�� �ּҸ�
	//�־� �ʱ�ȭ�Ѵ�. (������ ���������� ����Ʈ���� �ڱ��ڽ��� ���������)
	CClientSocket* clientSocket = new CClientSocket(&m_clientSocketList);
	m_clientSocketList.AddTail(clientSocket);
	
	CSERVERDlg* serverDlg = (CSERVERDlg*)AfxGetMainWnd();
	if(Accept(*clientSocket)) // ������ Ŭ���̾�Ʈ Accept
	{
		serverDlg->AddLogString("Accept Success!");
	}
	else
	{
		serverDlg->AddLogString("Accept Fail!");
	}
	CSocket::OnAccept(nErrorCode);
}



