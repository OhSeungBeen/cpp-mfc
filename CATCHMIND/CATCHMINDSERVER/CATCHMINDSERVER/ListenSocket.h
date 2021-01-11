#pragma once
#include "ClientSocket.h"
// ListenSocket 명령 대상입니다.

class CListenSocket : public CSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket();

	CObList m_clientSocketList;
	void OnAccept(int nErrorCode);
};


