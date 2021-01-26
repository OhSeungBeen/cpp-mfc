#pragma once
#include <vector>
#include "Data.h"
// CListenSocket 명령 대상입니다.

class CListenSocket : public CSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket();

	BOOL m_connected;
	int m_userSize;
	bool m_privateRoom;
	CString m_password;
	CString m_quiz;

	CObList m_pServerSocketList;
	std::vector<Profile> m_vProfile; // Room Users Profiles

	void OnAccept(int nErrorCode);

	void SendAllGameStart();
	void SendAllChatMsg(CString name, CString message);
	void SendAllProfile();
	void SendAllPoint(CPoint startPoint, CPoint endPoint, int thinkness, COLORREF rgb);
	void SendAllQuiz(CString quiz);
	void SendAllMode(int mode);
	void SendAllClear();
};


