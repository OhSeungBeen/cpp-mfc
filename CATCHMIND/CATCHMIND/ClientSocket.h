#pragma once
#include <vector>
#include "Data.h"

#define FULL_ROOM 0x40
#define ACCEPT 0x41
#define PRIVATE_ROOM 0x42
#define POINT 0x43
#define MESSAGE 0x44
#define EXISTING_USER_IN_ROOM_PROFILE 0x45
#define JOINED_NEW_USER_PROFILE 0x46
#define REQUEST_PROFILE 0x47
#define PROFILE_RECV_FROM_CLIENT 0x48
#define QUIZ 0x49
#define CHANGE_MODE 0x50

class CClientSocket : public CSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();

	BOOL m_connected;
	CString m_quiz;
	std::vector<Profile> m_vProfile;

	void SendHeader(byte command, int dataSize);
	void SendPoint(CPoint startPoint, CPoint endPoint, int thinkness, COLORREF rgb);
	void SendChatMsg(CString name, CString message);
	void SendMyProfile();
	void SendResponse(byte command, byte result);
	CString RecvString(int dataSize);
	Response RecvResponse();
	virtual void OnReceive(int nErrorCode);
};


