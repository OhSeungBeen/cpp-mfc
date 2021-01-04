// ClientSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CLIENT.h"
#include "ClientSocket.h"
#include "CLIENTDlg.h"

// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}


void CClientSocket::OnReceive(int nErrorCode)
{
	CCLIENTDlg* clientDlg = (CCLIENTDlg*)AfxGetMainWnd();
	CString stxHex, etxHex;

	clientDlg->GetDlgItemText(IDC_EDIT_STX, stxHex);
	clientDlg->GetDlgItemText(IDC_EDIT_ETX, etxHex);
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
		((CCLIENTDlg*)AfxGetMainWnd())->AddLogString("[recv]" + recvMessage);
	}


	CSocket::OnReceive(nErrorCode);
}
