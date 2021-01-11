// ClientSocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CATCHMIND.h"
#include "ClientSocket.h"


// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}

void CClientSocket::SendJoinInfo(CString name, CString id, CString pw, CString imagePath)
{
	
	Header header;
	header.id = JOIN;
	header.size = sizeof(JoinInfo);

	JoinInfo joinInfo;
	strcpy_s(joinInfo.name, name);
	strcpy_s(joinInfo.id, id);
	strcpy_s(joinInfo.pw, pw);
	strcpy_s(joinInfo.imagePath, "test");

	Send((char*)&header, sizeof(header)); // header
	Send((char*)&joinInfo, sizeof(JoinInfo)); // body
	
	int result;
	Receive(&result, sizeof(int));
	if(result == 1)
		AfxMessageBox("ȸ�� ���� �Ϸ�!");
	else
		AfxMessageBox("ȸ�� ���� ����!");
}

void CClientSocket::SendLoginInfo(CString id, CString pw)
{

	Header header;
	header.id = LOGIN;
	header.size = sizeof(LoginInfo);

	LoginInfo loginInfo;
	strcpy_s(loginInfo.id, id);
	strcpy_s(loginInfo.pw, pw);

	Send((char*)&header, sizeof(header)); // header
	Send((char*)&loginInfo, sizeof(LoginInfo)); // body

	int result;
	Receive(&result, sizeof(int));
	if(result == 1)
	{
		AfxMessageBox("�α��� ����!");
		CWnd *pWnd = AfxGetMainWnd();

		CWatingRoomDlg* watingRoomDlg = new CWatingRoomDlg();
		watingRoomDlg->Create(IDD_WATINGROOM_DIALOG, pWnd);
		watingRoomDlg->ShowWindow(SW_SHOW);
		//pWnd->ShowWindow(SW_HIDE);

		Receive((char*)&m_profileInfo, sizeof(loginInfo)); // ������ ���� ����
	}
	else
	{
		AfxMessageBox("�α��� ����!");
	}
}


