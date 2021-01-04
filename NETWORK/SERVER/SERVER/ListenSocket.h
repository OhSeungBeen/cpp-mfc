#pragma once

// serverSocket 명령 대상입니다.

class CListenSocket : public CSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket();
	void OnAccept(int nErrorCode);

	CObList m_clientSocketList;
};


