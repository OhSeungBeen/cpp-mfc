#pragma once

// CClientSocket ��� ����Դϴ�.

class CClientSocket : public CSocket
{
public:
	CClientSocket(CObList * m_pClientSocketList);
	virtual ~CClientSocket();

	// *�ڱ��ڽ��� ������ ����Ʈ �ּҸ� ���� ��������
	CObList* m_pClientSocketList;
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};

