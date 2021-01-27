#pragma once
#include <vector>
#include "Data.h"

#define FULL_ROOM 0x46
#define GAME_READY 0x52
#define GAME_START 0x53
//#define GAME_END 0x45
//#define NEXT_TURN 0x4E
//#define BLACK_BINGO 0x42
#define QUIZ 0x51
#define MESSAGE 0x4D
//#define WORD 0x57
#define PROFILE 0x50
#define PROFILE2 0x60

class CClientSocket : public CSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();

	BOOL m_connected;
	CString m_quiz;
	std::vector<Profile> m_vProfile;

	void SendHeader(byte command, int dataSize);
	void SendResponse(byte command, byte result);
	Response RecvResponse();

	void SendProfile();
	void SendChatMsg(CString name, CString message);
	void SendGameReady(CString words);

	virtual void OnReceive(int nErrorCode);
};


