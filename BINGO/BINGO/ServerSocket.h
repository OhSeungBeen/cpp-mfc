#pragma once
#include <vector>
#define FULL_ROOM 0x46
#define GAME_READY 0x52
#define GAME_START 0x53
#define GAME_END 0x45
#define NEXT_TURN 0x4E
#define BLACK_BINGO 0x42
#define QUIZ 0x51
#define MESSAGE 0x4D
#define WORD 0x57
#define PROFILE 0x50
#define PROFILE2 0x60

class CServerSocket : public CSocket
{
public:
	CServerSocket(CObList* m_pServerSocketList, std::vector<Profile>* vProfile, std::vector<CString>* vWords);
	virtual ~CServerSocket();

	CObList* m_pServerSocketList;
	std::vector<Profile>* m_vProfile;
	std::vector<CString>* m_vWords;
	
	
	void SendHeader(byte command, int dataSize);
	void SendResponse(byte command, byte result);
	Response RecvResponse();

	void SendFullRoom();
	void SendProfiles();
	void RequestProfile();
	void SendOtherProfile(Profile profile);
	void SendChatMsg(CString name, CString message);
	void SendOtherChatMsg(CString name, CString message);
	void SendQuiz(CString quiz);

	/*void SendAccept();
	void SendPrivate(CString password);
	void SendPoint(CPoint startPoint, CPoint endPoint, int thinkness, COLORREF rgb);
	void SendMode(int mode);
	void SendOtherMode(int mode);
	void SendOhterQuiz(CString quiz);*/

	/*CString RecvString(int dataSize);*/

	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


