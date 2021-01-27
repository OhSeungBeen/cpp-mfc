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
	int m_bingo;
	CString m_quiz;

	CObList m_pServerSocketList;
	std::vector<Profile> m_vProfile; // Room Users Profiles
	std::vector<CString> m_vWords; // Room Users Words

	void OnAccept(int nErrorCode);
	void SendAllChatMsg(CString name, CString message);
	void SendAllGameStart();

	/*void SendAllProfile();
	void SendAllPoint(CPoint startPoint, CPoint endPoint, int thinkness, COLORREF rgb);
	void SendAllQuiz(CString quiz);
	void SendAllMode(int mode);*/
};


