#pragma once
#include "ClientSocket.h"
// ListenSocket ��� ����Դϴ�.

class CListenSocket : public CSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket();

	CObList m_clientSocketList;
	void OnAccept(int nErrorCode);
};


