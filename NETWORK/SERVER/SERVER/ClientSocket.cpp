// ClientSocket.cpp : ���� �����Դϴ�.
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


// �����͸� ������ ȣ��ȴ�.
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


// Ŭ���̾�Ʈ�� ������ ����������
void CClientSocket::OnClose(int nErrorCode)
{

	CSocket::OnClose(nErrorCode);

	// ����Ʈ���� �ش� ������ ã�� �����Ѵ�.
	CClientSocket* p;
	// ù��带 ���´�.
	POSITION pos = m_pClientSocketList->GetHeadPosition(), pre_pos;
	// ������ ������
	while (pos != NULL) {
		pre_pos = pos;
		// ���� �����̵�
		p = (CClientSocket *)m_pClientSocketList->GetNext(pos);
		// �ڽ� Ŭ������� ����
		if (p == this) {
			// ���� ���� �̵��� �����̹Ƿ� �����������
			m_pClientSocketList->RemoveAt(pre_pos);
			delete p;
		}
	}
}

