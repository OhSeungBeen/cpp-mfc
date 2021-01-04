#pragma once

// CClientSocket 명령 대상입니다.

class CClientSocket : public CSocket
{
public:
	CClientSocket(CObList * m_pClientSocketList);
	virtual ~CClientSocket();

	// *자기자신을 저장할 리스트 주소를 받을 변수선언
	CObList* m_pClientSocketList;
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};

