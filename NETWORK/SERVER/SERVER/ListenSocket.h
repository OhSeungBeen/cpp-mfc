#pragma once

// serverSocket ��� ����Դϴ�.

class CListenSocket : public CSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket();
	void OnAccept(int nErrorCode);

	CObList m_clientSocketList;
};


