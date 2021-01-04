// ClientSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SERVER.h"
#include "ClientSocket.h"
#include "SERVERDlg.h"


// CClientSocket

CClientSocket::CClientSocket(CObList * m_pClientSocketList)
{
	this->m_pClientSocketList = m_pClientSocketList;
}

CClientSocket::~CClientSocket()
{
}


// 데이터를 받을때 호출된다.
void CClientSocket::OnReceive(int nErrorCode)
{
	
	CSERVERDlg* serverDlg = (CSERVERDlg*)AfxGetMainWnd();
	CString stxHex, etxHex;

	serverDlg->GetDlgItemText(IDC_EDIT_STX, stxHex);
	serverDlg->GetDlgItemText(IDC_EDIT_ETX, etxHex);
	char stx = (char)_tcstoul(stxHex, NULL, 16);
	char etx = (char)_tcstoul(etxHex, NULL, 16);

	char data;
	CString recvMessage;
	Receive(&data, sizeof(char));
	if(data == stx)
	{
		while(TRUE)
		{	
			Receive(&data, sizeof(char));
			if(data == etx)
				break;
			recvMessage += data;
		}
		serverDlg->AddLogString("[recv]" + recvMessage);
	}

	CSocket::OnReceive(nErrorCode);
}


// 클라이언트가 접속을 해제했을때
void CClientSocket::OnClose(int nErrorCode)
{

	CSocket::OnClose(nErrorCode);

	// 리스트에서 해당 소켓을 찾아 제거한다.
	CClientSocket* p;
	// 첫노드를 얻어온다.
	POSITION pos = m_pClientSocketList->GetHeadPosition(), pre_pos;
	// 마지막 노드까지
	while (pos != NULL) {
		pre_pos = pos;
		// 다음 노드로이동
		p = (CClientSocket *)m_pClientSocketList->GetNext(pos);
		// 자신 클래스라면 삭제
		if (p == this) {
			// 다음 노드로 이동한 상태이므로 이전노드제거
			m_pClientSocketList->RemoveAt(pre_pos);
			delete p;
		}
	}
}

